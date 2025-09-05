
#include "MainCMDInterpreter.h"
#include "../ExecManager.h"
#include "../stexcept.h"
#include "../../inter/InterManager.h"
#include "../../darv/MainScript.h"
#include "../../darv/CMD.h"
#include "../../io/io.h"
#include "../../util/strutil.h"
#include "../../shell/shell.h"
#include "../../msg/messagebuilder.h"

#include "../../consts.h"
#include "../../error_messages.h"
#include "../../info_messages.h"

#include <iostream>
using std::endl;

/*
Classe responsável por ler e setar workingDir e cbuildFile, interpretar 
o script principal, carregando toda a arvore de derivação, carregar as 
variáveis e propriedades definidas no comando principal com "-var" e "-prop" e 
validar o comando.

Para validar o comando principal, é verificada cada tarefa informada no comando. Se, após 
a interpretação do script e geração da arvore de derivação, alguma tarefa informada 
no comando principal não for, nem tarefa default, nem estiver definida no script, então a 
validação falha.

Exemplo:
    Informada a tarefa "executar". Ela não é uma tarefa default executada pelo sistema e, 
    caso não tenha sido definida no arquivo de configurações, também não é uma tarefa 
    de usuário. Logo, é uma tarefa desconhecida e o sistema informa isso para o usuário.
*/

void MainCMDInterpreter::configureAndInterpretsAndValidate( void* mgr ) {
    bool workingDirFound = false;
    bool scriptFileFound = false;

    this->configure( workingDirFound, scriptFileFound, mgr );
    this->interpretsMainScript( workingDirFound, scriptFileFound, mgr );
    this->validaMainCMD( mgr );
}

void MainCMDInterpreter::configure( bool& workingDirFound, bool& scriptFileFound, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    CMD* mainCMD = manager->getMainCMD();

    Output& out = manager->out;
    bool isVerbose = manager->getMainCMDArgManager()->isVerbose();

    workingDir = mainCMD->getPropertyValue( "--working-dir" );
    scriptFile = mainCMD->getPropertyValue( "--cbuild-file" );

    if ( workingDir != "" ) {
        workingDir = io::path::absoluteResolvePath( workingDir );
        workingDir = io::path::removeSeparatorFromDirIfNeed( workingDir );
        shell::setWorkingDir( workingDir );

        workingDirFound = true;
    } else {
        if ( scriptFile != "" ) {
            workingDir = io::path::dirPath( io::path::absoluteResolvePath( scriptFile ) );
            workingDir = io::path::removeSeparatorFromDirIfNeed( workingDir );

            scriptFile = io::path::fileOrDirName( scriptFile );
            shell::setWorkingDir( workingDir );
        } else {
            workingDir = shell::getWorkingDir();
        }

        workingDirFound = false;
    }

    if ( scriptFile == "" )
        scriptFile = consts::DEFAULT_SCRIPT_FILE_NAME;

    scriptFile = io::path::absoluteResolvePath( scriptFile );

    if ( isVerbose ) {
        messagebuilder b( infos::CBUILD_FILE );
        b << scriptFile;
        out << b.str() << endl;
    }

    scriptFileFound = true;

    if ( !io::fileExists( scriptFile ) ) {
        messagebuilder b2( errors::SCRIPT_FILE_NOT_FOUND );
        b2 << scriptFile;
        out << output::green( b2.str() ) << endl;

        if ( !workingDirFound )
            throw st_error( nullptr, errors::NO_SCRIPT_FILE_AND_NO_WORKING_DIR );

        scriptFileFound = false;
    }
}

void MainCMDInterpreter::interpretsMainScript( bool workingDirFound, bool scriptFileFound, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    InterManager* interManager = manager->getInterManager();
    MainScript* mainScript = manager->getMainScript();

    Output& out = manager->out;
    bool isVerbose = manager->getMainCMDArgManager()->isVerbose();

    this->loadProperties( mgr );
    this->loadVariables( mgr );

    mainScript->putLocalVar( "main_config_file", scriptFile );
    mainScript->putLocalVar( "working_dir", workingDir );

    if ( scriptFileFound ) {
        InterResult* result = interManager->interpretsMainScript( mainScript, scriptFile );
        if ( !result->isInterpreted() )
            throw st_error( result );

        delete result;
    }

    string basedir = mainScript->getPropertyValue( props::BASE_DIR );
    if ( basedir != "" ) {
        basedir = io::path::absoluteResolvePath( basedir );
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
        out << b2.str() << endl;
    }
}

void MainCMDInterpreter::validaMainCMD( void* mgr ) {
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

void MainCMDInterpreter::loadProperties( void* mgr ) {
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

void MainCMDInterpreter::loadVariables( void* mgr ) {
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