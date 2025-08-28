
#include "MainCMDArgManager.h"
#include "ExecManager.h"
#include "../darv/MainScript.h"
#include "../darv/CMD.h"

#include "../consts.h"

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
    return isClean || isBuild || isBuildAll;
}

bool MainCMDArgManager::isCompile() {
    CMD* mainCMD = ((ExecManager*)mgr)->getMainCMD();
    if ( mainCMD == nullptr )
        return false;
    
    bool isCompile = mainCMD->existsArg( tasks::COMPILE );
    bool isBuild = mainCMD->existsArg( tasks::BUILD );
    return isCompile || isBuild;
}

bool MainCMDArgManager::isCompileAll() {
    CMD* mainCMD = ((ExecManager*)mgr)->getMainCMD();
    if ( mainCMD == nullptr )
        return false;
    
    bool isCompileAll = mainCMD->existsArg( tasks::COMPILEALL );
    bool isBuildAll = mainCMD->existsArg( tasks::BUILDALL );
    return isCompileAll || isBuildAll;
}

bool MainCMDArgManager::isLink() {
    CMD* mainCMD = ((ExecManager*)mgr)->getMainCMD();
    if ( mainCMD == nullptr )
        return false;
    
    bool isLink = mainCMD->existsArg( tasks::LINK );
    bool isBuild = mainCMD->existsArg( tasks::BUILD );
    bool isBuildAll = mainCMD->existsArg( tasks::BUILDALL );
    return isLink || isBuild || isBuildAll;
}

bool MainCMDArgManager::isArchive() {
    CMD* mainCMD = ((ExecManager*)mgr)->getMainCMD();
    if ( mainCMD == nullptr )
        return false;
    
    bool isArchive = mainCMD->existsArg( tasks::ARCHIVE );
    return isArchive;
}

bool MainCMDArgManager::isCopy() {
    CMD* mainCMD = ((ExecManager*)mgr)->getMainCMD();
    if ( mainCMD == nullptr )
        return false;
    
    bool isCopy = mainCMD->existsArg( tasks::COPY );
    bool isBuild = mainCMD->existsArg( tasks::BUILD );
    bool isBuildAll = mainCMD->existsArg( tasks::BUILDALL );
    return isCopy || isBuild || isBuildAll;
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