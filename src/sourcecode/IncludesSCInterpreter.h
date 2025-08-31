#ifndef INCLUDES_SC_INTERPRETER_H
#define INCLUDES_SC_INTERPRETER_H

#include "CodeInfo.h"

#include <string>
#include <map>
#include <fstream>

using std::string;
using std::map;
using std::ifstream;

class IncludesSCInterpreter {

    public:
        bool interpretsIncludes( 
                map<string, CodeInfo*>& allCodeInfosMap,
                string line, 
                string filePath );

};

#endif