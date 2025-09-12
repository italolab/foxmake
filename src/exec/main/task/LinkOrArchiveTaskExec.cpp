
#include "LinkOrArchiveTaskExec.h"
#include "../../ExecManager.h"
#include "../../../darv/MainScript.h"
#include "../../../util/strutil.h"
#include "../../../output/output.h"

#include "../../../consts.h"
#include "../../../info_messages.h"

using std::endl;

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
    ScriptPropertyManager* scriptPropManager = manager->getScriptPropManager();

    Output& out = manager->out;
    bool isNoResume = manager->getMainCMDArgManager()->isNoResume();
    bool isLinkVerbose = manager->getMainCMDArgManager()->isVerbose( tasks::LINK );
    bool isArchiveVerbose = manager->getMainCMDArgManager()->isVerbose( tasks::ARCHIVE );

    bool isLink = manager->getMainCMDArgManager()->isLink();
    bool isArchive = manager->getMainCMDArgManager()->isArchive();

    bool isVerbose = ( isLink && isLinkVerbose ) || ( isArchive && isArchiveVerbose );

    string outputFileName = scriptPropManager->getOutputFileName();

    if ( isLink ) {
        if ( isVerbose )
            out << endl;
        if ( !isNoResume || isVerbose )
            out << infos::EXECUTING << " " << output::green( tasks::LINK ) << "..." << endl;    

        manager->executeUserTaskIfExists( tasks::LINK, TaskExecution::BEFORE );

        if ( strutil::endsWith( outputFileName, ".dll" ) ) {
            dynamicLibraryLinkTaskExec->exec( mgr );
        } else if ( strutil::endsWith( outputFileName, "so" ) ) {
            dynamicLibraryLinkTaskExec->exec( mgr );
        } else {
            exeLinkTaskExec->exec( mgr );
        }

        manager->executeUserTaskIfExists( tasks::LINK, TaskExecution::AFTER );
        if ( isVerbose )
            out << infos::SUCCESS_IN_LINKING << endl;
    }

    if ( isArchive ) {
        if ( isVerbose )
            out << endl;
        if ( !isNoResume || isVerbose )
            out << infos::EXECUTING << " " << output::green( tasks::ARCHIVE ) << "..." << endl;    

        manager->executeUserTaskIfExists( tasks::ARCHIVE, TaskExecution::BEFORE );

        staticLibraryArchiveTaskExec->exec( mgr );
        
        manager->executeUserTaskIfExists( tasks::ARCHIVE, TaskExecution::AFTER );

        if ( isVerbose )
            out << infos::SUCCESS_IN_ARCHIVING << endl;
    }
    
}
