#include "VarInter.h"
#include "InterManager.h"
#include "../darv/VarAttr.h"

InterResult* VarAttrInter::interprets( 
            Block* parent, string line, int& numberOfLinesReaded, void* mgr ) {
    if ( line.length() == 0 )
        return new InterResult( false );
    if ( line[ 0 ] != '$' )
        return new InterResult( false );

    size_t i = line.find( '=' );
    if ( i == string::npos )
        return new InterResult( false );

    string name = line.substr( 1, i-1 );
    string value = line.substr( i+1, line.length()-i );

    VarAttr* varAttr = new VarAttr( parent, name, value, numberOfLinesReaded, line );
    if ( parent != nullptr )
        parent->addStatement( varAttr );    

    numberOfLinesReaded++;

    return new InterResult( varAttr, numberOfLinesReaded, line.length() );
}