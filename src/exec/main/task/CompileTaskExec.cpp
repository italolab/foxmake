
#include "CompileTaskExec.h"
#include "../../ExecManager.h"
#include "../../stexcept.h"
#include "../../../compiler/Compiler.h"
#include "../../../darv/MainScript.h"
#include "../../../shell/shell.h"
#include "../../../io/io.h"
#include "../../../sourcecode/SourceCodeManager.h"
#include "../../../util/strutil.h"
#include "../../../output/output.h"
#include "../../../msg/messagebuilder.h"

#include "../../../error_messages.h"
#include "../../../info_messages.h"
#include "../../../consts.h"

#include <sstream>
#include <stdexcept>

using std::stringstream;
using std::endl;

/*
Se a propriedade "output.file.name" for definida, os arquivos de código fonte 
da pasta de source code são compilados.

Se a propriedade "test.dir" for definida, os arquivos de código fonte da pasta 
de testes são compilados.
*/

void CompileTaskExec::exec( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    SourceCodeManager* sourceCodeManager = manager->getSourceCodeManager();
    SourceCodeManager* testSourceCodeManager = manager->getTestSourceCodeManager();
    ScriptPropertyManager* scriptPropManager = manager->getScriptPropManager();

    bool isCompileAll = manager->getMainCMDArgManager()->isCompileAll();

    bool isVerbose;
    bool isShowCMDOutput;
    if ( isCompileAll ) {
        isVerbose = manager->getMainCMDArgManager()->isVerbose( tasks::COMPILEALL );
        isShowCMDOutput = manager->getMainCMDArgManager()->isShowCMDOutput( tasks::COMPILEALL );
    } else {
        isVerbose = manager->getMainCMDArgManager()->isVerbose( tasks::COMPILE );
        isShowCMDOutput = manager->getMainCMDArgManager()->isShowCMDOutput( tasks::COMPILE );
    }

    Output& out = manager->out;
    bool isNoResume = manager->getMainCMDArgManager()->isNoResume();

    if ( isVerbose )
        out << endl;
        
    if ( !isNoResume || isVerbose ) {
        if ( isCompileAll ) {
            out << infos::EXECUTING << " " << output::green( tasks::COMPILEALL ) << "..." << endl;
        } else {
            out << infos::EXECUTING << " " << output::green( tasks::COMPILE ) << "..." << endl;
        }
    }

    if ( isCompileAll )
        manager->executeUserTaskIfExists( tasks::COMPILEALL, TaskExecution::BEFORE );
    else manager->executeUserTaskIfExists( tasks::COMPILE, TaskExecution::BEFORE );

    string compiler = scriptPropManager->getCompiler();
    string exeFileName = scriptPropManager->getOutputFileName();

    string binDir = scriptPropManager->getBinDir();
    string objDir = scriptPropManager->getObjDir();
    string testDir = scriptPropManager->getTestDir();
    string srcDir = scriptPropManager->getSrcDir();

    binDir = io::path::addSeparatorIfNeed( binDir );
    objDir = io::path::addSeparatorIfNeed( objDir );

    this->appCreateDirs( binDir, manager );
    this->appCreateDirs( objDir, manager );

    if ( compiler == "" )
        compiler = consts::DEFAULT_COMPILER;

    vector<TCompilation*> filesToCompile;

    this->loadFilesToCompile( filesToCompile, mgr );

    Shell* shell = new Shell( out );
    shell->setVerbose( isVerbose );
    shell->setShowOutput( isShowCMDOutput );

    int i = 0;
    for( TCompilation* compilation : filesToCompile ) {
        Compiler* comp = new Compiler();
        comp->setCompiler( compiler );
        comp->setCompilerParams( compilation->compilerParams );
        comp->setDefines( compilation->defines );
        comp->setIncludeDirs( compilation->includeDirs );
        comp->setObjectCodeFile( compilation->objFile );
        comp->setSourceCodeFile( compilation->srcFile );

        string cmdline = comp->buildCMDLine();

        delete comp;

        shell->pushCommand( cmdline );

        i++;
    }

    int exitCode = shell->execute();
    delete shell;
    if ( exitCode != 0 )
        throw st_error( nullptr, errors::COMPILING_FAILED );

    sourceCodeManager->saveLastWriteTimesInFile( consts::LAST_WRITE_TIMES_FILE, false );
    testSourceCodeManager->saveLastWriteTimesInFile( consts::LAST_WRITE_TIMES_FILE, true );

    if ( isCompileAll )
        manager->executeUserTaskIfExists( tasks::COMPILEALL, TaskExecution::AFTER );
    else manager->executeUserTaskIfExists( tasks::COMPILE, TaskExecution::AFTER );

    if ( isVerbose ) {
        if ( filesToCompile.empty() )
            out << infos::COMPILATION_UP_TO_DATE << endl;
        else out << infos::SUCCESS_IN_COMPILATION << endl;
    }
}

void CompileTaskExec::loadFilesToCompile( vector<Compilation*>& compilations, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    SourceCodeManager* sourceCodeManager = manager->getSourceCodeManager();
    SourceCodeManager* testSourceCodeManager = manager->getTestSourceCodeManager();
    ScriptPropertyManager* scriptPropManager = manager->getScriptPropManager();

    bool isCompileAll = manager->getMainCMDArgManager()->isCompileAll();

    string compilerParams = scriptPropManager->getCompilerParams();
    string testCompilerParams = scriptPropManager->getTestCompilerParams();

    string includeDirs = scriptPropManager->getIncludeDirs();
    string defines = scriptPropManager->getDefines();

    string testIncludeDirs = scriptPropManager->getTestIncludeDirs();
    string testDefines = scriptPropManager->getTestDefines();

    string objDir = scriptPropManager->getObjDir();
    string testDir = scriptPropManager->getTestDir();
    string srcDir = scriptPropManager->getSrcDir();

    objDir = io::path::addSeparatorIfNeed( objDir );

    testIncludeDirs += " " + srcDir;
   
    vector<CodeInfo*> sourceCodeInfos = sourceCodeManager->sourceCodeInfos();
    for( CodeInfo* info : sourceCodeInfos ) {
        string dir = io::path::dirPath( objDir + info->objFilePath );
        if ( dir != "" )
            this->appCreateDirs( dir, manager );
    }

    vector<CodeInfo*> filesToCompile;
    if ( isCompileAll ) {
        filesToCompile = sourceCodeInfos;
    } else {
        sourceCodeManager->loadFilesToCompile( filesToCompile, consts::LAST_WRITE_TIMES_FILE );
    }

    for( CodeInfo* sourceCodeInfo : filesToCompile ) {
        Compilation* comp = new Compilation();
        comp->compilerParams = compilerParams;
        comp->includeDirs = includeDirs;
        comp->defines = defines;
        comp->objFile = objDir + sourceCodeInfo->objFilePath;
        comp->srcFile = sourceCodeInfo->filePath;

        compilations.push_back( comp );
    } 

    if ( testDir != "" ) {
        vector<CodeInfo*> testSourceCodeInfos = testSourceCodeManager->sourceCodeInfos();
        for( CodeInfo* info : testSourceCodeInfos ) {
            string dir = io::path::dirPath( objDir + info->objFilePath );
            if ( dir != "" )
                this->appCreateDirs( dir, manager );
        }

        vector<CodeInfo*> testFilesToCompile;
        if ( isCompileAll ) {
            testFilesToCompile = testSourceCodeInfos;
        } else {
            testSourceCodeManager->loadFilesToCompile( testFilesToCompile, consts::LAST_WRITE_TIMES_FILE );
        }

        filesToCompile.insert( filesToCompile.end(), testFilesToCompile.begin(), testFilesToCompile.end() );

        for( CodeInfo* sourceCodeInfo : testFilesToCompile ) {
            Compilation* comp = new Compilation();
            comp->compilerParams = testCompilerParams;
            comp->includeDirs = testIncludeDirs;
            comp->defines = testDefines;
            comp->objFile = objDir + sourceCodeInfo->objFilePath;
            comp->srcFile = sourceCodeInfo->filePath;
            compilations.push_back( comp );
        }
    }
}

void CompileTaskExec::appCreateDirs( string dirPath, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    CMD* mainCMD = manager->getMainCMD();

    try {
        io::createDirs( dirPath );
    } catch ( const io_error& e ) {
        messagebuilder b( errors::DIRECTORY_NOT_CREATED );
        b << io::path::absolutePath( dirPath );
        throw st_error( mainCMD, b.str() );
    }
}
