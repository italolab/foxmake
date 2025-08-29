
#include "LinkOrArchiveTaskExec.h"
#include "../ExecManager.h"
#include "../../darv/MainScript.h"
#include "../../util/strutil.h"
#include "../../output/output.h"

#include "../../consts.h"
#include "../../info_messages.h"

LinkOrArchiveTaskExec::LinkOrArchiveTaskExec() {
    this->exeLinkTaskExec = new ExeLinkTaskExec();
    this->staticLibraryArchiveTaskExec = new ArchiveTaskExec();
    this->dynamicLibraryLinkTaskExec = new DynamicLibraryLinkTaskExec();
}

LinkOrArchiveTaskExec::~LinkOrArchiveTaskExec() {
    delete exeLinkTaskExec;
    delete staticLibraryArchiveTaskExec;
    delete dynamicLibraryLinkTaskExec;
}

void LinkOrArchiveTaskExec::exec( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;

    Output& out = manager->out;
    bool isNoResume = manager->getMainCMDArgManager()->isNoResume();
    bool isLinkVerbose = manager->getMainCMDArgManager()->isVerbose( tasks::LINK );
    bool isArchiveVerbose = manager->getMainCMDArgManager()->isVerbose( tasks::ARCHIVE );

    bool isLink = manager->getMainCMDArgManager()->isLink();
    bool isArchive = manager->getMainCMDArgManager()->isArchive();

    bool isVerbose = ( isLink && isLinkVerbose ) || ( isArchive && isArchiveVerbose );

    MainScript* script = manager->getMainScript();

    string outputFileName = script->getPropertyValue( props::OUTPUT_FILE_NAME );

    if ( isLink ) {
        if ( isVerbose )
            out << "\n";
        if ( !isNoResume || isVerbose )
            out << infos::EXECUTING << " " << output::green( tasks::LINK ) << "..." << "\n";    

        manager->executaUserTaskIfExists( tasks::LINK, TaskExecution::BEFORE );

        if ( strutil::endsWith( outputFileName, ".dll" ) ) {
            dynamicLibraryLinkTaskExec->exec( mgr );
        } else if ( strutil::endsWith( outputFileName, "so" ) ) {
            dynamicLibraryLinkTaskExec->exec( mgr );
        } else {
            exeLinkTaskExec->exec( mgr );
        }

        manager->executaUserTaskIfExists( tasks::LINK, TaskExecution::AFTER );
        if ( isVerbose )
            out << infos::SUCCESS_IN_LINKING << "\n";
    }

    if ( isArchive ) {
        if ( isVerbose )
            out << "\n";
        if ( !isNoResume || isVerbose )
            out << infos::EXECUTING << " " << output::green( tasks::ARCHIVE ) << "..." << "\n";    

        manager->executaUserTaskIfExists( tasks::ARCHIVE, TaskExecution::BEFORE );

        staticLibraryArchiveTaskExec->exec( mgr );
        
        manager->executaUserTaskIfExists( tasks::ARCHIVE, TaskExecution::AFTER );

        if ( isVerbose )
            out << infos::SUCCESS_IN_ARCHIVING << "\n";
    }
    
}
