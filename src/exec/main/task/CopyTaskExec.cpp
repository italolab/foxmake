
#include "CopyTaskExec.h"
#include "../../ExecManager.h"
#include "../../stexcept.h"
#include "../../../io/io.h"
#include "../../../util/strutil.h"
#include "../../../msg/messagebuilder.h"

#include "../../../error_messages.h"
#include "../../../info_messages.h"

#include "../../../consts.h"

#include <string>
#include <vector>

using std::string;
using std::vector;
using std::endl;

void CopyTaskExec::exec( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    ScriptPropertyManager* scriptPropManager = manager->getScriptPropManager();

    Output& out = manager->out;

    bool isVerbose = manager->getMainCMDArgManager()->isVerbose( tasks::COPY );
    bool isNoResume = manager->getMainCMDArgManager()->isNoResume();

    if ( !isNoResume || isVerbose )
        out << infos::EXECUTING << " " << output::green( tasks::COPY ) << "..." << endl;    

    string buildDir = scriptPropManager->getBuildDir();
    string binDir = scriptPropManager->getBinDir();
    string buildFiles = scriptPropManager->getBuildFiles();

    manager->executeUserTaskIfExists( tasks::COPY, TaskExecution::BEFORE );
   
    binDir = io::path::addSeparatorIfNeed( binDir );
    buildDir = io::path::addSeparatorIfNeed( buildDir );
        
    this->appCreateDirs( buildDir, props::BUILD_DIR );

    out << infos::COPYING_TO_BUILD_FOLDER << endl;
    
    if ( binDir != buildDir ) {
        string outputFileName = scriptPropManager->getOutputFileName();
        if ( outputFileName != "" ) {
            string linkOutFName = binDir + outputFileName;
            appCopyFileOrDirectoryToBuild( linkOutFName, buildDir, props::OUTPUT_FILE_NAME, manager );        
        }
    }

    vector<string> bfiles = strutil::splitWithDoubleQuotes( buildFiles );
    for( string bfile : bfiles )
        appCopyFileOrDirectoryToBuild( bfile, buildDir, props::BUILD_FILES ,manager );

    manager->executeUserTaskIfExists( tasks::COPY, TaskExecution::AFTER );

    if ( isVerbose ) {
        out << infos::SUCCESS_IN_COPY << endl;
        out << endl;
    }
}

void CopyTaskExec::appCopyFileOrDirectoryToBuild( string path, string buildDir, string propName, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;

    Output& out = manager->out;
    bool isVerbose = manager->getMainCMDArgManager()->isVerbose( tasks::COPY );

    if ( !io::fileExists( path ) ) {
        messagebuilder b1 ( errors::FILE_OR_FOLDER_NOT_FOUND );
        b1 << path;

        messagebuilder b2 ( errors::VERIFY_THE_PROPERTY );
        b2 << propName;

        messagebuilder b3 ( errors::VERIFY_THE_PROPERTY );
        b3 << props::BIN_DIR;

        stringstream ss;
        ss << b1.str() << "\n" << b2.str() << "\n" << b3.str();
        throw st_error( nullptr, ss.str() );
    }

    try {
        string bdir = ( buildDir == "" ? "." : buildDir );
        io::createDirs( bdir );
        io::copyFileOrDir( path, bdir, true, true );        

        if ( isVerbose ) {
            messagebuilder b( infos::FILE_OR_DIRECTORY_COPIED );
            b << path;
            out << output::bold( b.str() ) << endl;
        }
    } catch ( const io_error& e ) {        
        messagebuilder b( errors::FILE_OR_DIRECTORY_NOT_COPIED_FOR_BUILD_FOLDER );
        b << path;
        throw st_error( nullptr, b.str() );
    }
}

void CopyTaskExec::appCreateDirs( string dirPath, string propName ) {
    try {
        io::createDirs( dirPath );
    } catch ( const io_error& e ) {
        messagebuilder b1( errors::FILE_OR_DIRECTORY_NOT_CREATED );
        b1 << io::path::absolutePath( dirPath );

        messagebuilder b2( errors::VERIFY_THE_PROPERTY );
        b2 << propName;

        stringstream ss;
        ss << b1.str() << "\n" << b2.str();
        throw st_error( nullptr, ss.str() );
    }
}
