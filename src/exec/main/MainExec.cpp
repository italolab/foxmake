
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
#include <iostream>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::stringstream;

void MainExec::exec( CMD* mainCMD, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    InterManager* interManager = manager->getInterManager();
    MainScript* mainScript = manager->getMainScript();

    bool isShowHelp = manager->isHelp();
    bool isVerbose = manager->isVerbose();

    if ( mainCMD->countNoOpArgs() == 0 || isShowHelp ) {
        this->showHelp( mgr );
        return;
    }

    string settingsFile = mainCMD->getPropertyValue( "--settings-file" );
    if ( settingsFile == "" )
        settingsFile = consts::DEFAULT_SETTINGS_FILE_NAME;

    settingsFile = io::absolutePath( settingsFile );

    if ( isVerbose ) {
        messagebuilder b( infos::CONFIGURATION_FILE );
        b << settingsFile;
        cout << b.str() << endl;
    }

    if ( !io::fileExists( settingsFile ) ) {
        messagebuilder b2( errors::CONFIGURATION_FILE_NOT_FOUND );
        b2 << settingsFile;
        throw st_error( mainCMD, b2.str() );
    }

    string workingDir = io::dirPath( settingsFile );
    shell::setWorkingDir( workingDir );

    mainScript->putLocalVar( "main_config_file", settingsFile );
    mainScript->putLocalVar( "working_dir", shell::getWorkingDir() );

    InterResult* result = interManager->interpretsMainScript( mainScript, settingsFile, 1 );
    if ( !result->isInterpreted() )
        throw st_error( result );

    delete result;

    string wdir = mainScript->getLocalVar( "working_dir" )->getValue();

    if ( isVerbose ) {
        messagebuilder b2( infos::CURRENT_DIRECTORY );
        b2 << wdir;
        cout << b2.str() << endl;
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

    if ( isClean )
        manager->executaTask( tasks::CLEAN );
    if ( isCompile )
        manager->executaTask( tasks::COMPILE );
    if ( isLink )
        manager->executaTask( tasks::LINK );
    if ( isCopy )
        manager->executaTask( tasks::COPY );

    if ( isBuild )
        manager->executaUserTask( tasks::BUILD );
    if ( isBuildAll )
        manager->executaUserTask( tasks::BUILDALL );

    this->executaNoDefaultTasks( manager );
    this->executaStatements( manager );

    if ( manager->isVerbose() )
        cout << endl;
    cout << infos::FINISH << endl;
}

void MainExec::genSourceAndHeaderInfos( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    SourceCodeManager* sourceCodeManager = manager->getSourceCodeManager();    

    MainScript* script = manager->getMainScript();
    CMD* mainCMD = manager->getMainCMD();

    string srcDir = script->getPropertyValue( props::SRC_DIR );

    if ( srcDir != "" && !io::fileExists( srcDir ) ) {
        string src = io::absolutePath( srcDir );
        
        messagebuilder b2( errors::SRC_DIRECTORY_NOT_FOUND );
        b2 << src << props::SRC_DIR;
        throw st_error( mainCMD, b2.str() );
    }

    srcDir = io::absoluteResolvedPath( srcDir );

    if ( manager->isVerbose() ) {
        messagebuilder b2( infos::SRC_DIRECTORY );
        b2 << srcDir;
        cout << b2.str() << endl;
    }

    bool ok = sourceCodeManager->recursiveProcFiles( srcDir );
    if ( !ok )
        throw st_error( mainCMD, errors::ERROR_IN_READING_SRC_FILES );
}

void MainExec::executaNoDefaultTasks( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    CMD* mainCMD = manager->getMainCMD();

    vector<string> names = manager->getMainScript()->taskNames();
    for( string taskName : names ) {
        bool isTaskArg = mainCMD->existsArg( taskName );
        if ( isTaskArg && !manager->isDefaultTask( taskName ) ) {
            if ( manager->isVerbose() ) {
                stringstream ss;
                ss << infos::EXECUTING << " " << taskName << "..." << endl;                
                cout << endl << ss.str() << endl;
            }

            manager->executaUserTask( taskName );
        }
    }
}

void MainExec::executaStatements( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;

    MainScript* script = manager->getMainScript();
    int tam = script->getStatementsLength();

    if ( tam > 0 ) {
        if( manager->isVerbose() )
            cout << endl;
        cout << infos::EXECUTING_STATEMENTS << endl;
    }

    for( int i = 0; i < tam; i++ ) {
        Statement* st = script->getStatementByIndex( i );
        manager->executaStatement( st );
    }

    if ( tam > 0 && manager->isVerbose() )
        cout << infos::SUCCESS_IN_EXECUTING_STATEMENTS << endl;
}

void MainExec::showHelp( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    CMD* mainCMD = manager->getMainCMD();

    int count = mainCMD->countNoOpArgs();
    if ( count == 0 ) {
        cout << helpmessage::helpMessage();
    } else if ( count > 0 ) {
        string taskName = mainCMD->getNoOpArg( 0 );
        if ( taskName == tasks::CLEAN ) {
            cout << helpmessage::cleanHelpMessage();
        } else if ( taskName == tasks::COMPILE ) {
            cout << helpmessage::compileHelpMessage();
        } else if ( taskName == tasks::COMPILEALL ) {
            cout << helpmessage::compileAllHelpMessage();
        } else if ( taskName == tasks::LINK ) {
            cout << helpmessage::linkHelpMessage();
        } else if ( taskName == tasks::COPY ) {
            cout << helpmessage::copyHelpMessage();
        } else if ( taskName == tasks::BUILD ) {
            cout << helpmessage::buildHelpMessage();
        } else if ( taskName == tasks::BUILDALL ) {
            cout << helpmessage::buildAllHelpMessage();
        } else {
            cout << errors::TASK_NOT_RECOGNIZED << endl;
        }
    }
}
