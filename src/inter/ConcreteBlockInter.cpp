
#include "ConcreteBlockInter.h"

ConcreteBlockInter::~ConcreteBlockInter() {}

InterResult* ConcreteBlockInter::interpretsLine( 
            Block* block, 
            BlockIterator* it, 
            string currentLine, 
            int& numberOfLinesReaded, 
            void* mgr ) {

    return new InterResult( false );
}

InterResult* ConcreteBlockInter::interprets( 
            Block* parent,
            BlockIterator* it, 
            int& numberOfLinesReaded, 
            void* mgr ) {

    string endToken = "";
    return BlockInter::interpretsBlock( parent, it, numberOfLinesReaded, endToken, nullptr,  mgr );
}