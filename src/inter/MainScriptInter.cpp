
#include "MainScriptInter.h"
#include "InterManager.h"
#include "it/FileIterator.h"
#include "../darv/MainScript.h"

MainScriptInter::MainScriptInter( BlockInterDriver* drv ) : BlockInter( drv ) {}

InterResult* MainScriptInter::interpretsLine( Block* block, string line, int lineNumber, void* mgr ) {
    InterManager* manager = (InterManager*)mgr;
    return manager->interpretsProp( (MainScript*)block, line, lineNumber );
}

InterResult* MainScriptInter::interprets( MainScript* script, string str, int lineNumber, void* mgr ) {
    this->script = script;

    return BlockInter::interprets2( nullptr, str, lineNumber, mgr );
}

string MainScriptInter::errorMSGForNotRecognizedStatement() {
    return "Linha nao reconhecida como comando, propriedade ou variavel.";
}

BlockIterator* MainScriptInter::createBlockIterator( string file ) {
    return new FileIterator( file );
}

Block* MainScriptInter::createOrGetBlock( Block* parent ) {
    return script;
}
