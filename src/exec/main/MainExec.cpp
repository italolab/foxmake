
#include "MainExec.h"
#include "../ExecManager.h"
#include "../stexcept.h"
#include "../../darv/CMD.h"
#include "../../inter/InterResult.h"
#include "../../shell/shell.h"
#include "../../util/strutil.h"
#include "../../io/io.h"
#include "../../sourcecode/SourceCodeManager.h"
#include "../../output/output.h"
#include "../../msg/messagebuilder.h"

#include "../../error_messages.h"
#include "../../info_messages.h"
#include "../../help_messages.h"
#include "../../consts.h"

#include <string>
#include <sstream>
#include <vector>

using std::string;
using std::vector;
using std::stringstream;
using std::endl;

MainExec::MainExec() {
    mainCMDInterpreter = new MainCMDInterpreter();

    cleanTaskExec = new CleanTaskExec();
    compileTaskExec = new CompileTaskExec();
    linkOrArchiveTaskExec = new LinkOrArchiveTaskExec();
    testTaskExec = new TestTaskExec();
    copyTaskExec = new CopyTaskExec();
}

MainExec::~MainExec() {
    delete mainCMDInterpreter;

    delete cleanTaskExec;
    delete compileTaskExec;
    delete linkOrArchiveTaskExec;
    delete testTaskExec;
    delete copyTaskExec;
}

void MainExec::exec( CMD* mainCMD, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;

    Output& out = manager->out;
    bool isShowHelp = manager->getMainCMDArgManager()->isHelp();
    bool isVerbose = manager->getMainCMDArgManager()->isVerbose();
    bool isNoResume = manager->getMainCMDArgManager()->isNoResume();

    if ( mainCMD->countNoOpArgs() == 0 || isShowHelp ) {
        this->showHelp( mgr );
        return;
    }
    
    mainCMDInterpreter->configureAndInterpretsAndValidate( mgr );

    bool isClean = manager->getMainCMDArgManager()->isClean();
    bool isCompile = manager->getMainCMDArgManager()->isCompile();
    bool isCompileAll = manager->getMainCMDArgManager()->isCompileAll();
    bool isLink = manager->getMainCMDArgManager()->isLink();
    bool isArchive = manager->getMainCMDArgManager()->isArchive();
    bool isTest = manager->getMainCMDArgManager()->isTest();
    bool isCopy = manager->getMainCMDArgManager()->isCopy();

    this->genSourceAndHeaderInfos( manager );

    if ( !isNoResume || isVerbose )
        out << infos::EXECUTING << " " << output::green( tasks::INIT ) << "..." << endl;

    manager->executeUserTaskIfExists( tasks::INIT, TaskExecution::BEFORE );    
    manager->executeUserTaskIfExists( tasks::INIT, TaskExecution::AFTER );

    manager->executeUserTaskIfExists( tasks::BUILD, TaskExecution::BEFORE );
    manager->executeUserTaskIfExists( tasks::BUILDALL, TaskExecution::BEFORE );
    manager->executeUserTaskIfExists( tasks::ARCHIVEBUILD, TaskExecution::BEFORE );
    manager->executeUserTaskIfExists( tasks::ARCHIVEBUILDALL, TaskExecution::BEFORE );
    manager->executeUserTaskIfExists( tasks::TESTBUILD, TaskExecution::BEFORE );
    manager->executeUserTaskIfExists( tasks::TESTBUILDALL, TaskExecution::BEFORE );
        
    if ( isClean )
        cleanTaskExec->exec( mgr );
    if ( isCompile || isCompileAll )
        compileTaskExec->exec( mgr );
    if ( isLink || isArchive )
        linkOrArchiveTaskExec->exec( mgr );
    if ( isTest )
        testTaskExec->exec( mgr );
    if ( isCopy )
        copyTaskExec->exec( mgr );
    
    manager->executeUserTaskIfExists( tasks::BUILD, TaskExecution::AFTER );
    manager->executeUserTaskIfExists( tasks::BUILDALL, TaskExecution::AFTER );
    manager->executeUserTaskIfExists( tasks::ARCHIVEBUILD, TaskExecution::AFTER );
    manager->executeUserTaskIfExists( tasks::ARCHIVEBUILDALL, TaskExecution::AFTER );
    manager->executeUserTaskIfExists( tasks::TESTBUILD, TaskExecution::AFTER );
    manager->executeUserTaskIfExists( tasks::TESTBUILDALL, TaskExecution::AFTER );

    this->executaNoDefaultTasks( manager );

    this->executaStatements( manager );

    if ( isVerbose )
        out << endl;
    if ( !isNoResume || isVerbose )
        out << infos::EXECUTING << " " << output::green( tasks::FINISH ) << "..." << endl;
        
    manager->executeUserTaskIfExists( tasks::FINISH, TaskExecution::BEFORE );
    manager->executeUserTaskIfExists( tasks::FINISH, TaskExecution::AFTER );
    
    if ( isVerbose )
        out << endl;

    if ( !isNoResume )
        out << infos::FINISH << endl;

    if ( isVerbose && !isNoResume ) {
        out << endl;
        out << infos::COPYRIGHT << endl;
    }
}

void MainExec::genSourceAndHeaderInfos( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    SourceCodeManager* sourceCodeManager = manager->getSourceCodeManager();    
    SourceCodeManager* testSourceCodeManager = manager->getTestSourceCodeManager();
    ScriptPropertyManager* scriptPropManager = manager->getScriptPropManager();

    Output& out = manager->out;
    CMD* mainCMD = manager->getMainCMD();

    bool isVerbose = manager->getMainCMDArgManager()->isVerbose();

    string srcDir = scriptPropManager->getSrcDir();
    string testDir = scriptPropManager->getTestDir();

    if ( !io::fileExists( srcDir ) ) {        
        messagebuilder b2( errors::SRC_DIRECTORY_NOT_FOUND );
        b2 << srcDir << props::SRC_DIR;
        throw st_error( mainCMD, b2.str() );
    }

    if ( isVerbose ) {
        messagebuilder b2( infos::SRC_DIRECTORY );
        b2 << srcDir;
        out << b2.str() << endl;
    }

    bool ok = sourceCodeManager->recursiveProcFiles( srcDir, consts::SRC_TARGET_FOLDER );
    if ( !ok )
        throw st_error( mainCMD, errors::ERROR_IN_READING_SRC_FILES );

    if ( testDir != "" ) {
        ok = testSourceCodeManager->recursiveProcFiles( testDir, consts::TEST_TARGET_FOLDER );
        if ( !ok )
            throw st_error( mainCMD, errors::ERROR_IN_READING_TEST_FILES );
    }
}

void MainExec::executaNoDefaultTasks( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    CMD* mainCMD = manager->getMainCMD();

    Output& out = manager->out;
    bool isVerbose = manager->getMainCMDArgManager()->isVerbose();
    bool isNoResume = manager->getMainCMDArgManager()->isNoResume();

    vector<Task*> tasks = manager->getMainScript()->getTasks();
    for( Task* task : tasks ) {
        string taskName = task->getName();

        bool isTaskArg = mainCMD->existsArg( taskName );
        if ( isTaskArg && !manager->isDefaultTask( taskName ) ) {
            if ( isVerbose && !isNoResume )
                out << infos::EXECUTING << " " << output::green( taskName ) << "..." << endl;                            

            manager->executeUserTaskIfExists( taskName, TaskExecution::BEFORE );
            manager->executeUserTaskIfExists( taskName, TaskExecution::NORMAL );
            manager->executeUserTaskIfExists( taskName, TaskExecution::AFTER );
        }
    }
}

void MainExec::executaStatements( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;

    Output& out = manager->out;
    bool isVerbose = manager->getMainCMDArgManager()->isVerbose();
    bool isNoResume = manager->getMainCMDArgManager()->isNoResume();

    MainScript* script = manager->getMainScript();
    int tam = script->getStatementsLength();

    if ( tam > 0 ) {
        if( isVerbose )
            out << endl;
        if ( !isNoResume )
            out << infos::EXECUTING_STATEMENTS << endl;
    }

    manager->executeBlockStatements( script );

    if ( tam > 0 && isVerbose )
        out << infos::SUCCESS_IN_EXECUTING_STATEMENTS << endl;
}

void MainExec::showHelp( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    CMD* mainCMD = manager->getMainCMD();

    Output& out = manager->out;
    
    int count = mainCMD->countNoOpArgs();
    if ( count == 0 ) {
        out << helpmessage::helpMessage();
    } else if ( count > 0 ) {
        string taskName = mainCMD->getNoOpArgByIndex( 0 );
        if ( taskName == tasks::CLEAN ) {
            out << helpmessage::cleanHelpMessage();
        } else if ( taskName == tasks::COMPILE ) {
            out << helpmessage::compileHelpMessage();
        } else if ( taskName == tasks::COMPILEALL ) {
            out << helpmessage::compileAllHelpMessage();
        } else if ( taskName == tasks::ARCHIVE ) {
            out << helpmessage::archiveHelpMessage();
        } else if ( taskName == tasks::TEST ) {
            out << helpmessage::testHelpMessage();
        } else if ( taskName == tasks::LINK ) {
            out << helpmessage::linkHelpMessage();
        } else if ( taskName == tasks::COPY ) {
            out << helpmessage::copyHelpMessage();
        } else if ( taskName == tasks::BUILD ) {
            out << helpmessage::buildHelpMessage();
        } else if ( taskName == tasks::ARCHIVEBUILD ) {
            out << helpmessage::archiveBuildHelpMessage();
        } else if ( taskName == tasks::TESTBUILD ) {
            out << helpmessage::testBuildHelpMessage();
        } else if ( taskName == tasks::BUILDALL ) {
            out << helpmessage::buildAllHelpMessage();
        } else if ( taskName == tasks::ARCHIVEBUILDALL ) {
            out << helpmessage::archiveBuildAllHelpMessage();
        } else if ( taskName == tasks::TESTBUILDALL ) {
            out << helpmessage::testBuildAllHelpMessage();
        } else {
            out << errors::TASK_NOT_RECOGNIZED << endl;
        }
    }
}
