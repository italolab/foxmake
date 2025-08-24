
#include "ByNameFileFilter.h"
#include "../io.h"
#include "../../util/strutil.h"

#include <iostream>
using namespace std;

ByNameFileFilter::ByNameFileFilter( string file1 ) : file1( file1 ) {}

bool ByNameFileFilter::match( string file2 ) {
    bool isNamesMatch = false;
    bool isExtsMatch = false;

    string name1 = io::fileNameWithoutExtension( file1 );
    string name2 = io::fileNameWithoutExtension( file2 );

    size_t i = name1.find( '*' );
    if ( i != string::npos ) {
        if ( name1 == "*" ) {
            isNamesMatch = true;
        } else {
            string startName = name1.substr( 0, i );
            string endName = name1.substr( i+1, name1.length()-i+1 );
            
            isNamesMatch = strutil::startsWith( name2, startName ) && strutil::endsWith( name2, endName );
        }
    } else {
        isNamesMatch = ( name1 == name2 );
    }

    string ext1 = io::extension( file1 );
    string ext2 = io::extension( file2 );
    if ( ext1 == "" ) { 
        isExtsMatch = ext2 == "" || name1 == "*";
    } else if ( ext1 == "*" ) {
        isExtsMatch = true;
    } else {
        isExtsMatch = ( ext1 == ext2 );
    }

    return ( isNamesMatch && isExtsMatch );
}