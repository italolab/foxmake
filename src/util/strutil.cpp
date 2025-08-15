
#include "strutil.h"

#include <sstream>
#include <iostream>

not_end_double_quote_error::not_end_double_quote_error( string msg ) : runtime_error( msg ) {}

namespace strutil {

    vector<string> splitWithDoubleQuotes( string str ) {
        vector<string> splitVect;

        stringstream ss;
        bool charAdded = false;
        size_t len = str.length();
        for( size_t i = 0; i < len; i++ ) {
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

    bool endsWithSome( string str, string prefixes ) {
        istringstream iss( prefixes );
        string prefix;

        while( iss >> prefix )
            if ( endsWith( str, prefix ) )
                return true;
        return false;
    }

    bool isEqualToSome( string str, string values ) {
        istringstream iss( values );
        string value;

        while( iss >> value )
            if ( str == value )
                return true;
        return false;
    }

    bool endsWith( string str, string suffix ) {
        size_t suffixLen = suffix.length();
        size_t strLen = str.length();
        if ( suffixLen <= strLen ) {
            for( size_t i = 0; i < suffixLen; i++ )
                if ( suffix[ suffixLen - i - 1 ] != str[ strLen - i - 1 ] )
                    return false;
            return true;
        }
        return false;
    }

    bool startsWith( string str, string prefix ) {
        size_t prefixLen = prefix.length();
        size_t strLen = str.length();
        if ( prefixLen <= strLen ) {
            for( size_t i = 0; i < prefixLen; i++ )
                if ( prefix[ i ] != str[ i ] )
                    return false;
            return true;
        }
        return false;
    }

    bool isNextToken( string str, int i, string token ) {
        size_t strLen = str.length();
        size_t tokenLen = token.length();
        if ( tokenLen <= strLen-i+1 ) {
            for( size_t j = 0; j < tokenLen; j++ )
                if ( str[ i+j ] != token[ j ] )
                    return false;
            return true;
        }
        return false;
    }

    string trim( string str ) {
        stringstream ss;
        size_t len = str.length();
        for( size_t i = 0; i < len; i++ )
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

    string removeStartWhiteSpaces( string str ) {
        int len = str.length();

        int i = 0;
        bool notWhiteSpace = false;
        while( !notWhiteSpace && i < len ) {
            if ( isWhiteSpace( str[ i ] ) ) {
                i++;
            } else {
                notWhiteSpace = true;
            }
        }

        if ( i < len )
            return str.substr( i, len-i );
        return "";
    }

    bool isWhiteSpace( char ch ) {
        return ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r';
    }

}
