#ifndef TEXT_OUTPUT_H
#define TEXT_OUTPUT_H

#include "Output.h"

class TextOutput : public Output {

    public:
        Output& operator<<( string text );

};

#endif