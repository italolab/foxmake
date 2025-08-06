#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

class not_end_double_quote_error : public runtime_error {

    public:
        not_end_double_quote_error( string msg );

};

namespace strutil {

    vector<string> splitWithDoubleQuotes( string str );

    bool endsWith( string str, string suffix );
    string trim( string str );

}

#endif
