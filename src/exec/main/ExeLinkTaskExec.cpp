
#include "ExeLinkTaskExec.h"
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

using std::string;
using std::vector;
using std::stringstream;

void ExeLinkTaskExec::exec( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    SourceCodeManager* sourceCodeManager = manager->getSourceCodeManager();

    Output& out = manager->out;
    Output& inf = manager->inf;
    bool isVerbose = manager->getArgManager()->isVerbose( tasks::LINK );
    bool isShowCMDOutput = manager->getArgManager()->isShowCMDOutput( tasks::LINK );

    MainScript* script = manager->getMainScript();

    string compiler = script->getPropertyValue( props::COMPILER );
    string linkerParams = script->getPropertyValue( props::LINKER_PARAMS );

    string outputFileName = script->getPropertyValue( props::OUTPUT_FILE_NAME );

    string binDir = script->getPropertyValue( props::BIN_DIR );
    string objDir = script->getPropertyValue( props::OBJ_DIR );

    string resourceFile = script->getPropertyValue( props::RESOURCE_FILE );

    string libDirs = script->getPropertyValue( props::LIB_DIRS );
    string libs = script->getPropertyValue( props::LIBS );

    string defines = script->getPropertyValue( props::DEFINES );

    binDir = io::absoluteResolvePath( binDir );
    objDir = io::absoluteResolvePath( objDir );

    binDir = io::addSeparatorToDirIfNeed( binDir );
    objDir = io::addSeparatorToDirIfNeed( objDir );

    if ( outputFileName == "" ) {
        messagebuilder b( errors::PROPERTY_NOT_DEFINED_FOR_LINKING );
        b << props::OUTPUT_FILE_NAME;
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

    ss << " -o " << binDir << outputFileName;    

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

    Shell* shell = new Shell( out, inf );
    shell->setVerbose( isVerbose );
    shell->setShowOutput( isShowCMDOutput );
    shell->pushCommand( ss.str() );

    int exitCode = shell->executa();
    if ( exitCode != 0 )
        throw st_error( nullptr, errors::LINKING_FAILED );

    delete shell;
}