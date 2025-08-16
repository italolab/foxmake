
#include "CopyTaskProc.h"
#include "../ProcManager.h"
#include "../stexcept.h"
#include "../../io/io.h"
#include "../../util/strutil.h"

#include "../../consts.h"

#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::cout;
using std::endl;

void CopyTaskProc::proc( CMD* mainCMD, void* mgr ) {
    ProcManager* manager = (ProcManager*)mgr;

    cout << "\nCOPIANDO ARQUIVOS DE BUILD..." << endl;

    MainScript* script = manager->getMainScript();

    string isDll = script->getPropertyValue( props::IS_DLL );
    string buildDir = script->getPropertyValue( props::BUILD_DIR );
    string binDir = script->getPropertyValue( props::BIN_DIR );
    string buildFiles = script->getPropertyValue( props::BUILD_FILES );

    if ( binDir != "" )
        binDir = io::addSeparatorToDirIfNeed( binDir );

    if ( buildDir != "" ) {
        this->appCreateDirs( mainCMD, buildDir );
        buildDir = io::addSeparatorToDirIfNeed( buildDir );
    }

    if ( binDir != buildDir ) {
        if ( isDll == "true" ) {
            string dllFileName = script->getPropertyValue( props::DLL_FILE_NAME );
            string fname = binDir + dllFileName;
            appCopyFileOrDirectoryToBuild( fname, buildDir, props::DLL_FILE_NAME, script );
        } else {
            string exeFileName = script->getPropertyValue( props::EXE_FILE_NAME );
            string fname = binDir + exeFileName;
            appCopyFileOrDirectoryToBuild( fname, buildDir, props::EXE_FILE_NAME, script );
        }
    }

    vector<string> bfiles = strutil::splitWithDoubleQuotes( buildFiles );
    for( string bfile : bfiles )
        appCopyFileOrDirectoryToBuild( bfile, buildDir, props::BUILD_FILES, script );

    manager->executaTaskIfExists( tasks::COPY );

    cout << "Arquivos de build copiados com sucesso!" << endl;
}

void CopyTaskProc::appCopyFileOrDirectoryToBuild( string path, string buildDir, string propName, MainScript* script ) {
    Prop* prop = script->getProperty( propName );

    if ( !io::fileExists( path ) )
        throw st_error( prop, "O arquivo ou pasta: \"" + path + "\" nao existe." );

    try {
        string bdir = ( buildDir == "" ? "." : buildDir );
        io::createDirs( bdir );
        io::copyFileOrDirectory( path, bdir, true, true );

        cout << "Copiado: " << path << endl;
    } catch ( const io_error& e ) {
        throw st_error( prop, "Nao foi possivel copiar o arquivo ou pasta: \"" + path + "\" para a pasta de build." );
    }
}

void CopyTaskProc::appCreateDirs( CMD* mainCMD, string dirPath ) {
    try {
        io::createDirs( dirPath );
    } catch ( const io_error& e ) {
        string absDirPath = io::absolutePath( dirPath );
        throw st_error( mainCMD, "Nao foi possivel criar o diretorio: \"" + absDirPath + "\"" );
    }
}
