
#include "CleanTaskProc.h"
#include "../ProcManager.h"
#include "../stexcept.h"
#include "../../io/io.h"
#include "../../util/strutil.h"

#include "../../consts.h"

#include <iostream>

using std::cout;
using std::endl;

void CleanTaskProc::proc( CMD* mainCMD, void* mgr ) {
    ProcManager* manager = (ProcManager*)mgr;

    cout << "\nEXECUTANDO LIMPESA..." << endl;

    MainScript* script = manager->getMainScript();

    string isDll = script->getPropertyValue( props::IS_DLL );
    string buildDir = script->getPropertyValue( props::BUILD_DIR );
    string binDir = script->getPropertyValue( props::BIN_DIR );
    string objDir = script->getPropertyValue( props::OBJ_DIR );
    string buildFiles = script->getPropertyValue( props::BUILD_FILES );

    if ( buildDir != "" )
        buildDir = io::addSeparatorToDirIfNeed( buildDir );
    if ( binDir != "" )
        binDir = io::addSeparatorToDirIfNeed( binDir );
    if ( objDir != "" )
        objDir = io::addSeparatorToDirIfNeed( objDir );

    string propName = ( isDll == "true" ? props::DLL_FILE_NAME : props::EXE_FILE_NAME );
    string fname = script->getPropertyValue( propName );
    if ( fname != "" ) {
        string file = binDir + fname;
        //appRecursiveDeleteFileOrDirectoryIfExists( file, propName, script );
    }

    vector<string> bfiles = strutil::splitWithDoubleQuotes( buildFiles );
    for( string bfile : bfiles ) {
        string fname = buildDir + io::fileOrDirName( bfile );
        appRecursiveDeleteFileOrDirectoryIfExists( fname, props::BUILD_FILES, script );
    }

    manager->executaTaskIfExists( tasks::CLEAN );

    cout << "Limpesa efetuada com sucesso!" << endl;
}

void CleanTaskProc::appRecursiveDeleteFileOrDirectoryIfExists( string path, string propName, MainScript* script ) {
    Prop* prop = script->getProperty( propName );

    try {
        if ( io::fileExists( path ) ) {
            int count = io::recursiveDeleteFileOrDirectory( path );
            if ( count == 0 )
                throw st_error( prop, "Arquivo ou pasta nao deletado: \"" + path + "\"" );

            cout << "Deletado: " << path << endl;
        }
    } catch ( const io_error& e ) {
        throw st_error( prop, "Nao foi possivel deletar o arquivo ou pasta: \"" + path + "\"" );
    }
}
