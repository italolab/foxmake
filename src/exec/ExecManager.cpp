
#include "ExecManager.h"
#include "stexcept.h"
#include "../darv/DefaultTaskConfig.h"
#include "../darv/Task.h"
#include "../darv/GenericCMD.h"
#include "../darv/CallCMD.h"
#include "../darv/IF.h"
#include "../darv/VarAttr.h"
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
    mainExecCMD = nullptr;

    mainScript = new MainScript();

    mainCMDArgManager = new MainCMDArgManager( this );
    scriptPropertyManager = new ScriptPropertyManager( this );

    interManager = new InterManager( this );
    sourceCodeManager = new SourceCodeManager( consts::SOURCE_FILE_EXTENSIONS, consts::HEADER_FILE_EXTENSIONS );
    testSourceCodeManager = new SourceCodeManager( consts::SOURCE_FILE_EXTENSIONS, consts::HEADER_FILE_EXTENSIONS );

    mainExec = new MainExec();

    validCMDNames.push_back( "cd" );
    validCMDNames.push_back( "cp" );
    validCMDNames.push_back( "rm" );
    validCMDNames.push_back( "mkdir" );
    validCMDNames.push_back( "echo" );
    validCMDNames.push_back( "call" );

    cmdExec = new CMDExec();
    shellCMDExec = new ShellCMDLineExec();
    varAttrExec = new VarAttrExec();
    ifExec = new IFExec();
    callExec = new CallExec();
}

ExecManager::~ExecManager() {
    delete mainExecCMD;
    delete mainScript;

    delete mainCMDArgManager;
    delete scriptPropertyManager;

    delete interManager;
    delete sourceCodeManager;

    delete mainExec;

    delete cmdExec;
    delete shellCMDExec;
    delete varAttrExec;
    delete ifExec;
    delete callExec;
}

void ExecManager::exec( int argc, char* argv[] ) {
    try {
        InterResult* result = interManager->interpretsMainCMD( argc, argv );
        if ( !result->isInterpreted() ) {
            messagebuilder b( errors::ERROR_IN_MAIN_CMD );
            b << result->getErrorMsg();
            throw runtime_error( b.str() );
        }

        CMD* mainCMD = (CMD*)result->getStatement();
        mainExecCMD = new ExecCMD( mainCMD );

        delete result;

        mainExec->exec( this );
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
            callExec->exec( (CallCMD*)cmd, this );
        } else {
            cmdExec->exec( cmd, this );
        }
    } else if ( dynamic_cast<ShellCMDLine*>( st ) ) {
        shellCMDExec->exec( (ShellCMDLine*)st, this );
    } else if ( dynamic_cast<IF*>( st ) ) {
        ifExec->exec( (IF*)st, this );
    } else if ( dynamic_cast<VarAttr*>( st ) ) {
        varAttrExec->exec( (VarAttr*)st, this );
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

ExecCMD* ExecManager::getMainExecCMD() {
    return mainExecCMD;
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
