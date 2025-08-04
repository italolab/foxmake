#ifndef IO_ERROR_H
#define IO_ERROR_H

#include <stdexcept>
#include <string>

using namespace std;

class io_error : public runtime_error {

    public:
        io_error( string msg );

};

class app_error : public runtime_error {

    public:
        app_error( string msg );

};

#endif
