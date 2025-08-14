#ifndef PROC_MANAGER_H
#define PROC_MANAGER_H

#include "Proc.h"
#include "TaskProc.h"
#include "main/MainProc.h"
#include "../darv/MainScript.h"
#include "../inter/InterManager.h"
#include "../io/SourceCodeInfoManager.h"

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

class ProcManager {

    public:
        virtual void exec( int argc, char* argv[] ) = 0;

        virtual void executaCMDProc( CMD* cmd ) = 0;

        virtual bool isDefaultTask( string taskName ) = 0;
        virtual void executaTaskProc( string taskName, CMD* mainCMD ) = 0;
        virtual void executaTaskIfExists( string taskName ) = 0;

        virtual vector<string> validCMDNames() = 0;

        virtual MainProc* getMainProc() = 0;
        virtual MainScript* getMainScript() = 0;
        virtual InterManager* getInterManager() = 0;
        virtual SourceCodeInfoManager* getSourceCodeInfoManager() = 0;

};


#endif
