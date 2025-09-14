#include "VarAttrInter.h"
#include "InterManager.h"
#include "../darv/VarAttr.h"
#include "../msg/messagebuilder.h"

#include "../error_messages.h"

InterResult* VarAttrInter::interprets( 
            Block* parent, string line, int& numberOfLinesReaded, void* mgr ) {

    InterManager* manager = (InterManager*)mgr;
    
    if ( line.length() == 0 )
        return new InterResult( false );
    if ( line[ 0 ] != '$' )
        return new InterResult( false );

    size_t i = line.find( '=' );
    if ( i == string::npos )
        return new InterResult( false );

    string name = line.substr( 1, i-1 );
    string value = line.substr( i+1, line.length()-i );

    if ( manager->isPredefinedVar( parent, name ) ) {
        messagebuilder b( errors::TRY_CHANGE_PREDEFINED_VAR );
        b << name;
        return new InterResult( line, numberOfLinesReaded, 0, b.str() );
    }

    VarAttr* varAttr = new VarAttr( parent, name, value, numberOfLinesReaded, line );
    if ( parent != nullptr )
        parent->addStatement( varAttr );    

    numberOfLinesReaded++;

    return new InterResult( varAttr, numberOfLinesReaded, line.length() );
}