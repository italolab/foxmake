
#include "CopyTaskExec.h"
#include "../ExecManager.h"
#include "../stexcept.h"
#include "../../io/io.h"
#include "../../util/strutil.h"
#include "../../msg/messagebuilder.h"

#include "../../error_messages.h"
#include "../../info_messages.h"

#include "../../consts.h"

#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::cout;
using std::endl;

void CopyTaskExec::exec( CMD* mainCMD, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;

    cout << endl << infos::EXECUTING_COPY << endl;

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

    cout << infos::SUCCESS_IN_COPY << endl;
}

void CopyTaskExec::appCopyFileOrDirectoryToBuild( string path, string buildDir, string propName, MainScript* script ) {
    Prop* prop = script->getProperty( propName );

    if ( !io::fileExists( path ) ) {
        messagebuilder b ( errors::FILE_OR_FOLDER_NOT_FOUND );
        b << path;
        throw st_error( prop, b.str() );
    }

    try {
        string bdir = ( buildDir == "" ? "." : buildDir );
        io::createDirs( bdir );
        io::copyFileOrDirectory( path, bdir, true, true );

        messagebuilder b( infos::FILE_OR_DIRECTORY_COPIED );
        b << path;
        cout << b.str() << endl;
    } catch ( const io_error& e ) {
        messagebuilder b( errors::FILE_OR_DIRECTORY_NOT_COPIED_FOR_BUILD_FOLDER );
        b << path;
        throw st_error( prop, b.str() );
    }
}

void CopyTaskExec::appCreateDirs( CMD* mainCMD, string dirPath ) {
    try {
        io::createDirs( dirPath );
    } catch ( const io_error& e ) {
        messagebuilder b( errors::FILE_OR_DIRECTORY_NOT_CREATED );
        b << io::absolutePath( dirPath );
        throw st_error( mainCMD, b.str() );
    }
}
