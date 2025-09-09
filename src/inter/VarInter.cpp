
#include "VarInter.h"
#include "InterManager.h"
#include "../darv/Var.h"

InterResult* VarInter::interprets( 
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

    bool isErrorIfNotFound = false;
    InterResult* replaceResult = manager->replacePropsAndVarsAndDollarSigns(
            value, numberOfLinesReaded, line, isErrorIfNotFound, parent );

    if ( !replaceResult->isInterpreted() )
        return replaceResult;

    delete replaceResult;

    Var* var = new Var( name, value, numberOfLinesReaded, line );
    if ( parent != nullptr )
        parent->putLocalVar( var );

    numberOfLinesReaded++;

    return new InterResult( nullptr, numberOfLinesReaded, line.length() );
}
