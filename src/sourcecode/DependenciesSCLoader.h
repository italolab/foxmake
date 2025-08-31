#ifndef DEPENDENCIES_SC_MANAGER_H
#define DEPENDENCIES_SC_MANAGER_H

#include "CodeInfo.h"
#include "IncludesSCInterpreter.h"
#include "ClassesSCInterpreter.h"

#include <string>
#include <map>
#include <vector>

using std::string;
using std::map;
using std::vector;

class DependenciesSCLoader {

    private:
        IncludesSCInterpreter* includesSCInterpreter;
        ClassesSCInterpreter* classesSCInterpreter;

        bool loadDepencenciesForFile( 
                map<string, CodeInfo*>& allCodeInfosMap, 
                map<string, string>& classToIncludeMap,
                string filePath );

        string findFilePathForClassName( 
            map<string, CodeInfo*>& allCodeInfosMap, 
            vector<string>& includes, 
            string className,
            string filePath );

    public:
        DependenciesSCLoader();
        virtual ~DependenciesSCLoader();

        bool loadDependencies( 
                map<string, CodeInfo*>& allCodeInfosMap,
                map<string, string>& classToIncludeMap );

};

#endif