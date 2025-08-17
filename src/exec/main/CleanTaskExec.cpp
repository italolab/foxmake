
#include "CleanTaskExec.h"
#include "../ExecManager.h"
#include "../stexcept.h"
#include "../../io/io.h"
#include "../../util/strutil.h"
#include "../../msg/messagebuilder.h"

#include "../../error_messages.h"
#include "../../info_messages.h"
#include "../../consts.h"

#include <iostream>

using std::cout;
using std::endl;

void CleanTaskExec::exec( CMD* mainCMD, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;

    cout << endl << infos::EXECUTING_CLEAN << endl;

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


    cout << infos::SUCCESS_IN_CLEAN << endl;
}

void CleanTaskExec::appRecursiveDeleteFileOrDirectoryIfExists( string path, string propName, MainScript* script ) {
    Prop* prop = script->getProperty( propName );

    try {
        if ( io::fileExists( path ) ) {
            int count = io::recursiveDeleteFileOrDirectory( path );
            if ( count == 0 ) {
                messagebuilder b ( errors::FILE_OR_FOLDER_NOT_DELETED );
                b << path;
                throw st_error( prop, b.str() );
            }

            messagebuilder b( infos::FILE_OR_DIRECTORY_DELETED );
            b << path;
            cout << b.str() << endl;
        }
    } catch ( const io_error& e ) {
        messagebuilder b( errors::FILE_OR_FOLDER_DELETION_IS_NOT_POSSIBLE );
        b << path;
        throw st_error( prop, b.str() );
    }
}
