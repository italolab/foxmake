
#include "LinkTaskExec.h"
#include "../ExecManager.h"
#include "../stexcept.h"
#include "../../darv/MainScript.h"
#include "../../shell/shell.h"
#include "../../io/io.h"
#include "../../io/SourceCodeManager.h"
#include "../../util/strutil.h"
#include "../../msg/messagebuilder.h"

#include "../../error_messages.h"
#include "../../info_messages.h"
#include "../../consts.h"

#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <iostream>

using std::string;
using std::vector;
using std::stringstream;
using std::cout;
using std::endl;

void LinkTaskExec::exec( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    SourceCodeManager* sourceCodeManager = manager->getSourceCodeManager();

    bool isVerbose = manager->getArgManager()->isVerbose( tasks::LINK );
    bool isShowCMDOutput = manager->getArgManager()->isShowCMDOutput( tasks::LINK );
    bool isNoResume = manager->getArgManager()->isNoResume();

    if ( isVerbose )
        cout << endl;
    if ( !isNoResume || isVerbose )
        cout << infos::EXECUTING << " " << tasks::LINK << "..." << endl;

    manager->executaUserTaskIfExists( tasks::LINK, Task::BEFORE );

    MainScript* script = manager->getMainScript();

    string isDll = script->getPropertyValue( props::IS_DLL );

    string compiler = script->getPropertyValue( props::COMPILER );
    string linkerParams = script->getPropertyValue( props::LINKER_PARAMS );

    string exeFileName = script->getPropertyValue( props::EXE_FILE_NAME );
    string dllFileName = script->getPropertyValue( props::DLL_FILE_NAME );

    string binDir = script->getPropertyValue( props::BIN_DIR );
    string objDir = script->getPropertyValue( props::OBJ_DIR );

    string resourceFile = script->getPropertyValue( props::RESOURCE_FILE );

    string libDirs = script->getPropertyValue( props::LIB_DIRS );
    string libs = script->getPropertyValue( props::LIBS );

    string outputDefFile = script->getPropertyValue( props::OUTPUT_DEF_FILE );
    string outImplibFile = script->getPropertyValue( props::OUT_IMPLIB_FILE );

    string defines = script->getPropertyValue( props::DEFINES );

    binDir = io::absoluteResolvePath( binDir );
    objDir = io::absoluteResolvePath( objDir );

    binDir = io::addSeparatorToDirIfNeed( binDir );
    objDir = io::addSeparatorToDirIfNeed( objDir );

    bool isdll = isDll == "true";

    if ( exeFileName == "" ) {
        messagebuilder b( errors::PROPERTY_EXE_FILE_NAME_NOT_DEFINED_FOR_LINKING );
        b << props::EXE_FILE_NAME;
        throw st_error( nullptr, b.str() );
    }

    if ( resourceFile != "" ) {
        if ( !io::fileExists( resourceFile ) ) {
            messagebuilder b( errors::RESOURCE_FILE_NOT_EXISTS );
            b << resourceFile;
            throw st_error( nullptr, b.str() );
        }
    }

    stringstream ss;
    ss << compiler;

    if ( isdll )
        ss << " -shared";
    if ( isdll && outputDefFile != "" )
        ss << " -Wl,--output-def=" << outputDefFile;
    if ( isdll && outImplibFile != "" )
        ss << " -Wl,--out-implib=" << outImplibFile;

    if ( isdll ) {
        ss << " -o " << binDir << dllFileName;
    } else {
        ss << " -o " << binDir << exeFileName;
    }

    vector<CodeInfo*> sourceCodeInfos = sourceCodeManager->sourceCodeInfos();
    for( CodeInfo* info : sourceCodeInfos )
        ss << " " << objDir << info->objFilePath;    

    if ( resourceFile != "" )
        ss << " " << resourceFile;

    vector<string> libdirsVect = strutil::splitWithDoubleQuotes( libDirs );
    vector<string> libsVect = strutil::splitWithDoubleQuotes( libs );

    stringstream libdirParams;
    stringstream libParams;
    string token;

    for( string libdir : libdirsVect)
        libdirParams << " -L" << libdir;

    for( string lib : libsVect )
        libParams << " -l" << lib;

    ss << libdirParams.str() << libParams.str();

    ss << " " << linkerParams;

    Shell* shell = new Shell();
    shell->setVerbose( isVerbose );
    shell->setShowOutput( isShowCMDOutput );
    shell->pushCommand( ss.str() );

    int exitCode = shell->executa();
    if ( exitCode != 0 )
        throw st_error( nullptr, errors::LINKING_FAILED );

    delete shell;

    manager->executaUserTaskIfExists( tasks::LINK, Task::AFTER );

    if ( isVerbose )
        cout << infos::SUCCESS_IN_LINKING << endl;
}
