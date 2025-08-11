
#include "MainScriptInter.h"
#include "InterManager.h"
#include "it/FileIterator.h"
#include "../darv/MainScript.h"


MainScriptInter::MainScriptInter( BlockInterDriver* drv ) : BlockInter( drv ) {}

InterResult* MainScriptInter::interpretsLine( Block* block, string line, int lineNumber, AbstractInterManager* mgr ) {
    InterManager* manager = (InterManager*)mgr;
    return manager->getPropInter()->interpreta( (MainScript*)block, line, lineNumber, manager );
}

InterResult* MainScriptInter::interprets( string str, int lineNumber, AbstractInterManager* mgr ) {
    return BlockInter::interprets2( nullptr, str, lineNumber, mgr );
}

string MainScriptInter::errorMSGForNotRecognizedStatement() {
    return "Linha nao reconhecida como comando, propriedade ou variavel.";
}

BlockIterator* MainScriptInter::createBlockIterator( string file ) {
    return new FileIterator( file );
}

Block* MainScriptInter::createBlock( Block* parent ) {
    return new MainScript();
}
