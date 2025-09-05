
#include "hashutil.h"

#include <ctime>
#include <cstdlib>

#include <string>

using std::string;

namespace hashutil {

    size_t currentHash() {
        srand( time( NULL ) );
        int currTime = time( NULL );
        int randomNum = rand();

        std::hash<string> hash_fn;
        return hash_fn( std::to_string( currTime ) + std::to_string( randomNum ) );
    }

}