#ifndef ERROR_OUTPUT_H
#define ERROR_OUTPUT_H

#include "Output.h"

class ErrorOutput : public Output {

    public:
        Output& operator<<( string text );

};

#endif