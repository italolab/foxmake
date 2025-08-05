
#include "util.h"

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
