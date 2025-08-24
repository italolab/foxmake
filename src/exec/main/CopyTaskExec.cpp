
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

void CopyTaskExec::exec( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;

    bool isVerbose = manager->isVerbose( tasks::COPY );
    bool isNoResume = manager->isNoResume();

    if ( isVerbose )
        cout << endl;
    if ( !isNoResume || isVerbose )
        cout << infos::EXECUTING << " " << tasks::COPY << "..." << endl;

    MainScript* script = manager->getMainScript();
    CMD* mainCMD = manager->getMainCMD();

    string isDll = script->getPropertyValue( props::IS_DLL );
    string buildDir = script->getPropertyValue( props::BUILD_DIR );
    string binDir = script->getPropertyValue( props::BIN_DIR );
    string buildFiles = script->getPropertyValue( props::BUILD_FILES );

    manager->executaUserTaskIfExists( tasks::COPY, Task::BEFORE );

    buildDir = io::absoluteResolvePath( buildDir );
    binDir = io::absoluteResolvePath( binDir );
   
    binDir = io::addSeparatorToDirIfNeed( binDir );
    buildDir = io::addSeparatorToDirIfNeed( buildDir );
        
    this->appCreateDirs( mainCMD, buildDir, props::BUILD_DIR );

    if ( binDir != buildDir ) {
        if ( isDll == "true" ) {
            string dllFileName = script->getPropertyValue( props::DLL_FILE_NAME );
            string fname = binDir + dllFileName;
            appCopyFileOrDirectoryToBuild( fname, buildDir, props::BIN_DIR, manager );
        } else {
            string exeFileName = script->getPropertyValue( props::EXE_FILE_NAME );
            string fname = binDir + exeFileName;
            appCopyFileOrDirectoryToBuild( fname, buildDir, props::BIN_DIR, manager );
        }
    }

    vector<string> bfiles = strutil::splitWithDoubleQuotes( buildFiles );
    for( string bfile : bfiles )
        appCopyFileOrDirectoryToBuild( bfile, buildDir, props::BUILD_FILES ,manager );

    manager->executaUserTaskIfExists( tasks::COPY, Task::AFTER );

    if ( isVerbose )
        cout << infos::SUCCESS_IN_COPY << endl;
}

void CopyTaskExec::appCopyFileOrDirectoryToBuild( string path, string buildDir, string propName, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;

    bool isVerbose = manager->isVerbose( tasks::COPY );

    if ( !io::fileExists( path ) ) {
        messagebuilder b1 ( errors::FILE_OR_FOLDER_NOT_FOUND );
        b1 << path;

        messagebuilder b2 ( errors::VERIFY_THE_PROPERTY );
        b2 << propName;

        stringstream ss;
        ss << b1.str() << "\n" << b2.str();
        throw st_error( nullptr, ss.str() );
    }

    try {
        string bdir = ( buildDir == "" ? "." : buildDir );
        io::createDirs( bdir );
        io::copyFileOrDirectory( path, bdir, true, true );        

        if ( isVerbose ) {
            messagebuilder b( infos::FILE_OR_DIRECTORY_COPIED );
            b << path;
            cout << b.str() << endl;
        }
    } catch ( const io_error& e ) {        
        messagebuilder b( errors::FILE_OR_DIRECTORY_NOT_COPIED_FOR_BUILD_FOLDER );
        b << path;
        throw st_error( nullptr, b.str() );
    }
}

void CopyTaskExec::appCreateDirs( CMD* mainCMD, string dirPath, string propName ) {
    try {
        io::createDirs( dirPath );
    } catch ( const io_error& e ) {
        messagebuilder b1( errors::FILE_OR_DIRECTORY_NOT_CREATED );
        b1 << io::absolutePath( dirPath );

        messagebuilder b2( errors::VERIFY_THE_PROPERTY );
        b2 << propName;

        stringstream ss;
        ss << b1.str() << "\n" << b2.str();
        throw st_error( nullptr, ss.str() );
    }
}
