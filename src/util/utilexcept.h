#ifndef UTIL_EXCEPT_H
#define UTIL_EXCEPT_H

#include <string>
#include <stdexcept>

using namespace std;

class io_error : public runtime_error {

    public:
        io_error( string msg );

};

class prop_error : public io_error {

    public:
        prop_error( string msg );

};

#endif
