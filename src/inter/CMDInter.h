#ifndef CMD_INTER_H
#define CMD_INTER_H

#include "Inter.h"
#include "../darv/CMD.h"

#include <string>

class InterManager;

class CMDInter : public Inter{

    private:
        InterResult* interprets( 
                Block* parent, 
                int argc, 
                char* argv[], 
                int& numberOfLinesReaded, 
                void* mgr );

        InterResult* newCMD( 
                CMD** cmd, 
                Block* parent,
                string cmdName, 
                string line,
                int numberOfLinesReaded,  
                int argc, 
                char* argv[] );

        void loadCMDNameAndLine( int argc, char* argv[], string& cmdName, string& cmdLine );
        
    public:
        InterResult* interprets( 
                Block* parent, 
                string line, 
                int& numberOfLinesReaded, 
                void* mgr );
                
        InterResult* interpretsMainCMD( int argc, char* argv[], void* mgr );

};

#endif
