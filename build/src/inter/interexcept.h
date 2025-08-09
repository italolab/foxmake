#ifndef INTER_EXCEPT_H
#define INTER_EXCEPT_H

#include <string>
#include <stdexcept>

using namespace std;

class inter_error : public runtime_error {

    public:
        inter_error( string msg );

};

#endif
