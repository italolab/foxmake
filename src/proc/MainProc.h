#ifndef MAIN_PROC_H
#define MAIN_PROC_H

#include "Proc.h"
#include "ProcManager.h"
#include "../inter/block/MainInter.h"

#include <string>

using namespace std;

class MainProc : public Proc {

    private:
        void procCMDs( ProcManager* mgr );

        void clean( CMDInter* inter, MainInter* mainInter );
        void compileAndLink( CMDInter* inter, MainInter* mainInter, bool isCompile, bool isLink );
        void copyFiles( CMDInter* inter, MainInter* mainInter );

        void appCopyFileOrDirectoryToBuild( string path, string buildDir );
        void appDeleteFileOrDirectory( string path );

    public:
        MainProc( string cmdName );

        void processa( CMDInter* inter, ProcManager* mgr );

};

#endif
