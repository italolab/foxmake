#ifndef DEPENDENCIES_SC_MANAGER_H
#define DEPENDENCIES_SC_MANAGER_H

#include "CodeInfo.h"
#include "IncludesSCInterpreter.h"
#include "ClassesSCInterpreter.h"

#include <string>
#include <map>

using std::string;
using std::map;

class DependenciesSCLoader {

    private:
        IncludesSCInterpreter* includesSCInterpreter;
        ClassesSCInterpreter* classesSCInterpreter;

        bool loadDepencenciesForFile( 
                map<string, CodeInfo*>& allCodeInfosMap, 
                map<string, string>& classToIncludeMap,
                string filePath );

    public:
        DependenciesSCLoader();
        virtual ~DependenciesSCLoader();

        bool loadDependencies( 
                map<string, CodeInfo*>& allCodeInfosMap,
                map<string, string>& classToIncludeMap );

};

#endif