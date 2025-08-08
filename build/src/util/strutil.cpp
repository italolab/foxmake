
#include "strutil.h"

#include <sstream>
#include <iostream>

not_end_double_quote_error::not_end_double_quote_error( string msg ) : runtime_error( msg ) {}

namespace strutil {

    vector<string> splitWithDoubleQuotes( string str ) {
        vector<string> splitVect;

        stringstream ss;
        bool charAdded = false;
        int len = str.length();
        for( int i = 0; i < len; i++ ) {
            if ( str[ i ] == '\"' ) {
                size_t j = str.find( '\"', i+1 );
                if ( j == string::npos ) {
                    throw not_end_double_quote_error( "Aspas duplas de fim nao encontradas." );
                }
                string str2 = str.substr( i+1, j-i-1 );
                splitVect.push_back( str2 );
                i = j;
            } else if ( str[ i ] == ' ' || str[ i ] == '\n' || str[ i ] == '\t' || str[ i ] == '\r' ) {
                if ( charAdded ) {
                    splitVect.push_back( ss.str() );
                    ss.str( "" );
                    charAdded = false;
                }
            } else {
                ss << str[ i ];
                charAdded = true;
            }
        }

        if ( charAdded )
            splitVect.push_back( ss.str() );

        return splitVect;
    }

    bool endsWith( string str, string suffix ) {
        int suffixLen = suffix.length();
        int strLen = str.length();
        if ( suffixLen <= strLen ) {
            for( int i = 0; i < suffixLen; i++ )
                if ( suffix[ suffixLen - i - 1 ] != str[ strLen - i - 1 ] )
                    return false;
            return true;
        }
        return false;
    }

    bool startsWith( string str, string prefix ) {
        int prefixLen = prefix.length();
        int strLen = str.length();
        if ( prefixLen <= strLen ) {
            for( int i = 0; i < prefixLen; i++ )
                if ( prefix[ i ] != str[ i ] )
                    return false;
            return true;
        }
        return false;
    }


    string trim( string str ) {
        stringstream ss;
        int len = str.length();
        for( int i = 0; i < len; i++ )
            if ( str[ i ] != ' ' && str[ i ] != '\t' && str[ i ] != '\r' && str[ i ] != '\n' )
                ss << str[ i ];
        return ss.str();
    }

    string replace( string str, string replaceStr, string newReplaceStr ) {
        string newStr = str;
        size_t i = newStr.find( replaceStr );
        if ( i != string::npos ) {
            int replaceStrLen = replaceStr.length();
            newStr.replace( i, replaceStrLen, newReplaceStr );
        }
        return newStr;
    }

}
