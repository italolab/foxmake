#ifndef INFO_OUTPUT_H
#define INFO_OUTPUT_H

#include "Output.h"

class InfoOutput : public Output {

    public:
        Output& operator<<( string text );

};

#endif