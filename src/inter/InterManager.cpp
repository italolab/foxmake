
#include "InterManager.h"
#include "../util/strutil.h"

#include "../error_messages.h"

#include <stdexcept>

using std::runtime_error;

InterManager::InterManager( InterDriver* drv ) {
    this->drv = drv;

    this->concreteBlockInter = new ConcreteBlockInter();
    this->mainScriptInter = new MainScriptInter();
    this->taskInter = new TaskInter();
    this->procInter = new ProcInter();
    this->taskDefinitionInter = new TaskDefinitionInter();
    this->defaultTaskConfigInter = new DefaultTaskConfigInter();
    this->cmdInter = new CMDInter();
    this->shellCMDInter = new ShellCMDLineInter();
    this->propInter = new PropInter();
    this->noInBlockVarAttrInter = new NoInBlockVarAttrInter();
    this->varAttrInter = new VarAttrInter();

    this->ifInter = new IFInter();
    this->propsAndVarsReplacer = new PropsAndVarsReplacer();

    this->ifPreProcessor = new IFPreProcessor();
}

InterManager::~InterManager() {
    delete concreteBlockInter;
    delete mainScriptInter;
    delete taskInter;
    delete procInter;
    delete taskDefinitionInter;
    delete defaultTaskConfigInter;
    delete cmdInter;
    delete shellCMDInter;
    delete propInter;
    delete noInBlockVarAttrInter;
    delete varAttrInter;

    delete ifInter;
    delete propsAndVarsReplacer;

    delete ifPreProcessor;
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
    return noInBlockVarAttrInter->interprets( parent, line, numberOfLinesReaded, this );
}

InterResult* InterManager::interpretsProp( MainScript* parent, string line, int& numberOfLinesReaded ) {
    return propInter->interprets( parent, line, numberOfLinesReaded, this );
}

InterResult* InterManager::interpretsVarAttr( Block* parent, string line, int& numberOfLinesReaded ) {
    return varAttrInter->interprets( parent, line, numberOfLinesReaded, this );
}

InterResult* InterManager::interpretsBlock( Block* block, BlockIterator* it, int& numberOfLinesReaded ) {
    return concreteBlockInter->interprets( block, it, numberOfLinesReaded, this );
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

InterResult* InterManager::interpretsIF( Block* parent, BlockIterator* it, string currentLine, int& numberOfLinesReaded, bool isAddToParent ) {
    return ifInter->interprets( parent, it, currentLine, numberOfLinesReaded, isAddToParent, this );
}

InterResult* InterManager::replacePropsAndVarsAndDollarSigns( string& text, int& numberOfLinesReaded, string line, Block* block ) {
    return propsAndVarsReplacer->replacePropsAndVarsAndDollarSigns( text, numberOfLinesReaded, line, block );
}

InterResult* InterManager::ifPreProcess( Block* block, BlockIterator* it, string& preProcessedText ) {
    return ifPreProcessor->preProcess( block, it, preProcessedText, this );
}

bool InterManager::isPredefinedVar( Statement* st, string name ) {    
    if ( st != nullptr ) {
        Statement* root = st->getRoot();
        if ( root == nullptr )
            return false;

        MainScript* script = (MainScript*)root;
        Var* var = script->getPredefinedVar( name );

        return ( var != nullptr );
    }

    return false;
}

bool InterManager::isPropOrVar( Block* block, string name ) {
    Statement* root = block->getRoot();
    if ( root == nullptr )
        throw runtime_error( errors::runtime::NULL_ROOT_STATEMENT );

    MainScript* script = (MainScript*)root;
    Prop* prop = script->getProperty( name );
    if ( prop != nullptr )
        return true;

    Var* var = block->getVar( name );
    if ( var == nullptr )
        var = script->getPredefinedVar( name );

    return ( var != nullptr );
}

string InterManager::getPropOrVarValue( Block* block, string name ) {
    Statement* root = block->getRoot();
    if ( root == nullptr )
        throw runtime_error( errors::runtime::NULL_ROOT_STATEMENT );

    MainScript* script = (MainScript*)root;
    Prop* prop = script->getProperty( name );
    if ( prop != nullptr )
        return prop->getValue();

    Var* var = block->getVar( name );
    if ( var == nullptr )
        var = script->getPredefinedVar( name );

    if ( var != nullptr )
        return var->getValue();

    return "";
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
