
#include "MainExec.h"
#include "../ExecManager.h"
#include "../stexcept.h"
#include "../../darv/CMD.h"
#include "../../inter/InterResult.h"
#include "../../shell/shell.h"
#include "../../util/strutil.h"
#include "../../io/io.h"
#include "../../io/SourceCodeManager.h"
#include "../../output/output.h"
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

MainExec::MainExec() {
    cleanTaskExec = new CleanTaskExec();
    compileTaskExec = new CompileTaskExec();
    linkOrArchiveTaskExec = new LinkOrArchiveTaskExec();
    copyTaskExec = new CopyTaskExec();
}

MainExec::~MainExec() {
    delete cleanTaskExec;
    delete compileTaskExec;
    delete linkOrArchiveTaskExec;
    delete copyTaskExec;
}

void MainExec::exec( CMD* mainCMD, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;

    Output& out = manager->out;
    bool isShowHelp = manager->getMainCMDArgManager()->isHelp();
    bool isVerbose = manager->getMainCMDArgManager()->isVerbose();
    bool isNoResume = manager->getMainCMDArgManager()->isNoResume();

    if ( mainCMD->countNoOpArgs() == 0 || isShowHelp ) {
        this->showHelp( mgr );
        return;
    }
    
    this->configureEnvironmentAndInterpretsMainScript( mgr );
    this->validaMainCMD( mgr );

    bool isClean = manager->getMainCMDArgManager()->isClean();
    bool isCompile = manager->getMainCMDArgManager()->isCompile();
    bool isCompileAll = manager->getMainCMDArgManager()->isCompileAll();
    bool isLink = manager->getMainCMDArgManager()->isLink();
    bool isArchive = manager->getMainCMDArgManager()->isArchive();
    bool isCopy = manager->getMainCMDArgManager()->isCopy();
    bool isBuild = manager->getMainCMDArgManager()->isBuild();
    bool isBuildAll = manager->getMainCMDArgManager()->isBuildAll();

    this->genSourceAndHeaderInfos( manager );

    manager->executaUserTaskIfExists( tasks::INIT, TaskExecution::BEFORE );
    manager->executaUserTaskIfExists( tasks::INIT, TaskExecution::AFTER );

    if ( isBuild )
        manager->executaUserTaskIfExists( tasks::BUILD, TaskExecution::BEFORE );
    if ( isBuildAll )
        manager->executaUserTaskIfExists( tasks::BUILDALL, TaskExecution::BEFORE );

    if ( isClean )
        cleanTaskExec->exec( mgr );
    if ( isCompile || isCompileAll )
        compileTaskExec->exec( mgr );
    if ( isLink || isArchive )
        linkOrArchiveTaskExec->exec( mgr );
    if ( isCopy )
        copyTaskExec->exec( mgr );
    
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

void MainExec::validaMainCMD( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    MainScript* script = manager->getMainScript();
    CMD* mainCMD = manager->getMainCMD();

    vector<string>& args = mainCMD->args();
    int len = args.size();
    for( int i = 0; i < len; i++ ) {
        string arg = args[ i ];
        if ( strutil::startsWith( arg, "-" ) )
            continue;

        if ( i > 0 )
            if ( args[ i-1 ] == "-var" || args[ i-1 ] == "-prop" )
                continue;
        
        bool isDefaultTask = manager->isDefaultTask( arg );
        bool isUserTask = script->existsTask( arg );

        if ( !isDefaultTask && !isUserTask ) {
            messagebuilder b( errors::CMD_TASK_NOT_FOUND );
            b << arg;
            throw st_error( mainCMD, b.str() );
        }
    }
}

void MainExec::configureEnvironmentAndInterpretsMainScript( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    InterManager* interManager = manager->getInterManager();
    MainScript* mainScript = manager->getMainScript();
    CMD* mainCMD = manager->getMainCMD();

    Output& out = manager->out;
    bool isVerbose = manager->getMainCMDArgManager()->isVerbose();

    string workingDir = mainCMD->getPropertyValue( "--working-dir" );
    string settingsFile = mainCMD->getPropertyValue( "--settings-file" );

    bool workingDirFound;

    if ( workingDir != "" ) {
        workingDir = io::absoluteResolvePath( workingDir );
        shell::setWorkingDir( workingDir );

        workingDirFound = true;
    } else {
        if ( settingsFile != "" ) {
            workingDir = io::dirPath( io::absoluteResolvePath( settingsFile ) );
            settingsFile = io::fileOrDirName( settingsFile );
            shell::setWorkingDir( workingDir );
        } else {
            workingDir = shell::getWorkingDir();
        }

        workingDirFound = false;
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
        out << output::green( b2.str() ) << "\n";

        if ( !workingDirFound )
            throw st_error( nullptr, errors::NO_SETTINGS_AND_NO_WORKING_DIR );

        settingsFileFound = false;
    }

    this->loadMainCMDProperties( mgr );
    this->loadMainCMDVariables( mgr );

    mainScript->putLocalVar( "main_config_file", settingsFile );
    mainScript->putLocalVar( "working_dir", workingDir );

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
}


void MainExec::loadMainCMDProperties( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    CMD* mainCMD = manager->getMainCMD();
    MainScript* mainScript = manager->getMainScript();

    vector<string> properties = mainCMD->getOpArgValues( "-prop" );

    for( string prop : properties ) {
        size_t i = prop.find( '=' );
        if ( i == string::npos ) {
            messagebuilder b( errors::INVALID_PROP_DEF );
            b << prop;
            throw st_error( mainCMD, b.str() );
        }

        string propName = prop.substr( 0, i );
        string propValue = prop.substr( i+1, prop.length()-i-1 );

        if ( !manager->isValidProp( propName ) ) {
            messagebuilder b( errors::IS_NOT_A_VALID_PROP );
            b << propName;
            throw st_error( mainCMD, b.str() );
        }

        mainScript->putProperty( propName, propValue );
    }
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

    bool isVerbose = manager->getMainCMDArgManager()->isVerbose();

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
    bool isVerbose = manager->getMainCMDArgManager()->isVerbose();
    bool isNoResume = manager->getMainCMDArgManager()->isNoResume();

    vector<Task*> tasks = manager->getMainScript()->tasks();
    for( Task* task : tasks ) {
        string taskName = task->getName();

        bool isTaskArg = mainCMD->existsArg( taskName );
        if ( isTaskArg && !manager->isDefaultTask( taskName ) ) {
            if ( isVerbose && !isNoResume )
                out << infos::EXECUTING << " " << output::green( taskName ) << "...\n";                            

            manager->executaUserTaskIfExists( taskName, TaskExecution::BEFORE );
            manager->executaUserTaskIfExists( taskName, TaskExecution::NORMAL );
            manager->executaUserTaskIfExists( taskName, TaskExecution::AFTER );
        }
    }
}

void MainExec::executaStatements( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;

    Output& out = manager->out;
    bool isVerbose = manager->getMainCMDArgManager()->isVerbose();
    bool isNoResume = manager->getMainCMDArgManager()->isNoResume();

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
