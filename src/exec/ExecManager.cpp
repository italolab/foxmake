
#include "ExecManager.h"
#include "stexcept.h"
#include "cp/CPExec.h"
#include "rm/RMExec.h"
#include "cd/CDExec.h"
#include "mkdir/MKDirExec.h"
#include "echo/EchoExec.h"
#include "main/CleanTaskExec.h"
#include "main/CompileTaskExec.h"
#include "main/LinkTaskExec.h"
#include "main/CopyTaskExec.h"
#include "shcmd/ShellCMDExec.h"
#include "../inter/InterResult.h"
#include "../shell/shell.h"
#include "../io/io.h"
#include "../msg/messagebuilder.h"

#include "../error_messages.h"
#include "../consts.h"

#include <stdexcept>
#include <typeinfo>
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

using std::runtime_error;
using std::exception;

ExecManager::ExecManager() {
    mainCMD = nullptr;
    mainScript = new MainScript();
    interManager = new InterManager( this );

    sourceCodeManager = new SourceCodeManager( consts::SOURCE_FILE_EXTENSIONS, consts::HEADER_FILE_EXTENSIONS );

    mainExec = new MainExec();

    execsMap[ cmds::CP ] = new CPExec();
    execsMap[ cmds::RM ] = new RMExec();
    execsMap[ cmds::CD ] = new CDExec();
    execsMap[ cmds::MKDIR ] = new MKDirExec();
    execsMap[ cmds::ECHO ] = new EchoExec();

    taskExecsMap[ tasks::CLEAN ] = new CleanTaskExec();
    taskExecsMap[ tasks::COMPILE ] = new CompileTaskExec();
    taskExecsMap[ tasks::LINK ] = new LinkTaskExec();
    taskExecsMap[ tasks::COPY ] = new CopyTaskExec();

    shellCMDExec = new ShellCMDExec();
}

ExecManager::~ExecManager() {
    delete mainScript;

    delete interManager;
    delete sourceCodeManager;

    delete mainExec;

    for( const auto& pair : execsMap )
        delete pair.second;
    for( const auto& pair : taskExecsMap )
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
        cerr << e.message() << endl;
    } catch ( const exception& e ) {
        cerr << e.what() << endl;
    }
}

void ExecManager::executaStatement( Statement* st ) {
    if ( dynamic_cast<CMD*>( st ) ) {
        CMD* cmd = (CMD*)st;

        Exec* exec = execsMap[ cmd->getName() ];
        if ( exec == nullptr )
            throw runtime_error( "Executor de comando nao encontrado pelo nome: \"" + cmd->getName() + "\"" );

        exec->exec( cmd, this );
    } else if ( dynamic_cast<ShellCMD*>( st ) ) {
        shellCMDExec->exec( (ShellCMD*)st, this );
    } else {
        stringstream ss;
        ss << "Instrucao de tipo invalido." << endl;
        ss << "Linha=\"" << st->getLine() << endl;
        ss << "Tipo=\"" << typeid( st ).name() << "\"" << endl;
        throw runtime_error( ss.str() );
    }
}

void ExecManager::executaTask( string taskName ) {
    TaskExec* exec = taskExecsMap[ taskName ];
    if ( exec == nullptr )
        throw runtime_error( "Executor de tarefa nao encontrado pelo nome: \"" + taskName + "\"" );
    exec->exec( this );
}

void ExecManager::executaUserTaskIfExists( string taskName, bool beforeFlag ) {
    Task* task = mainScript->getTask( taskName, beforeFlag );
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

bool ExecManager::isHelp() {
    if ( mainCMD == nullptr )
        return false;
        
    bool isShowHelp = mainCMD->existsArg( "-h" );
    if ( !isShowHelp )
        isShowHelp = mainCMD->existsArg( "--help" );
    return isShowHelp;
}

bool ExecManager::isVerbose() {
    if ( mainCMD == nullptr )
        return false;
        
    bool isVerbose = mainCMD->existsArg( "-v" );
    if ( !isVerbose )
        isVerbose = mainCMD->existsArg( "--verbose" );
    return isVerbose;
}

bool ExecManager::isNoResume() {
    if ( mainCMD == nullptr )
        return false;
        
    return mainCMD->existsArg( "--no-resume" );
}

vector<string> ExecManager::validCMDNames() {
    vector<string> names;
    for( const auto& pair : execsMap )
        names.push_back( pair.first );
    return names;
}

vector<string> ExecManager::validPropNames() {
    return props::VALID_NAMES;
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

InterManager* ExecManager::getInterManager() {
    return interManager;
}
