
#include "hashutil.h"

#include <ctime>
#include <cstdlib>

namespace hashutil {

    size_t currentHash() {
        srand( time( NULL ) );
        int currTime = time( NULL );
        int randomNum = rand();

        std::hash<int> hash_fn;
        return hash_fn( currTime + randomNum );
    }

}