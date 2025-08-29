#ifndef INTER_DRIVER_H
#define INTER_DRIVER_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class InterDriver {

    public:
        virtual bool isValidCMD( string cmdName ) = 0;
        virtual bool isValidProp( string propName ) = 0;
        virtual bool isDefaultTask( string taskName ) = 0;
};

#endif
