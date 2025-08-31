
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
    CMD* mainCMD = ((ExecManager*)mgr)->getMainCMD();
    if ( mainCMD == nullptr )
        return false;
        
    bool isShowHelp = mainCMD->existsArg( "-h" );
    if ( !isShowHelp )
        isShowHelp = mainCMD->existsArg( "--help" );
    return isShowHelp;
}

bool MainCMDArgManager::isVerbose() {
    CMD* mainCMD = ((ExecManager*)mgr)->getMainCMD();
    if ( mainCMD == nullptr )
        return false;
        
    bool isVerbose = mainCMD->existsArg( "-v" );
    if ( !isVerbose )
        isVerbose = mainCMD->existsArg( "--verbose" );
    return isVerbose;
}

bool MainCMDArgManager::isNoResume() {
    CMD* mainCMD = ((ExecManager*)mgr)->getMainCMD();
    if ( mainCMD == nullptr )
        return false;
        
    return mainCMD->existsArg( "--no-resume" );
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
        return defaultTaskConfig->isVerbose();
    return this->isVerbose();
}

bool MainCMDArgManager::isShowCMDOutput( string taskName ) {
    MainScript* mainScript = ((ExecManager*)mgr)->getMainScript();
    if ( mainScript == nullptr )
        return consts::DEFAULT_SHOW_CMD_OUTPUT;

    DefaultTaskConfig* defaultTaskConfig = mainScript->getDefaultTaskConfig( taskName );    
    if ( defaultTaskConfig != nullptr )
        return defaultTaskConfig->isShowCMDOutput();
    return consts::DEFAULT_SHOW_CMD_OUTPUT;
}

bool MainCMDArgManager::isClean() {
    CMD* mainCMD = ((ExecManager*)mgr)->getMainCMD();
    if ( mainCMD == nullptr )
        return false;

    bool isClean = mainCMD->existsArg( tasks::CLEAN );
    bool isBuild = mainCMD->existsArg( tasks::BUILD );
    bool isBuildAll = mainCMD->existsArg( tasks::BUILDALL );
    bool isArchiveBuild = mainCMD->existsArg( tasks::ARCHIVEBUILD );
    bool isArchiveBuildAll = mainCMD->existsArg( tasks::ARCHIVEBUILDALL );    
    bool isTestBuild = mainCMD->existsArg( tasks::TESTBUILD );
    bool isTestBuildAll = mainCMD->existsArg( tasks::TESTBUILDALL );
    return isClean || isBuild || isBuildAll || isArchiveBuild || isArchiveBuildAll || isTestBuild || isTestBuildAll;
}

bool MainCMDArgManager::isCompile() {
    CMD* mainCMD = ((ExecManager*)mgr)->getMainCMD();
    if ( mainCMD == nullptr )
        return false;
    
    bool isCompile = mainCMD->existsArg( tasks::COMPILE );
    bool isBuild = mainCMD->existsArg( tasks::BUILD );
    bool isArchiveBuild = mainCMD->existsArg( tasks::ARCHIVEBUILD );
    bool isTestBuild = mainCMD->existsArg( tasks::TESTBUILD );
    return isCompile || isBuild || isArchiveBuild || isTestBuild;
}

bool MainCMDArgManager::isCompileAll() {
    CMD* mainCMD = ((ExecManager*)mgr)->getMainCMD();
    if ( mainCMD == nullptr )
        return false;
    
    bool isCompileAll = mainCMD->existsArg( tasks::COMPILEALL );
    bool isBuildAll = mainCMD->existsArg( tasks::BUILDALL );
    bool isArchiveBuildAll = mainCMD->existsArg( tasks::ARCHIVEBUILDALL );
    bool isTestBuildAll = mainCMD->existsArg( tasks::TESTBUILDALL );
    return isCompileAll || isBuildAll || isArchiveBuildAll || isTestBuildAll;
}

bool MainCMDArgManager::isLink() {
    CMD* mainCMD = ((ExecManager*)mgr)->getMainCMD();
    if ( mainCMD == nullptr )
        return false;
    
    bool isLink = mainCMD->existsArg( tasks::LINK );
    bool isBuild = mainCMD->existsArg( tasks::BUILD );
    bool isBuildAll = mainCMD->existsArg( tasks::BUILDALL );
    bool isTestBuild = mainCMD->existsArg( tasks::TESTBUILD );
    bool isTestBuildAll = mainCMD->existsArg( tasks::TESTBUILDALL );
    return isLink || isBuild || isBuildAll || isTestBuild || isTestBuildAll;
}

bool MainCMDArgManager::isArchive() {
    CMD* mainCMD = ((ExecManager*)mgr)->getMainCMD();
    if ( mainCMD == nullptr )
        return false;
    
    bool isArchive = mainCMD->existsArg( tasks::ARCHIVE );
    bool isArchiveBuild = mainCMD->existsArg( tasks::ARCHIVEBUILD );
    bool isArchiveBuildAll = mainCMD->existsArg( tasks::ARCHIVEBUILDALL );
    return isArchive || isArchiveBuild || isArchiveBuildAll;
}

bool MainCMDArgManager::isTest() {
    CMD* mainCMD = ((ExecManager*)mgr)->getMainCMD();
    if ( mainCMD == nullptr )
        return false;
    
    bool isTest = mainCMD->existsArg( tasks::TEST );
    bool isTestBuild = mainCMD->existsArg( tasks::TESTBUILD );
    bool isTestBuildAll = mainCMD->existsArg( tasks::TESTBUILDALL );
    return isTest || isTestBuild || isTestBuildAll;
}

bool MainCMDArgManager::isCopy() {
    CMD* mainCMD = ((ExecManager*)mgr)->getMainCMD();
    if ( mainCMD == nullptr )
        return false;
    
    bool isCopy = mainCMD->existsArg( tasks::COPY );
    bool isBuild = mainCMD->existsArg( tasks::BUILD );
    bool isBuildAll = mainCMD->existsArg( tasks::BUILDALL );
    bool isArchiveBuild = mainCMD->existsArg( tasks::ARCHIVEBUILD );
    bool isArchiveBuildAll = mainCMD->existsArg( tasks::ARCHIVEBUILDALL );
    bool isTestBuild = mainCMD->existsArg( tasks::TESTBUILD );
    bool isTestBuildAll = mainCMD->existsArg( tasks::TESTBUILDALL );
    return isCopy || isBuild || isBuildAll || isArchiveBuild || isArchiveBuildAll || isTestBuild || isTestBuildAll;
}

bool MainCMDArgManager::isBuild() {
    CMD* mainCMD = ((ExecManager*)mgr)->getMainCMD();
    if ( mainCMD == nullptr )
        return false;
    
    bool isBuild = mainCMD->existsArg( tasks::BUILD );
    return isBuild;
}

bool MainCMDArgManager::isBuildAll() {
    CMD* mainCMD = ((ExecManager*)mgr)->getMainCMD();
    if ( mainCMD == nullptr )
        return false;
    
    bool isBuildAll = mainCMD->existsArg( tasks::BUILDALL );
    return isBuildAll;
}

bool MainCMDArgManager::isArchiveBuild() {
    CMD* mainCMD = ((ExecManager*)mgr)->getMainCMD();
    if ( mainCMD == nullptr )
        return false;
    
    bool isArchiveBuild = mainCMD->existsArg( tasks::ARCHIVEBUILD );
    return isArchiveBuild;
}

bool MainCMDArgManager::isArchiveBuildAll() {
    CMD* mainCMD = ((ExecManager*)mgr)->getMainCMD();
    if ( mainCMD == nullptr )
        return false;
    
    bool isArchiveBuildAll = mainCMD->existsArg( tasks::ARCHIVEBUILDALL );
    return isArchiveBuildAll;
}

bool MainCMDArgManager::isTestBuild() {
    CMD* mainCMD = ((ExecManager*)mgr)->getMainCMD();
    if ( mainCMD == nullptr )
        return false;
    
    bool isTestBuild = mainCMD->existsArg( tasks::TESTBUILD );
    return isTestBuild;
}

bool MainCMDArgManager::isTestBuildAll() {
    CMD* mainCMD = ((ExecManager*)mgr)->getMainCMD();
    if ( mainCMD == nullptr )
        return false;
    
    bool isTestBuildAll = mainCMD->existsArg( tasks::TESTBUILDALL );
    return isTestBuildAll;
}