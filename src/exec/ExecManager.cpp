
#include "ExecManager.h"
#include "stexcept.h"
#include "../darv/DefaultTaskConfig.h"
#include "../darv/Task.h"
#include "../darv/GenericCMD.h"
#include "../darv/CallCMD.h"
#include "../darv/IF.h"
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
    scriptPropertyManager = new ScriptPropertyManager( this );

    interManager = new InterManager( this );
    sourceCodeManager = new SourceCodeManager( consts::SOURCE_FILE_EXTENSIONS, consts::HEADER_FILE_EXTENSIONS );
    testSourceCodeManager = new SourceCodeManager( consts::SOURCE_FILE_EXTENSIONS, consts::HEADER_FILE_EXTENSIONS );

    mainExec = new MainExec();

    cpExec = new CPExec();
    rmExec = new RMExec();
    cdExec = new CDExec();
    mkdirExec = new MKDirExec();
    echoExec = new EchoExec();

    validCMDNames.push_back( "cd" );
    validCMDNames.push_back( "cp" );
    validCMDNames.push_back( "rm" );
    validCMDNames.push_back( "mkdir" );
    validCMDNames.push_back( "echo" );
    validCMDNames.push_back( "call" );

    shellCMDExec = new ShellCMDLineExec();
}

ExecManager::~ExecManager() {
    delete mainScript;

    delete mainCMDArgManager;
    delete scriptPropertyManager;

    delete interManager;
    delete sourceCodeManager;

    delete mainExec;

    delete cdExec;
    delete cpExec;
    delete rmExec;
    delete echoExec;
    delete mkdirExec;
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

void ExecManager::executeBlockStatements( Block* block ) {
    int len = block->getStatementsLength();
    for( int i = 0; i < len; i++ ) {
        Statement* st = block->getStatementByIndex( i );
        this->executeStatement( st );
    }
}

void ExecManager::executeStatement( Statement* st ) {
    if ( dynamic_cast<CMD*>( st ) ) {
        CMD* cmd = (CMD*)st;
        
        if ( dynamic_cast<CallCMD*>( cmd ) ) {
            CallCMD* callCMD = (CallCMD*)cmd;
            Proc* proc = callCMD->getProc();
            if ( proc == nullptr ) {
                messagebuilder b ( errors::runtime::NULL_PROC );
                b << __func__;
                throw runtime_error( b.str() );
            }
            this->executeBlockStatements( proc );
        } else {
            string cmdName = cmd->getName();
            if ( cmdName == "cd" ) {
                cdExec->exec( cmd, this );
            } else if ( cmdName == "cp" ) {
                cpExec->exec( cmd, this );
            } else if ( cmdName == "rm" ) {
                rmExec->exec( cmd, this );
            } else if ( cmdName == "echo" ) {
                echoExec->exec( cmd, this );
            } else if ( cmdName == "mkdir" ) {
                mkdirExec->exec( cmd, this );
            } else {
                messagebuilder b( errors::runtime::CMD_EXECUTOR_NOT_FOUND );
                b << cmd->getName();
                throw runtime_error( b.str() );
            }
        }
    } else if ( dynamic_cast<ShellCMDLine*>( st ) ) {
        shellCMDExec->exec( (ShellCMDLine*)st, this );
    } else if ( dynamic_cast<IF*>( st ) ) {
        IF* ifst = (IF*)st;
        if ( ifst->getConditionValue() ) {
            this->executeStatement( ifst->getThenStatement() );
        } else {
            this->executeStatement( ifst->getElseStatement() );
        }   
    } else if ( dynamic_cast<Block*>( st ) ) {
        this->executeBlockStatements( (Block*)st );     
    } else {
        messagebuilder b( errors::runtime::INVALID_STATEMENT_TYPE );
        b << st->getLine();
        b << typeid( st ).name();
        throw runtime_error( b.str() );
    }
}

void ExecManager::executeUserTaskIfExists( string taskName, TaskExecution taskExecution ) {
    Task* task = mainScript->getTask( taskName, taskExecution );
    if ( task != nullptr )
        this->executeBlockStatements( task );
}

bool ExecManager::executeProc( string procName ) {
    Proc* proc = mainScript->getProc( procName );
    if ( proc != nullptr ) {
        this->executeBlockStatements( proc );
        return true;
    }
    return false;
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
    for( string validCMDName : validCMDNames )
        if ( cmdName == validCMDName )
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

ScriptPropertyManager* ExecManager::getScriptPropManager() {
    return scriptPropertyManager;
}

InterManager* ExecManager::getInterManager() {
    return interManager;
}
