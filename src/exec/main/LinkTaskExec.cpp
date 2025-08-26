
#include "LinkTaskExec.h"
#include "../ExecManager.h"
#include "../../darv/MainScript.h"
#include "../../util/strutil.h"

#include "../../consts.h"
#include "../../info_messages.h"

LinkTaskExec::LinkTaskExec() {
    this->exeLinkTaskExec = new ExeLinkTaskExec();
    this->dynamicLibraryLinkTaskExec = new DynamicLibraryLinkTaskExec();
}

void LinkTaskExec::exec( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;

    Output& out = manager->out;
    Output& inf = manager->inf;
    bool isVerbose = manager->getArgManager()->isVerbose( tasks::LINK );
    bool isNoResume = manager->getArgManager()->isNoResume();

    if ( isVerbose )
        out << "\n";
    if ( !isNoResume || isVerbose ) {
        out << infos::EXECUTING << " ";
        inf << tasks::LINK;
        out << "..." << "\n";
    }

    manager->executaUserTaskIfExists( tasks::LINK, Task::BEFORE );

    MainScript* script = manager->getMainScript();

    string outputFileName = script->getPropertyValue( props::OUTPUT_FILE_NAME );

    if ( strutil::endsWith( outputFileName, ".dll" ) ) {
        dynamicLibraryLinkTaskExec->exec( mgr );
    } else if ( strutil::endsWith( outputFileName, "so" ) ) {
        dynamicLibraryLinkTaskExec->exec( mgr );
    } else if ( strutil::startsWith( outputFileName, "lib" ) ) {

    } else {
        exeLinkTaskExec->exec( mgr );
    }

    manager->executaUserTaskIfExists( tasks::LINK, Task::AFTER );

    if ( isVerbose )
        out << infos::SUCCESS_IN_LINKING << "\n";
}
