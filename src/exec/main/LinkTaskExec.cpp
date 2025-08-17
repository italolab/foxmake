
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

void LinkTaskExec::exec( CMD* mainCMD, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    SourceCodeManager* sourceCodeManager = manager->getSourceCodeManager();

    cout << endl << infos::EXECUTING_LINKING << endl;

    MainScript* script = manager->getMainScript();

    string isDll = script->getPropertyValue( props::IS_DLL );

    string compiler = script->getPropertyValue( props::COMPILER );
    string linkerParams = script->getPropertyValue( props::LINKER_PARAMS );

    string exeFileName = script->getPropertyValue( props::EXE_FILE_NAME );
    string dllFileName = script->getPropertyValue( props::DLL_FILE_NAME );

    string binDir = script->getPropertyValue( props::BIN_DIR );
    string objDir = script->getPropertyValue( props::OBJ_DIR );

    string libDirs = script->getPropertyValue( props::LIB_DIRS );
    string dllDirs = script->getPropertyValue( props::DLL_DIRS );

    string outputDefFile = script->getPropertyValue( props::OUTPUT_DEF_FILE );
    string outImplibFile = script->getPropertyValue( props::OUT_IMPLIB_FILE );

    string defines = script->getPropertyValue( props::DEFINES );

    if ( binDir != "" )
        binDir = io::addSeparatorToDirIfNeed( binDir );
    if ( objDir != "" )
        objDir = io::addSeparatorToDirIfNeed( objDir );

    bool isdll = isDll == "true";

    if ( exeFileName == "" ) {
        messagebuilder b( errors::PROPERTY_EXE_FILE_NAME_NOT_DEFINED_FOR_LINKING );
        b << props::EXE_FILE_NAME;
        throw st_error( nullptr, b.str() );
    }

    stringstream ss;
    ss << compiler;

    if ( isdll )
        ss << " -shared";
    if ( isdll && outputDefFile != "" )
        ss << " -Wl,--output-def=" << outputDefFile;
    if ( isdll && outImplibFile != "" )
        ss << " -Wl,--out-implib=" << outImplibFile;

    if ( !isdll )
        ss << " -o " << binDir << exeFileName;

    if ( isdll ) {
        vector<string> libdirsVect = strutil::splitWithDoubleQuotes( libDirs );
        vector<string> dllsVect = strutil::splitWithDoubleQuotes( dllDirs );

        stringstream libdirParams;
        stringstream dllParams;
        string token;

        for( string libdir : libdirsVect)
            libdirParams << " -L" << libdir;

        for( string dll : dllsVect )
            dllParams << " -l" << dll;

        ss << libdirParams.str() << dllParams.str();
    }

    vector<CodeInfo*> sourceCodeInfos = sourceCodeManager->sourceCodeInfos();
    for( CodeInfo* info : sourceCodeInfos )
        ss << " " << objDir << info->objFilePath;

    if ( isdll )
        ss << " -o " << binDir + dllFileName;

    ss << " " << linkerParams;

    Shell* shell = new Shell();
    shell->pushCommand( ss.str() );

    int exitCode = shell->executa();
    if ( exitCode != 0 )
        throw st_error( nullptr, errors::LINKING_FAILED );

    delete shell;

    manager->executaTaskIfExists( tasks::LINK );

    cout << infos::SUCCESS_IN_LINKING << endl;
}
