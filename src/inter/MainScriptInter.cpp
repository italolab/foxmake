
#include "MainScriptInter.h"
#include "InterManager.h"
#include "it/FileIterator.h"
#include "../darv/MainScript.h"
#include "../util/strutil.h"

#include "../error_messages.h"

MainScriptInter::~MainScriptInter() {}

InterResult* MainScriptInter::interpretsLine( 
            Block* block, 
            BlockIterator* it, 
            string currentLine, 
            int& numberOfLinesReaded, 
            void* mgr ) {

    InterManager* manager = (InterManager*)mgr;

    MainScript* script = (MainScript*)block;

    InterResult* result = manager->interpretsProp( script, currentLine, numberOfLinesReaded );
    if ( !result->isInterpreted() && !result->isErrorFound())
        result = manager->interpretsTask( script, it, currentLine, numberOfLinesReaded );
    if ( !result->isInterpreted() && !result->isErrorFound() )
        result = manager->interpretsDefaultTaskConfig( script, currentLine, numberOfLinesReaded );

    return result;
}

InterResult* MainScriptInter::interprets( 
            MainScript* script, 
            string file, 
            void* mgr ) {

    FileIterator* it = new FileIterator( file );

    string endToken = "";
    int numberOfLinesReaded = 0;
    return BlockInter::interpretsBlock( script, it, numberOfLinesReaded, endToken, nullptr,  mgr );
}
