
#include "MainScriptInter.h"
#include "InterManager.h"
#include "it/FileIterator.h"
#include "../darv/MainScript.h"

MainScriptInter::MainScriptInter( BlockInterDriver* drv ) : BlockInter( drv ) {}

InterResult* MainScriptInter::interprets( MainScript* script, string file, int lineNumber, void* mgr ) {
    this->script = script;

    return BlockInter::interpretsBlock( nullptr, file, lineNumber, mgr );
}

InterResult* MainScriptInter::extInterpretsLine( Block* script, BlockIterator* it, string currentLine, int lineNumber, void* mgr ) {
    InterManager* manager = (InterManager*)mgr;

    InterResult* result = manager->interpretsProp( (MainScript*)script, currentLine, lineNumber );
    if ( result->isOk() )
        return result;
    return manager->interpretsGoal( script, it, currentLine, lineNumber );
}

string MainScriptInter::errorMSGForNotRecognizedStatement() {
    return "Linha nao reconhecida como comando, propriedade ou variavel.";
}

BlockIterator* MainScriptInter::createBlockIterator( string file ) {
    return new FileIterator( file );
}

Block* MainScriptInter::getBlock() {
    return script;
}
