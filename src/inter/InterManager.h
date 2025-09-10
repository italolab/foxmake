#ifndef INTER_MANAGER_H
#define INTER_MANAGER_H

#include "InterDriver.h"
#include "ConcreteBlockInter.h"
#include "MainScriptInter.h"
#include "TaskInter.h"
#include "ProcInter.h"
#include "preproc/PreProcessor.h"
#include "DefaultTaskConfigInter.h"
#include "taskdef/TaskDefinitionInter.h"
#include "taskdef/TaskDefinitionResult.h"
#include "CMDInter.h"
#include "ShellCMDLineInter.h"
#include "PropInter.h"
#include "VarInter.h"
#include "VarAttrInter.h"
#include "IFInter.h"
#include "PropsAndVarsReplacer.h"
#include "InterResult.h"
#include "it/BlockIterator.h"

#include "../darv/Block.h"
#include "../darv/MainScript.h"

class InterManager {

    private:
        ConcreteBlockInter* concreteBlockInter;
        MainScriptInter* mainScriptInter;
        TaskInter* taskInter;
        ProcInter* procInter;
        CMDInter* cmdInter;
        ShellCMDLineInter* shellCMDInter;
        PropInter* propInter;
        VarInter* varInter;
        VarAttrInter* varAttrInter;
        DefaultTaskConfigInter* defaultTaskConfigInter;
        TaskDefinitionInter* taskDefinitionInter;

        IFInter* ifInter;

        PropsAndVarsReplacer* propsAndVarsReplacer;

        PreProcessor* preProcessor;
        
        InterDriver* drv;

    public:
        InterManager( InterDriver* drv );
        virtual ~InterManager();

        InterResult* interpretsMainCMD( int argc, char* argv[] );

        InterResult* interpretsCMD( Block* parent, string line, int& numberOfLinesReaded );
        InterResult* interpretsShellCMD( Block* parent, BlockIterator* it, string currentLine, int& numberOfLinesReaded );
        InterResult* interpretsVar( Block* parent, string line, int& numberOfLinesReaded );
        InterResult* interpretsProp( MainScript* parent, string line, int& numberOfLinesReaded );

        InterResult* interpretsVarAttr( Block* parent, string line, int& numberOfLinesReaded );

        InterResult* interpretsBlock( Block* parent, BlockIterator* it, int& numberOfLinesReaded );

        InterResult* interpretsMainScript( MainScript* script, string file );
        InterResult* interpretsTask( MainScript* parent, BlockIterator* it, string currentLine, int& numberOfLinesReaded );
        InterResult* interpretsProc( MainScript* parent, BlockIterator* it, string currentLine, int& numberOfLinesReaded );

        InterResult* interpretsDefaultTaskConfig( MainScript* script, string currentLine, int& numberOfLinesReaded );

        TaskDefinitionResult* interpretsTaskDefinition( string currentLine );

        InterResult* interpretsIF( Block* parent, BlockIterator* it, string currentLine, int& numberOfLinesReaded, bool isAddToParent );

        InterResult* replacePropsAndVarsAndDollarSigns( string& text, int& numberOfLinesReaded, string line, Block* block );

        InterResult* preProcess( Block* block, BlockIterator* it, string& preProcessedText );

        bool isValidCMD( string line );
        bool isValidProp( string propName );
        bool isValidDefaultTask( string taskName );
};

#endif
