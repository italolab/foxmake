
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
    return isLink || isBuild || isBuildAll;
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