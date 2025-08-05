#ifndef INTER_UTIL_H
#define INTER_UTIL_H

#include <string>
#include <stdexcept>

using namespace std;

class inter_error : public runtime_error {

    public:
        inter_error( string msg );

};

namespace interutil {

    string replaceVars( string line, int lineNumber );

}

#endif
