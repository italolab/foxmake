
#include "TestTaskExec.h"
#include "../../ExecManager.h"
#include "../../stexcept.h"
#include "../../../darv/MainScript.h"
#include "../../../io/io.h"
#include "../../../sourcecode/SourceCodeManager.h"
#include "../../../shell/shell.h"
#include "../../../output/output.h"
#include "../../../msg/messagebuilder.h"

#include "../../../consts.h"
#include "../../../error_messages.h"
#include "../../../info_messages.h"

using std::endl;

void TestTaskExec::exec( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    ScriptPropertyManager* scriptPropManager = manager->getScriptPropManager();

    Output& out = manager->out;

    bool isVerbose = manager->getMainCMDArgManager()->isVerbose( tasks::TEST );
    bool isShowCMDOutput = manager->getMainCMDArgManager()->isShowCMDOutput( tasks::TEST );
    bool isNoResume = manager->getMainCMDArgManager()->isNoResume();

    if ( isVerbose )
        out << endl;
    if ( !isNoResume || isVerbose )
        out << infos::EXECUTING << " " << output::green( tasks::TEST ) << "..." << endl;    

    string testDir = scriptPropManager->getTestDir();
    string binDir = scriptPropManager->getBinDir();

    if ( testDir == "" ) {
        messagebuilder b( errors::PROPERTY_NOT_DEFINED );
        b << props::TEST_DIR;
        throw st_error( nullptr, b.str() );
    }

    manager->executeUserTaskIfExists( tasks::TEST, TaskExecution::BEFORE );

    binDir = io::path::addSeparatorIfNeed( binDir );

    string testOutputFile = binDir + consts::TEST_OUTPUT_FILE_NAME;
    if ( !io::fileExists( testOutputFile ) )
        throw st_error( nullptr, errors::TEST_FILE_EXE_NOT_FOUND );    

    string command = testOutputFile;

    Shell* shell = new Shell( out );
    shell->setVerbose( isVerbose );
    shell->setShowOutput( isShowCMDOutput );
    shell->pushCommand( command );

    int exitCode = shell->execute();

    delete shell;

    if ( exitCode != 0 )
        throw st_error( nullptr, errors::TESTING_FAILED );

    manager->executeUserTaskIfExists( tasks::TEST, TaskExecution::AFTER );

    if ( isVerbose )
        out << infos::SUCCESS_IN_TESTING << endl;
}