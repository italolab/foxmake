
#include "ConcreteBlockInter.h"
#include "InterManager.h"

ConcreteBlockInter::~ConcreteBlockInter() {}

InterResult* ConcreteBlockInter::interpretsLine( 
            Block* block, 
            BlockIterator* it, 
            string currentLine, 
            int& numberOfLinesReaded, 
            void* mgr ) {

    InterManager* manager = (InterManager*)mgr;

    return manager->interpretsVarAttr( block, currentLine, numberOfLinesReaded );
}

InterResult* ConcreteBlockInter::interprets( 
            Block* parent,
            BlockIterator* it, 
            int& numberOfLinesReaded, 
            void* mgr ) {

    string endToken = "";
    
    return BlockInter::interpretsBlock( 
                parent, 
                it, 
                numberOfLinesReaded, 
                endToken, 
                nullptr, 
                mgr );
}