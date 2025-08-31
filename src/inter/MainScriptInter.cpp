
#include "MainScriptInter.h"
#include "InterManager.h"
#include "it/FileIterator.h"
#include "../darv/MainScript.h"
#include "../util/strutil.h"

#include "../error_messages.h"

MainScriptInter::~MainScriptInter() {}

InterResult* MainScriptInter::interpretsLine( Block* block, BlockIterator* it, string currentLine, int currentLineNumber, void* mgr ) {
    InterManager* manager = (InterManager*)mgr;

    MainScript* script = (MainScript*)block;

    InterResult* result = manager->interpretsProp( script, currentLine, currentLineNumber );
    if ( !result->isInterpreted() && !result->isErrorFound())
        result = manager->interpretsTask( script, it, currentLine, currentLineNumber );
    if ( !result->isInterpreted() && !result->isErrorFound() )
        result = manager->interpretsDefaultTaskConfig( script, currentLine, currentLineNumber );

    return result;
}

InterResult* MainScriptInter::interpretsEnd( Block* block, string currentLine, int currentLineNumber ) {
    return new InterResult( false );
}

InterResult* MainScriptInter::interprets( MainScript* script, string file, int lineNumber, void* mgr ) {
    FileIterator* it = new FileIterator( file );

    int numberOfLines = 0;
    BlockInterResult* result = BlockInter::interpretsBlock( script, it, lineNumber, numberOfLines, mgr );
    return result->getInterResult();
}
