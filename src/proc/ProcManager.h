#ifndef PROC_MANAGER_H
#define PROC_MANAGER_H

#include "../darv/MainScript.h"

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

        virtual MainProc* getMainProc() = 0;
        virtual MainScript* getMainScript() = 0;
        virtual Proc* getProc( string cmdName ) = 0;
        virtual vector<string> validCMDNames() = 0;

};


#endif
