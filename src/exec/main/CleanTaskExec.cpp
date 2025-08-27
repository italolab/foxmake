
#include "CleanTaskExec.h"
#include "../ExecManager.h"
#include "../stexcept.h"
#include "../../io/io.h"
#include "../../util/strutil.h"
#include "../../output/output.h"
#include "../../msg/messagebuilder.h"

#include "../../error_messages.h"
#include "../../info_messages.h"
#include "../../consts.h"

void CleanTaskExec::exec( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;

    Output& out = manager->out;
    bool isVerbose = manager->getArgManager()->isVerbose( tasks::CLEAN );
    bool isNoResume = manager->getArgManager()->isNoResume();

    if ( isVerbose )
        out << "\n";
    if ( !isNoResume || isVerbose )
        out << infos::EXECUTING << " " << output::green( tasks::CLEAN ) << "..." << "\n";    

    manager->executaUserTaskIfExists( tasks::CLEAN, TaskExecution::BEFORE );

    MainScript* script = manager->getMainScript();

    string buildDir = script->getPropertyValue( props::BUILD_DIR );
    string binDir = script->getPropertyValue( props::BIN_DIR );
    string objDir = script->getPropertyValue( props::OBJ_DIR );
    string buildFiles = script->getPropertyValue( props::BUILD_FILES );

    buildDir = io::absoluteResolvePath( buildDir );
    binDir = io::absoluteResolvePath( binDir );
    objDir = io::absoluteResolvePath( objDir );

    buildDir = io::addSeparatorToDirIfNeed( buildDir );
    binDir = io::addSeparatorToDirIfNeed( binDir );
    objDir = io::addSeparatorToDirIfNeed( objDir );

    bool removedSome = false;

    string propName = props::OUTPUT_FILE_NAME;
    string fname = script->getPropertyValue( propName );
    if ( fname != "" ) {
        string file = binDir + fname;
        bool removed = this->appRecursiveDeleteFileOrDirectoryIfExists( file, mgr );
        if ( removed )
            removedSome = true;
    }

    vector<string> bfiles = strutil::splitWithDoubleQuotes( buildFiles );
    for( string bfile : bfiles ) {
        string fname = buildDir + io::fileOrDirName( bfile );
        bool removed = this->appRecursiveDeleteFileOrDirectoryIfExists( fname, mgr );
        if ( removed )
            removedSome = true;
    }

    manager->executaUserTaskIfExists( tasks::CLEAN, TaskExecution::AFTER );

    if ( isVerbose ) {
        if ( removedSome )
            out << infos::SUCCESS_IN_CLEAN << "\n";
        else out << infos::CLEAN_UP_TO_DATE << "\n";
    }
}

bool CleanTaskExec::appRecursiveDeleteFileOrDirectoryIfExists( string path, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;

    Output& out = manager->out;
    bool isVerbose = manager->getArgManager()->isVerbose( tasks::CLEAN );
    
    try {
        if ( io::fileExists( path ) ) {
            int count = io::recursiveDeleteFileOrDirectory( path );
            if ( count == 0 ) {
                messagebuilder b ( errors::FILE_OR_FOLDER_NOT_DELETED );
                b << path;
                throw st_error( nullptr, b.str() );
            }

            if ( isVerbose ) {
                messagebuilder b( infos::FILE_OR_DIRECTORY_DELETED );
                b << path;
                out << output::green( b.str() ) << "\n";
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
