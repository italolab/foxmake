
#include "MainCMDArgManager.h"
#include "ExecManager.h"
#include "../darv/MainScript.h"
#include "../darv/CMD.h"

#include "../consts.h"

/*
Classe responsável por prover métodos para o acesso a propriedades do sistema. 
Exemplo:

Acessar o valor de showCMDOutput. Isto é, a configuração de tarefas default 
pode configurar essa propriedade e, caso a propriedade seja definida. Por exemplo, 
com a instrução: "task compile noshowoutput;", o método retorna valor false. Se definida 
com "showoutput", o método retorna true e se não houver a definição, é retornado o valor 
padrão armazenado na constante DEFAULT_SHOW_CMD_OUTPUT.

O mesmo vale para o acesso a propriedade verbose. Se definida como configuração de 
uma tarefa default, o valor correspondente é retornado, caso contrário, se o comando 
principal receber a opção "--verbose" ou "-v", retorna true, caso contrário, retorna 
false.

Essa classe fornece métodos, também, sobre se uma determinada tarefa deve ser executada. 
Exemplo: 
    Se no comando principal for informada apenas a tarefa "buildall", então os 
    métodos: isClean, isCompileAll, isLink, isCopy e isBuildAll retornam true, os demais 
    retornam false.

    Se for informado "clean" "compile", então os métodos: isClean e isCompile retornam 
    true e, o restante, retorna false.
*/

MainCMDArgManager::MainCMDArgManager( void* mgr ) {
    this->mgr = mgr;
}

bool MainCMDArgManager::isHelp() {
    ExecCMD* mainExecCMD = ((ExecManager*)mgr)->getMainExecCMD();
    if ( mainExecCMD == nullptr )
        return false;
        
    bool isShowHelp = mainExecCMD->existsArg( "-h" );
    if ( !isShowHelp )
        isShowHelp = mainExecCMD->existsArg( "--help" );
    return isShowHelp;
}

bool MainCMDArgManager::isVerbose() {
    ExecCMD* mainExecCMD = ((ExecManager*)mgr)->getMainExecCMD();
    if ( mainExecCMD == nullptr )
        return false;
        
    bool isVerbose = mainExecCMD->existsArg( "-v" );
    if ( !isVerbose )
        isVerbose = mainExecCMD->existsArg( "--verbose" );
    return isVerbose;
}

bool MainCMDArgManager::isNoResume() {
    ExecCMD* mainExecCMD = ((ExecManager*)mgr)->getMainExecCMD();
    if ( mainExecCMD == nullptr )
        return false;
        
    return mainExecCMD->existsArg( "--no-resume" );
}

bool MainCMDArgManager::isVerbose( GenericCMD* cmd ) {
    Statement* task = cmd->getTask();    
    if ( task == nullptr )
        return this->isVerbose();
    return this->isVerbose( ((Task*)task)->getName() );
}

bool MainCMDArgManager::isShowCMDOutput( GenericCMD* cmd ) {
    Statement* task = cmd->getTask();
    if ( task == nullptr )
        return consts::DEFAULT_SHOW_CMD_OUTPUT;
    return this->isShowCMDOutput( ((Task*)task)->getName() );
}

bool MainCMDArgManager::isVerbose( string taskName ) {
    MainScript* mainScript = ((ExecManager*)mgr)->getMainScript();
    if ( mainScript == nullptr )
        return this->isVerbose();

    DefaultTaskConfig* defaultTaskConfig = mainScript->getDefaultTaskConfig( taskName );    
    if ( defaultTaskConfig != nullptr )
        if ( defaultTaskConfig->isVerboseDefined() )
            return defaultTaskConfig->isVerbose();
    return this->isVerbose();
}

bool MainCMDArgManager::isShowCMDOutput( string taskName ) {
    MainScript* mainScript = ((ExecManager*)mgr)->getMainScript();
    if ( mainScript == nullptr )
        return consts::DEFAULT_SHOW_CMD_OUTPUT;

    DefaultTaskConfig* defaultTaskConfig = mainScript->getDefaultTaskConfig( taskName );    
    if ( defaultTaskConfig != nullptr )
        if ( defaultTaskConfig->isShowCMDOutputDefined() )
            return defaultTaskConfig->isShowCMDOutput();
    return consts::DEFAULT_SHOW_CMD_OUTPUT;
}

bool MainCMDArgManager::isClean() {
    ExecCMD* mainExecCMD = ((ExecManager*)mgr)->getMainExecCMD();
    if ( mainExecCMD == nullptr )
        return false;

    bool isClean = mainExecCMD->existsArg( tasks::CLEAN );
    bool isBuild = mainExecCMD->existsArg( tasks::BUILD );
    bool isBuildAll = mainExecCMD->existsArg( tasks::BUILDALL );
    bool isArchiveBuild = mainExecCMD->existsArg( tasks::ARCHIVEBUILD );
    bool isArchiveBuildAll = mainExecCMD->existsArg( tasks::ARCHIVEBUILDALL );    
    bool isTestBuild = mainExecCMD->existsArg( tasks::TESTBUILD );
    bool isTestBuildAll = mainExecCMD->existsArg( tasks::TESTBUILDALL );
    return isClean || isBuild || isBuildAll || isArchiveBuild || isArchiveBuildAll || isTestBuild || isTestBuildAll;
}

bool MainCMDArgManager::isCompile() {
    ExecCMD* mainExecCMD = ((ExecManager*)mgr)->getMainExecCMD();
    if ( mainExecCMD == nullptr )
        return false;
    
    bool isCompile = mainExecCMD->existsArg( tasks::COMPILE );
    bool isBuild = mainExecCMD->existsArg( tasks::BUILD );
    bool isArchiveBuild = mainExecCMD->existsArg( tasks::ARCHIVEBUILD );
    bool isTestBuild = mainExecCMD->existsArg( tasks::TESTBUILD );
    return isCompile || isBuild || isArchiveBuild || isTestBuild;
}

bool MainCMDArgManager::isCompileAll() {
    ExecCMD* mainExecCMD = ((ExecManager*)mgr)->getMainExecCMD();
    if ( mainExecCMD == nullptr )
        return false;
    
    bool isCompileAll = mainExecCMD->existsArg( tasks::COMPILEALL );
    bool isBuildAll = mainExecCMD->existsArg( tasks::BUILDALL );
    bool isArchiveBuildAll = mainExecCMD->existsArg( tasks::ARCHIVEBUILDALL );
    bool isTestBuildAll = mainExecCMD->existsArg( tasks::TESTBUILDALL );
    return isCompileAll || isBuildAll || isArchiveBuildAll || isTestBuildAll;
}

bool MainCMDArgManager::isLink() {
    ExecCMD* mainExecCMD = ((ExecManager*)mgr)->getMainExecCMD();
    if ( mainExecCMD == nullptr )
        return false;
    
    bool isLink = mainExecCMD->existsArg( tasks::LINK );
    bool isBuild = mainExecCMD->existsArg( tasks::BUILD );
    bool isBuildAll = mainExecCMD->existsArg( tasks::BUILDALL );
    bool isTestBuild = mainExecCMD->existsArg( tasks::TESTBUILD );
    bool isTestBuildAll = mainExecCMD->existsArg( tasks::TESTBUILDALL );
    return isLink || isBuild || isBuildAll || isTestBuild || isTestBuildAll;
}

bool MainCMDArgManager::isArchive() {
    ExecCMD* mainExecCMD = ((ExecManager*)mgr)->getMainExecCMD();
    if ( mainExecCMD == nullptr )
        return false;
    
    bool isArchive = mainExecCMD->existsArg( tasks::ARCHIVE );
    bool isArchiveBuild = mainExecCMD->existsArg( tasks::ARCHIVEBUILD );
    bool isArchiveBuildAll = mainExecCMD->existsArg( tasks::ARCHIVEBUILDALL );
    return isArchive || isArchiveBuild || isArchiveBuildAll;
}

bool MainCMDArgManager::isTest() {
    ExecCMD* mainExecCMD = ((ExecManager*)mgr)->getMainExecCMD();
    if ( mainExecCMD == nullptr )
        return false;
    
    bool isTest = mainExecCMD->existsArg( tasks::TEST );
    bool isTestBuild = mainExecCMD->existsArg( tasks::TESTBUILD );
    bool isTestBuildAll = mainExecCMD->existsArg( tasks::TESTBUILDALL );
    return isTest || isTestBuild || isTestBuildAll;
}

bool MainCMDArgManager::isCopy() {
    ExecCMD* mainExecCMD = ((ExecManager*)mgr)->getMainExecCMD();
    if ( mainExecCMD == nullptr )
        return false;
    
    bool isCopy = mainExecCMD->existsArg( tasks::COPY );
    bool isBuild = mainExecCMD->existsArg( tasks::BUILD );
    bool isBuildAll = mainExecCMD->existsArg( tasks::BUILDALL );
    bool isArchiveBuild = mainExecCMD->existsArg( tasks::ARCHIVEBUILD );
    bool isArchiveBuildAll = mainExecCMD->existsArg( tasks::ARCHIVEBUILDALL );
    bool isTestBuild = mainExecCMD->existsArg( tasks::TESTBUILD );
    bool isTestBuildAll = mainExecCMD->existsArg( tasks::TESTBUILDALL );
    return isCopy || isBuild || isBuildAll || isArchiveBuild || isArchiveBuildAll || isTestBuild || isTestBuildAll;
}

bool MainCMDArgManager::isBuild() {
    ExecCMD* mainExecCMD = ((ExecManager*)mgr)->getMainExecCMD();
    if ( mainExecCMD == nullptr )
        return false;
    
    bool isBuild = mainExecCMD->existsArg( tasks::BUILD );
    return isBuild;
}

bool MainCMDArgManager::isBuildAll() {
    ExecCMD* mainExecCMD = ((ExecManager*)mgr)->getMainExecCMD();
    if ( mainExecCMD == nullptr )
        return false;
    
    bool isBuildAll = mainExecCMD->existsArg( tasks::BUILDALL );
    return isBuildAll;
}

bool MainCMDArgManager::isArchiveBuild() {
    ExecCMD* mainExecCMD = ((ExecManager*)mgr)->getMainExecCMD();
    if ( mainExecCMD == nullptr )
        return false;
    
    bool isArchiveBuild = mainExecCMD->existsArg( tasks::ARCHIVEBUILD );
    return isArchiveBuild;
}

bool MainCMDArgManager::isArchiveBuildAll() {
    ExecCMD* mainExecCMD = ((ExecManager*)mgr)->getMainExecCMD();
    if ( mainExecCMD == nullptr )
        return false;
    
    bool isArchiveBuildAll = mainExecCMD->existsArg( tasks::ARCHIVEBUILDALL );
    return isArchiveBuildAll;
}

bool MainCMDArgManager::isTestBuild() {
    ExecCMD* mainExecCMD = ((ExecManager*)mgr)->getMainExecCMD();
    if ( mainExecCMD == nullptr )
        return false;
    
    bool isTestBuild = mainExecCMD->existsArg( tasks::TESTBUILD );
    return isTestBuild;
}

bool MainCMDArgManager::isTestBuildAll() {
    ExecCMD* mainExecCMD = ((ExecManager*)mgr)->getMainExecCMD();
    if ( mainExecCMD == nullptr )
        return false;
    
    bool isTestBuildAll = mainExecCMD->existsArg( tasks::TESTBUILDALL );
    return isTestBuildAll;
}