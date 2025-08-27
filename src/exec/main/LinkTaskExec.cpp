
#include "LinkTaskExec.h"
#include "../ExecManager.h"
#include "../../darv/MainScript.h"
#include "../../util/strutil.h"
#include "../../output/output.h"

#include "../../consts.h"
#include "../../info_messages.h"

LinkTaskExec::LinkTaskExec() {
    this->exeLinkTaskExec = new ExeLinkTaskExec();
    this->staticLibraryLinkTaskExec = new StaticLibraryLinkTaskExec();
    this->dynamicLibraryLinkTaskExec = new DynamicLibraryLinkTaskExec();
}

LinkTaskExec::~LinkTaskExec() {
    delete exeLinkTaskExec;
    delete staticLibraryLinkTaskExec;
    delete dynamicLibraryLinkTaskExec;
}

void LinkTaskExec::exec( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;

    Output& out = manager->out;
    bool isVerbose = manager->getArgManager()->isVerbose( tasks::LINK );
    bool isNoResume = manager->getArgManager()->isNoResume();

    if ( isVerbose )
        out << "\n";
    if ( !isNoResume || isVerbose )
        out << infos::EXECUTING << " " << output::green( tasks::LINK ) << "..." << "\n";    

    manager->executaUserTaskIfExists( tasks::LINK, TaskExecution::BEFORE );

    MainScript* script = manager->getMainScript();

    string outputFileName = script->getPropertyValue( props::OUTPUT_FILE_NAME );

    if ( strutil::endsWith( outputFileName, ".dll" ) ) {
        dynamicLibraryLinkTaskExec->exec( mgr );
    } else if ( strutil::endsWith( outputFileName, "so" ) ) {
        dynamicLibraryLinkTaskExec->exec( mgr );
    } else if ( strutil::startsWith( outputFileName, "lib" ) ) {
        staticLibraryLinkTaskExec->exec( mgr );
    } else {
        exeLinkTaskExec->exec( mgr );
    }

    manager->executaUserTaskIfExists( tasks::LINK, TaskExecution::AFTER );

    if ( isVerbose )
        out << infos::SUCCESS_IN_LINKING << "\n";
}
