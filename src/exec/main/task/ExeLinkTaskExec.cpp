
#include "ExeLinkTaskExec.h"
#include "../../ExecManager.h"
#include "../../stexcept.h"
#include "../../../compiler/Linker.h"
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

#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

using std::string;
using std::vector;
using std::stringstream;
using std::endl;

void ExeLinkTaskExec::exec( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    ScriptPropertyManager* scriptPropManager = manager->getScriptPropManager();

    string compiler = scriptPropManager->getCompiler();
    string outputFileName = scriptPropManager->getOutputFileName();
    string resourceFile = scriptPropManager->getResourceFile();
    string testDir = scriptPropManager->getTestDir();

    if ( outputFileName == "" && testDir == "" ) {
        messagebuilder b( errors::PROPERTY_NOT_DEFINED_FOR_LINKING );
        b << props::OUTPUT_FILE_NAME;
        throw st_error( nullptr, b.str() );
    }

    if ( resourceFile != "" ) {
        if ( !io::fileExists( resourceFile ) ) {
            messagebuilder b( errors::RESOURCE_FILE_NOT_EXISTS );
            b << resourceFile;
            throw st_error( nullptr, b.str() );
        }
    }

    if ( outputFileName != "" )
        this->execLinkage( mgr );    
}

/*
São linkados todos os arquivos objeto do projeto que correspondem aos arquivos 
de código fonte da pasta de src. O executável gerado vai para o caminho correspondente 
a propriedade "bin.dir" concatenado ao valor da propriedade "output.file.name".
*/

void ExeLinkTaskExec::execLinkage( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    SourceCodeManager* sourceCodeManager = manager->getSourceCodeManager();
    ScriptPropertyManager* scriptPropManager = manager->getScriptPropManager();

    Output& out = manager->out;
    bool isVerbose = manager->getMainCMDArgManager()->isVerbose( tasks::LINK );
    bool isShowCMDOutput = manager->getMainCMDArgManager()->isShowCMDOutput( tasks::LINK );

    string compiler = scriptPropManager->getCompiler();
    string linkerParams = scriptPropManager->getLinkerParams();

    string outputFileName = scriptPropManager->getOutputFileName();

    string binDir = scriptPropManager->getBinDir();
    string objDir = scriptPropManager->getObjDir();

    string resourceFile = scriptPropManager->getResourceFile();

    string libDirs = scriptPropManager->getLibDirs();
    string libs = scriptPropManager->getLibs();
    
    string defines = scriptPropManager->getDefines();

    binDir = io::path::addSeparatorIfNeed( binDir );
    objDir = io::path::addSeparatorIfNeed( objDir );

    vector<string> objectCodeFiles;
    vector<CodeInfo*> sourceCodeInfos = sourceCodeManager->sourceCodeInfos();
    for( CodeInfo* info : sourceCodeInfos )        
        objectCodeFiles.push_back( objDir + info->objFilePath );    

    if ( objectCodeFiles.empty() ) {
        out << output::green( infos::NOTHING_TO_LINK ) << endl;
    } else {
        Linker* linker = new Linker();
        linker->setCompiler( compiler );
        linker->setLinkerParams( linkerParams );
        linker->setDefines( defines );
        linker->setLibraryDirs( libDirs );
        linker->setLibraries( libs );
        linker->setObjectCodeFiles( objectCodeFiles );
        linker->setResourceFile( resourceFile );
        linker->setOutputFile( binDir + outputFileName );
        string cmdline = linker->buildCMDLine();

        delete linker;

        Shell* shell = new Shell( out );
        shell->setVerbose( isVerbose );
        shell->setShowOutput( isShowCMDOutput );
        shell->pushCommand( cmdline );

        int exitCode = shell->execute();
        delete shell;
        if ( exitCode != 0 )
            throw st_error( nullptr, errors::LINKING_FAILED );
    }
}