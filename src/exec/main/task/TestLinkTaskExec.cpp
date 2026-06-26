
#include "TestLinkTaskExec.h"
#include "../../ExecManager.h"
#include "../../stexcept.h"
#include "../../../compiler/Linker.h"
#include "../../../darv/MainScript.h"
#include "../../../util/strutil.h"
#include "../../../output/output.h"
#include "../../../io/io.h"
#include "../../../shell/shell.h"

#include "../../../consts.h"
#include "../../../error_messages.h"
#include "../../../info_messages.h"

using std::endl;

/*
São linkados todos os arquivos objeto do projeto, excluíndo os arquivos objeto que não 
têm um arquivo de header correspondente.
Exemplo:
    - "main.o" pode não ter um "main.h", logo, se não tem, não é linkado.
    - "util/strutil.o" pode ter um arquivo "util/strutil.h" correspondente, logo, 
      se tem, é linkado.

São também linkados os arquivos objeto correspondentes aos sources da pasta de testes.

O arquivo de saída é o caminho da concatenação entre o valor da propriedade "bin.dir" e 
o valor da constante TEST_OUTPUT_FILE_NAME
*/

void TestLinkTaskExec::execLinkage( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    SourceCodeManager* sourceCodeManager = manager->getSourceCodeManager();
    SourceCodeManager* testSourceCodeManager = manager->getTestSourceCodeManager();
    ScriptPropertyManager* scriptPropManager = manager->getScriptPropManager();

    Output& out = manager->out;
    bool isVerbose = manager->getMainCMDArgManager()->isVerbose( tasks::LINK );
    bool isShowCMDOutput = manager->getMainCMDArgManager()->isShowCMDOutput( tasks::LINK );

    string compiler = scriptPropManager->getCompiler();
    string testLinkerParams = scriptPropManager->getTestLinkerParams();

    string testLibDirs = scriptPropManager->getTestLibDirs();
    string testLibs = scriptPropManager->getTestLibs();

    string testDefines = scriptPropManager->getTestDefines();

    string objDir = scriptPropManager->getObjDir();
    string binDir = scriptPropManager->getBinDir();

    objDir = io::path::addSeparatorIfNeed( objDir );
    binDir = io::path::addSeparatorIfNeed( binDir );

    vector<string> withHeaderObjFiles = sourceCodeManager->withHeaderObjectCodeFiles();    
    vector<CodeInfo*> testSourceCodeInfos = testSourceCodeManager->sourceCodeInfos();
        
    vector<string> objectCodeFiles;
    
    for( string objFile : withHeaderObjFiles ) {
        string ofile = objDir + objFile;
        if ( io::fileExists( ofile ) )
            objectCodeFiles.push_back( ofile );
    }

    for( CodeInfo* info : testSourceCodeInfos )
        objectCodeFiles.push_back( objDir + info->objFilePath );

    if ( objectCodeFiles.empty() ) {
        out << output::green( infos::NOTHING_TO_TEST ) << endl;
    } else {
        Linker* linker = new Linker();
        linker->setCompiler( compiler );
        linker->setLinkerParams( testLinkerParams );
        linker->setDefines( testDefines );
        linker->setLibraryDirs( testLibDirs );
        linker->setLibraries( testLibs );
        linker->setObjectCodeFiles( objectCodeFiles );
        linker->setOutputFile( binDir + consts::TEST_OUTPUT_FILE_NAME );
        string cmdline = linker->buildCMDLine();

        delete linker;

        Shell* shell = new Shell( out );
        shell->setVerbose( isVerbose );
        shell->setShowOutput( isShowCMDOutput );
        shell->pushCommand( cmdline );

        int exitCode = shell->execute();
        delete shell;
        if ( exitCode != 0 )
            throw st_error( nullptr, errors::TEST_LINKING_FAILED );            
    }
}