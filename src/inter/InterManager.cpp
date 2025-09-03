
#include "InterManager.h"
#include "../util/strutil.h"

InterManager::InterManager( InterDriver* drv ) {
    this->drv = drv;

    this->mainScriptInter = new MainScriptInter();
    this->taskInter = new TaskInter();
    this->procInter = new ProcInter();
    this->taskDefinitionInter = new TaskDefinitionInter();
    this->defaultTaskConfigInter = new DefaultTaskConfigInter();
    this->cmdInter = new CMDInter();
    this->shellCMDInter = new ShellCMDLineInter();
    this->propInter = new PropInter();
    this->varInter = new VarInter();
}

InterManager::~InterManager() {
    delete mainScriptInter;
    delete taskInter;
    delete procInter;
    delete taskDefinitionInter;
    delete defaultTaskConfigInter;
    delete cmdInter;
    delete shellCMDInter;
    delete propInter;
    delete varInter;
}

InterResult* InterManager::interpretsMainCMD( int argc, char* argv[] ) {
    return cmdInter->interpretsMainCMD( argc, argv, this );
}

InterResult* InterManager::interpretsCMD( Block* parent, string line, int& numberOfLinesReaded ) {
    return cmdInter->interprets( parent, line, numberOfLinesReaded, this );
}

InterResult* InterManager::interpretsShellCMD( Block* parent, BlockIterator* it, string currentLine, int& numberOfLinesReaded ) {
    return shellCMDInter->interprets( parent, it, currentLine, numberOfLinesReaded, this );
}

InterResult* InterManager::interpretsVar( Block* parent, string line, int& numberOfLinesReaded ) {
    return varInter->interprets( parent, line, numberOfLinesReaded, this );
}

InterResult* InterManager::interpretsProp( MainScript* parent, string line, int& numberOfLinesReaded ) {
    return propInter->interprets( parent, line, numberOfLinesReaded, this );
}

InterResult* InterManager::interpretsMainScript( MainScript* script, string file ) {
    return mainScriptInter->interprets( script, file, this );
}

InterResult* InterManager::interpretsTask( MainScript* parent, BlockIterator* it, string currentLine, int& numberOfLinesReaded ) {
    return taskInter->interprets( parent, it, currentLine, numberOfLinesReaded, this );
}

InterResult* InterManager::interpretsProc( MainScript* parent, BlockIterator* it, string currentLine, int& numberOfLinesReaded ) {
    return procInter->interprets( parent, it, currentLine, numberOfLinesReaded, this );
}

InterResult* InterManager::interpretsDefaultTaskConfig( MainScript* script, string currentLine, int& numberOfLinesReaded ) {
    return defaultTaskConfigInter->interprets( script, currentLine, numberOfLinesReaded, this );
}

TaskDefinitionResult* InterManager::interpretsTaskDefinition( string currentLine ) {
    return taskDefinitionInter->interprets( currentLine, this );
}

bool InterManager::isValidCMD( string line ) {
    string line2 = strutil::removeStartWhiteSpaces( line );
    
    size_t i = line2.find( ' ' );
    if ( i == string::npos )
        i = line2.find( '\n' );
    if ( i == string::npos )
        i = line2.find( '\t' );
    if ( i == string::npos )
        i = line2.find( '\t' );

    string cmd;
    if ( i == string::npos )
        cmd = line2;
    else cmd = line2.substr( 0, i );
    
    return drv->isValidCMD( cmd );
}

bool InterManager::isValidProp( string propName ) {
   return drv->isValidProp( propName );
}

bool InterManager::isValidDefaultTask( string taskName ) {
    return drv->isDefaultTask( taskName );
}
