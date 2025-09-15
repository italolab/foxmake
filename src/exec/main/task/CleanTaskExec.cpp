
#include "CleanTaskExec.h"
#include "../../ExecManager.h"
#include "../../stexcept.h"
#include "../../../io/io.h"
#include "../../../util/strutil.h"
#include "../../../output/output.h"
#include "../../../msg/messagebuilder.h"

#include "../../../error_messages.h"
#include "../../../info_messages.h"
#include "../../../consts.h"

using std::endl;

void CleanTaskExec::exec( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    ScriptPropertyManager* scriptPropManager = manager->getScriptPropManager();

    Output& out = manager->out;
    bool isVerbose = manager->getMainCMDArgManager()->isVerbose( tasks::CLEAN );
    bool isNoResume = manager->getMainCMDArgManager()->isNoResume();

    if ( !isNoResume || isVerbose )
        out << infos::EXECUTING << " " << output::green( tasks::CLEAN ) << "..." << endl;    

    manager->executeUserTaskIfExists( tasks::CLEAN, TaskExecution::BEFORE );

    string buildDir = scriptPropManager->getBuildDir();
    string binDir = scriptPropManager->getBinDir();
    string objDir = scriptPropManager->getObjDir();
    string buildFiles = scriptPropManager->getBuildFiles();

    buildDir = io::path::addSeparatorIfNeed( buildDir );
    binDir = io::path::addSeparatorIfNeed( binDir );
    objDir = io::path::addSeparatorIfNeed( objDir );    

    bool removedSome = false;

    string outputFName = scriptPropManager->getOutputFileName();
    if ( outputFName != "" ) {
        string file = binDir + outputFName;
        bool removed = this->appRecursiveDeleteFileOrDirectoryIfExists( file, mgr );
        if ( removed )
            removedSome = true;
    }

    string testFileExe = binDir + consts::TEST_OUTPUT_FILE_NAME;
    bool removed = this->appRecursiveDeleteFileOrDirectoryIfExists( testFileExe, mgr );
    if ( removed )
        removedSome = true;

    vector<string> bfiles = strutil::splitWithDoubleQuotes( buildFiles );
    for( string bfile : bfiles ) {
        string fname = buildDir + io::path::fileOrDirName( bfile );
        bool removed2 = this->appRecursiveDeleteFileOrDirectoryIfExists( fname, mgr );
        if ( removed2 )
            removedSome = true;
    }

    manager->executeUserTaskIfExists( tasks::CLEAN, TaskExecution::AFTER );

    if ( isVerbose ) {
        if ( removedSome )
            out << infos::SUCCESS_IN_CLEAN << endl;
        else out << infos::CLEAN_UP_TO_DATE << endl;
        out << endl;
    }
}

bool CleanTaskExec::appRecursiveDeleteFileOrDirectoryIfExists( string path, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;

    Output& out = manager->out;
    bool isVerbose = manager->getMainCMDArgManager()->isVerbose( tasks::CLEAN );
    
    try {
        if ( io::fileExists( path ) ) {
            int count = io::deleteFileOrDir( path, true );
            if ( count == 0 ) {
                messagebuilder b ( errors::FILE_OR_FOLDER_NOT_DELETED );
                b << path;
                throw st_error( nullptr, b.str() );
            }

            if ( isVerbose ) {
                messagebuilder b( infos::FILE_OR_DIRECTORY_DELETED );
                b << path;
                out << output::bold( b.str() ) << endl;
            }
            return true;
        }
        return false;
    } catch ( const io_error& e ) {
        messagebuilder b( errors::FILE_OR_FOLDER_DELETION_IS_NOT_POSSIBLE );
        b << path;
        throw st_error( nullptr, b.str() );
    }
}
