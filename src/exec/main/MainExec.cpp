
#include "MainExec.h"
#include "../ExecManager.h"
#include "../stexcept.h"
#include "../../darv/CMD.h"
#include "../../inter/InterResult.h"
#include "../../shell/shell.h"
#include "../../util/strutil.h"
#include "../../io/io.h"
#include "../../io/SourceCodeManager.h"
#include "../../msg/messagebuilder.h"

#include "../../error_messages.h"
#include "../../info_messages.h"
#include "../../help_messages.h"
#include "../../consts.h"

#include <string>
#include <sstream>
#include <vector>

using std::string;
using std::vector;
using std::stringstream;

void MainExec::exec( CMD* mainCMD, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    InterManager* interManager = manager->getInterManager();
    MainScript* mainScript = manager->getMainScript();

    Output& out = manager->out;
    Output& inf = manager->inf;
    bool isShowHelp = manager->getArgManager()->isHelp();
    bool isVerbose = manager->getArgManager()->isVerbose();
    bool isNoResume = manager->getArgManager()->isNoResume();

    if ( mainCMD->countNoOpArgs() == 0 || isShowHelp ) {
        this->showHelp( mgr );
        return;
    }

    string workingDir = mainCMD->getPropertyValue( "--working-dir" );
    string settingsFile = mainCMD->getPropertyValue( "--settings-file" );

    if ( workingDir != "" ) {
        workingDir = io::absoluteResolvePath( workingDir );
        shell::setWorkingDir( workingDir );
    } else {
        if ( settingsFile != "" ) {
            workingDir = io::dirPath( io::absoluteResolvePath( settingsFile ) );
            settingsFile = io::fileOrDirName( settingsFile );
            shell::setWorkingDir( workingDir );
        } else {
            workingDir = shell::getWorkingDir();
        }
    }

    if ( settingsFile == "" )
        settingsFile = consts::DEFAULT_SETTINGS_FILE_NAME;

    settingsFile = io::absoluteResolvePath( settingsFile );

    if ( isVerbose ) {
        messagebuilder b( infos::CONFIGURATION_FILE );
        b << settingsFile;
        out << b.str() << "\n";
    }

    bool settingsFileFound = true;

    if ( !io::fileExists( settingsFile ) ) {
        messagebuilder b2( errors::CONFIGURATION_FILE_NOT_FOUND );
        b2 << settingsFile;
        inf << b2.str() << "\n";

        settingsFileFound = false;
    }

    mainScript->putLocalVar( "main_config_file", settingsFile );
    mainScript->putLocalVar( "working_dir", workingDir );

    this->loadMainCMDVariables( mgr );

    if ( settingsFileFound ) {
        InterResult* result = interManager->interpretsMainScript( mainScript, settingsFile, 1 );
        if ( !result->isInterpreted() )
            throw st_error( result );

        delete result;
    }

    string basedir = mainScript->getPropertyValue( props::BASE_DIR );
    if ( basedir != "" ) {
        basedir = io::absoluteResolvePath( basedir );
        if ( !io::fileExists( basedir ) ) {
            messagebuilder b( errors::BASE_DIRECTORY_NOT_FOUND );
            b << basedir << props::BASE_DIR;
            throw st_error( nullptr, b.str() );
        }
        
        shell::setWorkingDir( basedir );
    }

    string wdir = mainScript->getLocalVar( "working_dir" )->getValue();

    if ( isVerbose ) {
        messagebuilder b2( infos::CURRENT_DIRECTORY );
        b2 << wdir;
        out << b2.str() << "\n";
    }

    bool isClean = mainCMD->existsArg( tasks::CLEAN );
    bool isCompile = mainCMD->existsArg( tasks::COMPILE );
    bool isCompileAll = mainCMD->existsArg( tasks::COMPILEALL );
    bool isLink = mainCMD->existsArg( tasks::LINK );
    bool isCopy = mainCMD->existsArg( tasks::COPY );
    bool isBuild = mainCMD->existsArg( tasks::BUILD );

    bool isBuildAll = mainCMD->existsArg( tasks::BUILDALL );

    if ( isCompileAll )
        isCompile = true;

    if ( isBuild || isBuildAll ) {
        isClean = true;
        isCompile = true;
        isLink = true;
        isCopy = true;
    }

    this->genSourceAndHeaderInfos( manager );

    manager->executaUserTaskIfExists( tasks::INIT, TaskExecution::BEFORE );
    manager->executaUserTaskIfExists( tasks::INIT, TaskExecution::AFTER );

    if ( isBuild )
        manager->executaUserTaskIfExists( tasks::BUILD, TaskExecution::BEFORE );
    if ( isBuildAll )
        manager->executaUserTaskIfExists( tasks::BUILDALL, TaskExecution::BEFORE );

    if ( isClean )
        manager->executaTask( tasks::CLEAN );
    if ( isCompile )
        manager->executaTask( tasks::COMPILE );
    if ( isLink )
        manager->executaTask( tasks::LINK );
    if ( isCopy )
        manager->executaTask( tasks::COPY );
    
    if ( isBuild )
        manager->executaUserTaskIfExists( tasks::BUILD, TaskExecution::AFTER );
    if ( isBuildAll )
        manager->executaUserTaskIfExists( tasks::BUILDALL, TaskExecution::AFTER );

    this->executaNoDefaultTasks( manager );

    this->executaStatements( manager );

    manager->executaUserTaskIfExists( tasks::FINISH, TaskExecution::BEFORE );
    manager->executaUserTaskIfExists( tasks::FINISH, TaskExecution::AFTER );

    if ( isVerbose )
        out << "\n";

    if ( !isNoResume )
        out << infos::FINISH << "\n";
}

void MainExec::loadMainCMDVariables( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    CMD* mainCMD = manager->getMainCMD();
    MainScript* mainScript = manager->getMainScript();

    vector<string> variables = mainCMD->getOpArgValues( "-var" );

    for( string var : variables ) {
        size_t i = var.find( '=' );
        if ( i == string::npos ) {
            messagebuilder b( errors::INVALID_VAR_DEF );
            b << var;
            throw st_error( mainCMD, b.str() );
        }

        string varName = var.substr( 0, i );
        string varValue = var.substr( i+1, var.length()-i-1 );

        mainScript->putLocalVar( varName, varValue );
    }
}

void MainExec::genSourceAndHeaderInfos( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    SourceCodeManager* sourceCodeManager = manager->getSourceCodeManager();    

    Output& out = manager->out;
    MainScript* script = manager->getMainScript();
    CMD* mainCMD = manager->getMainCMD();

    bool isVerbose = manager->getArgManager()->isVerbose();

    string srcDir = script->getPropertyValue( props::SRC_DIR );
    if ( srcDir == "" )
        srcDir = ".";
    srcDir = io::absoluteResolvePath( srcDir );

    if ( !io::fileExists( srcDir ) ) {        
        messagebuilder b2( errors::SRC_DIRECTORY_NOT_FOUND );
        b2 << srcDir << props::SRC_DIR;
        throw st_error( mainCMD, b2.str() );
    }

    if ( isVerbose ) {
        messagebuilder b2( infos::SRC_DIRECTORY );
        b2 << srcDir;
        out << b2.str() << "\n";
    }

    bool ok = sourceCodeManager->recursiveProcFiles( srcDir );
    if ( !ok )
        throw st_error( mainCMD, errors::ERROR_IN_READING_SRC_FILES );
}

void MainExec::executaNoDefaultTasks( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    CMD* mainCMD = manager->getMainCMD();

    Output& out = manager->out;
    Output& inf = manager->inf;
    bool isVerbose = manager->getArgManager()->isVerbose();

    vector<Task*> tasks = manager->getMainScript()->tasks();
    for( Task* task : tasks ) {
        string taskName = task->getName();

        bool isTaskArg = mainCMD->existsArg( taskName );
        if ( isTaskArg && !manager->isDefaultTask( taskName ) ) {
            if ( isVerbose ) {
                out << infos::EXECUTING << " ";
                inf << taskName;
                out << "...\n";                
            }

            manager->executaUserTaskIfExists( taskName, TaskExecution::BEFORE );
            manager->executaUserTaskIfExists( taskName, TaskExecution::NORMAL );
            manager->executaUserTaskIfExists( taskName, TaskExecution::AFTER );
        }
    }
}

void MainExec::executaStatements( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;

    Output& out = manager->out;
    bool isVerbose = manager->getArgManager()->isVerbose();
    bool isNoResume = manager->getArgManager()->isNoResume();

    MainScript* script = manager->getMainScript();
    int tam = script->getStatementsLength();

    if ( tam > 0 ) {
        if( isVerbose )
            out << "\n";
        if ( !isNoResume )
            out << infos::EXECUTING_STATEMENTS << "\n";
    }

    for( int i = 0; i < tam; i++ ) {
        Statement* st = script->getStatementByIndex( i );
        manager->executaStatement( st );
    }

    if ( tam > 0 && isVerbose )
        out << infos::SUCCESS_IN_EXECUTING_STATEMENTS << "\n";
}

void MainExec::showHelp( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    CMD* mainCMD = manager->getMainCMD();

    Output& out = manager->out;
    
    int count = mainCMD->countNoOpArgs();
    if ( count == 0 ) {
        out << helpmessage::helpMessage();
    } else if ( count > 0 ) {
        string taskName = mainCMD->getNoOpArg( 0 );
        if ( taskName == tasks::CLEAN ) {
            out << helpmessage::cleanHelpMessage();
        } else if ( taskName == tasks::COMPILE ) {
            out << helpmessage::compileHelpMessage();
        } else if ( taskName == tasks::COMPILEALL ) {
            out << helpmessage::compileAllHelpMessage();
        } else if ( taskName == tasks::LINK ) {
            out << helpmessage::linkHelpMessage();
        } else if ( taskName == tasks::COPY ) {
            out << helpmessage::copyHelpMessage();
        } else if ( taskName == tasks::BUILD ) {
            out << helpmessage::buildHelpMessage();
        } else if ( taskName == tasks::BUILDALL ) {
            out << helpmessage::buildAllHelpMessage();
        } else {
            out << errors::TASK_NOT_RECOGNIZED << "\n";
        }
    }
}
