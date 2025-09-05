
#include "hashutil.h"

#include <ctime>
#include <cstdlib>

#include <string>

using std::string;

#include <iostream>
using namespace std;

namespace hashutil {

    size_t currentHash() {
        srand( time( NULL ) );
        int currTime = time( NULL );
        int randomNum = rand();

        string numstr = std::to_string( currTime ) + std::to_string( randomNum );

        std::hash<string> hash_fn;
        return hash_fn( numstr );
    }

}