
#include "ScriptPropertyManager.h"
#include "ExecManager.h"
#include "../io/io.h"

#include "../consts.h"

ScriptPropertyManager::ScriptPropertyManager( void* mgr ) {
    this->mgr = mgr;
}

string ScriptPropertyManager::getCompiler() {
    ExecManager* manager = (ExecManager*)mgr;
    MainScript* script = manager->getMainScript();

    string compiler = script->getPropertyValue( props::COMPILER );
    if ( compiler == "" )
        return consts::DEFAULT_COMPILER;
    return compiler; 
}

string ScriptPropertyManager::getArchiver() {
    ExecManager* manager = (ExecManager*)mgr;
    MainScript* script = manager->getMainScript();
    
    string archiver = script->getPropertyValue( props::ARCHIVER );
    if ( archiver == "" )
        return consts::DEFAULT_ARCHIVER;
    return archiver; 
}

string ScriptPropertyManager::getBaseDir() {
    ExecManager* manager = (ExecManager*)mgr;
    MainScript* script = manager->getMainScript();
    
    string basedir = script->getPropertyValue( props::BASE_DIR );
    return io::path::absoluteResolvePath( basedir );
}

string ScriptPropertyManager::getSrcDir() {
    ExecManager* manager = (ExecManager*)mgr;
    MainScript* script = manager->getMainScript();
    
    string srcDir = script->getPropertyValue( props::SRC_DIR );
    if ( srcDir == "" )
        return io::path::currentPath();
    return io::path::absoluteResolvePath( srcDir );
}

string ScriptPropertyManager::getTestDir() {
    ExecManager* manager = (ExecManager*)mgr;
    MainScript* script = manager->getMainScript();
    
    string testDir = script->getPropertyValue( props::TEST_DIR );
    if ( testDir == "" )
        return consts::DEFAULT_TEST_DIR;
    return io::path::absoluteResolvePath( testDir );
}

string ScriptPropertyManager::getBinDir() {
    ExecManager* manager = (ExecManager*)mgr;
    MainScript* script = manager->getMainScript();
    
    string binDir = script->getPropertyValue( props::BIN_DIR );
    if ( binDir == "" )
        return io::path::currentPath();
    return io::path::absoluteResolvePath( binDir );
}

string ScriptPropertyManager::getObjDir() {
    ExecManager* manager = (ExecManager*)mgr;
    MainScript* script = manager->getMainScript();
    
    string objDir = script->getPropertyValue( props::OBJ_DIR );
    if ( objDir == "" )
        return consts::DEFAULT_OBJ_DIR;
    return io::path::absoluteResolvePath( objDir );
}

string ScriptPropertyManager::getBuildDir() {
    ExecManager* manager = (ExecManager*)mgr;
    MainScript* script = manager->getMainScript();
    
    string buildDir = script->getPropertyValue( props::BUILD_DIR );
    if ( buildDir == "" )
        return consts::DEFAULT_BUILD_DIR;
    return io::path::absoluteResolvePath( buildDir );
}

string ScriptPropertyManager::getOutputFileName() {
    ExecManager* manager = (ExecManager*)mgr;
    MainScript* script = manager->getMainScript();
    
    return script->getPropertyValue( props::OUTPUT_FILE_NAME );
}

string ScriptPropertyManager::getBuildFiles() {
    ExecManager* manager = (ExecManager*)mgr;
    MainScript* script = manager->getMainScript();
    
    return script->getPropertyValue( props::BUILD_FILES );
}

string ScriptPropertyManager::getResourceFile() {
    ExecManager* manager = (ExecManager*)mgr;
    MainScript* script = manager->getMainScript();
    
    return script->getPropertyValue( props::RESOURCE_FILE );
}

string ScriptPropertyManager::getCompilerParams() {
    ExecManager* manager = (ExecManager*)mgr;
    MainScript* script = manager->getMainScript();
    
    return script->getPropertyValue( props::COMPILER_PARAMS );
}

string ScriptPropertyManager::getLinkerParams() {
    ExecManager* manager = (ExecManager*)mgr;
    MainScript* script = manager->getMainScript();
    
    return script->getPropertyValue( props::LINKER_PARAMS );
}

string ScriptPropertyManager::getArchiverParams() {
    ExecManager* manager = (ExecManager*)mgr;
    MainScript* script = manager->getMainScript();
    
    return script->getPropertyValue( props::ARCHIVER_PARAMS );
}

string ScriptPropertyManager::getLibDirs() {
    ExecManager* manager = (ExecManager*)mgr;
    MainScript* script = manager->getMainScript();
    
    return script->getPropertyValue( props::LIB_DIRS );
}

string ScriptPropertyManager::getIncludeDirs() {
    ExecManager* manager = (ExecManager*)mgr;
    MainScript* script = manager->getMainScript();
    
    return script->getPropertyValue( props::INCLUDE_DIRS );
}

string ScriptPropertyManager::getLibs() {
    ExecManager* manager = (ExecManager*)mgr;
    MainScript* script = manager->getMainScript();
    
    return script->getPropertyValue( props::LIBS );
}

string ScriptPropertyManager::getDefines() {
    ExecManager* manager = (ExecManager*)mgr;
    MainScript* script = manager->getMainScript();
    
    return script->getPropertyValue( props::DEFINES );
}

string ScriptPropertyManager::getTestCompilerParams() {
    ExecManager* manager = (ExecManager*)mgr;
    MainScript* script = manager->getMainScript();
    
    return script->getPropertyValue( props::TEST_COMPILER_PARAMS );
}

string ScriptPropertyManager::getTestLinkerParams() {
    ExecManager* manager = (ExecManager*)mgr;
    MainScript* script = manager->getMainScript();
    
    return script->getPropertyValue( props::TEST_LINKER_PARAMS );
}

string ScriptPropertyManager::getTestLibDirs() {
    ExecManager* manager = (ExecManager*)mgr;
    MainScript* script = manager->getMainScript();
    
    return script->getPropertyValue( props::TEST_LIB_DIRS );
}

string ScriptPropertyManager::getTestIncludeDirs() {
    ExecManager* manager = (ExecManager*)mgr;
    MainScript* script = manager->getMainScript();
    
    return script->getPropertyValue( props::TEST_INCLUDE_DIRS );
}

string ScriptPropertyManager::getTestLibs() {
    ExecManager* manager = (ExecManager*)mgr;
    MainScript* script = manager->getMainScript();
    
    return script->getPropertyValue( props::TEST_LIBS );
}

string ScriptPropertyManager::getTestDefines() {
    ExecManager* manager = (ExecManager*)mgr;
    MainScript* script = manager->getMainScript();
    
    return script->getPropertyValue( props::TEST_DEFINES );
}

string ScriptPropertyManager::getOutputDefFile() {
    ExecManager* manager = (ExecManager*)mgr;
    MainScript* script = manager->getMainScript();
    
    return script->getPropertyValue( props::OUTPUT_DEF_FILE );
}

string ScriptPropertyManager::getOutImplibFile() {
    ExecManager* manager = (ExecManager*)mgr;
    MainScript* script = manager->getMainScript();
    
    return script->getPropertyValue( props::OUT_IMPLIB_FILE );
}