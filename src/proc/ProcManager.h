#ifndef PROC_MANAGER_H
#define PROC_MANAGER_H

#include "../darv/MainScript.h"
#include "../io/cppio.h"

#include <map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class MainProc;
class Proc;

class ProcManager {

    public:
        virtual void exec( int argc, char* argv[] ) = 0;

        virtual void reloadCPPFiles( string srcDir ) = 0;

        virtual bool isDefaultTask( string taskName ) = 0;
        virtual void executaTaskProc( string taskName, CMD* mainCMD ) = 0;
        virtual void executaTaskIfExists( string taskName ) = 0;

        virtual Proc* getProc( string cmdName ) = 0;
        virtual Proc* getTaskProc( string cmdName ) = 0;

        virtual vector<CPPFile*>& getCPPFiles() = 0;
        virtual vector<string> validCMDNames() = 0;

        virtual MainProc* getMainProc() = 0;
        virtual MainScript* getMainScript() = 0;

};


#endif
