
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

using std::string;
using std::vector;

void CopyTaskExec::exec( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;

    Output& out = manager->out;
    Output& inf = manager->inf;
    bool isVerbose = manager->getArgManager()->isVerbose( tasks::COPY );
    bool isNoResume = manager->getArgManager()->isNoResume();

    if ( isVerbose )
        out << "\n";
    if ( !isNoResume || isVerbose ) {
        out << infos::EXECUTING << " ";
        inf << tasks::COPY;
        out << "..." << "\n";
    }

    MainScript* script = manager->getMainScript();
    CMD* mainCMD = manager->getMainCMD();

    string buildDir = script->getPropertyValue( props::BUILD_DIR );
    string binDir = script->getPropertyValue( props::BIN_DIR );
    string buildFiles = script->getPropertyValue( props::BUILD_FILES );

    manager->executaUserTaskIfExists( tasks::COPY, TaskExecution::BEFORE );

    buildDir = io::absoluteResolvePath( buildDir );
    binDir = io::absoluteResolvePath( binDir );
   
    binDir = io::addSeparatorToDirIfNeed( binDir );
    buildDir = io::addSeparatorToDirIfNeed( buildDir );
        
    this->appCreateDirs( mainCMD, buildDir, props::BUILD_DIR );

    if ( binDir != buildDir ) {
        string outputFileName = script->getPropertyValue( props::OUTPUT_FILE_NAME );
        string fname = binDir + outputFileName;
        appCopyFileOrDirectoryToBuild( fname, buildDir, props::BIN_DIR, manager );        
    }

    vector<string> bfiles = strutil::splitWithDoubleQuotes( buildFiles );
    for( string bfile : bfiles )
        appCopyFileOrDirectoryToBuild( bfile, buildDir, props::BUILD_FILES ,manager );

    manager->executaUserTaskIfExists( tasks::COPY, TaskExecution::AFTER );

    if ( isVerbose )
        out << infos::SUCCESS_IN_COPY << "\n";
}

void CopyTaskExec::appCopyFileOrDirectoryToBuild( string path, string buildDir, string propName, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;

    Output& inf = manager->inf;
    bool isVerbose = manager->getArgManager()->isVerbose( tasks::COPY );

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
            inf << b.str() << "\n";
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
