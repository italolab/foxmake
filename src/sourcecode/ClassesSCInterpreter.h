#ifndef CLASSES_SC_INTERPRETER_H
#define CLASSES_SC_INTERPRETER_H

#include "CodeInfo.h"

#include <string>
#include <map>
#include <fstream>

using std::string;
using std::map;
using std::ifstream;

class ClassesSCInterpreter {

    public:
        void interpretsClass( 
                map<string, CodeInfo*>& allCodeInfosMap,
                ifstream& in, 
                string line, 
                string filePath );

};

#endif