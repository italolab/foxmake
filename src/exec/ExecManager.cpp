
#include "ExecManager.h"
#include "stexcept.h"
#include "cp/CPExec.h"
#include "rm/RMExec.h"
#include "cd/CDExec.h"
#include "mkdir/MKDirExec.h"
#include "echo/EchoExec.h"
#include "shcmd/ShellCMDExec.h"
#include "../darv/DefaultTaskConfig.h"
#include "../darv/Task.h"
#include "../darv/GenericCMD.h"
#include "../inter/InterResult.h"
#include "../shell/shell.h"
#include "../io/io.h"
#include "../msg/messagebuilder.h"

#include "../error_messages.h"
#include "../consts.h"

#include <stdexcept>
#include <typeinfo>

using std::runtime_error;
using std::exception;

ExecManager::ExecManager() {
    mainCMD = nullptr;
    mainScript = new MainScript();

    mainCMDArgManager = new MainCMDArgManager( this );
    interManager = new InterManager( this );
    sourceCodeManager = new SourceCodeManager( consts::SOURCE_FILE_EXTENSIONS, consts::HEADER_FILE_EXTENSIONS );
    testSourceCodeManager = new SourceCodeManager( consts::SOURCE_FILE_EXTENSIONS, consts::HEADER_FILE_EXTENSIONS );

    mainExec = new MainExec();

    execsMap[ cmds::CP ] = new CPExec();
    execsMap[ cmds::RM ] = new RMExec();
    execsMap[ cmds::CD ] = new CDExec();
    execsMap[ cmds::MKDIR ] = new MKDirExec();
    execsMap[ cmds::ECHO ] = new EchoExec();

    shellCMDExec = new ShellCMDExec();
}

ExecManager::~ExecManager() {
    delete mainScript;

    delete interManager;
    delete sourceCodeManager;

    delete mainExec;

    for( const auto& pair : execsMap )
        delete pair.second;

    delete shellCMDExec;
}

void ExecManager::exec( int argc, char* argv[] ) {
    try {
        InterResult* result = interManager->interpretsMainCMD( argc, argv );
        if ( !result->isInterpreted() ) {
            messagebuilder b( errors::ERROR_IN_MAIN_CMD );
            b << result->getErrorMsg();
            throw runtime_error( b.str() );
        }

        mainCMD = (CMD*)result->getStatement();

        delete result;

        mainExec->exec( mainCMD, this );
    } catch ( const st_error& e ) {
        e.printMessage( out );
    } catch ( const exception& e ) {
        out << output::red( e.what() ) << "\n";
    }
}

void ExecManager::executaStatement( Statement* st ) {
    if ( dynamic_cast<CMD*>( st ) ) {
        CMD* cmd = (CMD*)st;

        Exec* exec = execsMap[ cmd->getName() ];
        if ( exec == nullptr ) {
            messagebuilder b( errors::runtime::CMD_EXECUTOR_NOT_FOUND );
            b << cmd->getName();
            throw runtime_error( b.str() );
        }

        exec->exec( cmd, this );
    } else if ( dynamic_cast<ShellCMD*>( st ) ) {
        shellCMDExec->exec( (ShellCMD*)st, this );
    } else {
        messagebuilder b( errors::runtime::INVALID_STATEMENT_TYPE );
        b << st->getLine();
        b << typeid( st ).name();
        throw runtime_error( b.str() );
    }
}

void ExecManager::executaUserTaskIfExists( string taskName, TaskExecution taskExecution ) {
    Task* task = mainScript->getTask( taskName, taskExecution );
    if ( task != nullptr ) {
        int len = task->getStatementsLength();
        for( int i = 0; i < len; i++ ) {
            Statement* st = task->getStatementByIndex( i );
            this->executaStatement( st );
        }
    }
}

bool ExecManager::isDefaultTask( string taskName ) {
    vector<string> defaultTasks = tasks::DEFAULT_TASKS;
    for( string name : defaultTasks )
        if ( name == taskName )
            return true;
    return false;
}

bool ExecManager::isValidProp( string propName ) {
    vector<string> validProps = props::VALID_NAMES;
    for( string name : validProps )
        if ( name == propName )
            return true;
    return false;
}

bool ExecManager::isValidCMD( string cmdName ) {
    vector<string> names;
    for( const auto& pair : execsMap )
        if ( pair.first == cmdName )
            return true;
    return false;
}

MainExec* ExecManager::getMainExec() {
    return mainExec;
}

MainScript* ExecManager::getMainScript() {
    return mainScript;
}

CMD* ExecManager::getMainCMD() {
    return mainCMD;
}

SourceCodeManager* ExecManager::getSourceCodeManager() {
    return sourceCodeManager;
}

SourceCodeManager* ExecManager::getTestSourceCodeManager() {
    return testSourceCodeManager;
}

MainCMDArgManager* ExecManager::getMainCMDArgManager() {
    return mainCMDArgManager;
}

InterManager* ExecManager::getInterManager() {
    return interManager;
}
