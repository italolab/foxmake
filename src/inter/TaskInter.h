#ifndef GOAL_INTER_H
#define GOAL_INTER_H

#include "BlockInter.h"
#include "it/BlockIterator.h"
#include "../darv/MainScript.h"
#include "../darv/Task.h"

#include <vector>

using std::vector;

class TaskInter : public BlockInter {

    private:
        const string BEFORE = "before";
        const string AFTER = "after";

        vector<string> VALID_FLAGS = {
            BEFORE,
            AFTER
        };
    
        bool validateFlags( 
            MainScript* script, 
            string taskName, 
            vector<string>& flags,
            string& errorMsg,
            string currentLine,
            void* mgr );
        
        void setFlags( Task* task, vector<string>& flags );
        bool isValidFlag( string flag );

        InterResult* interpretsLine( 
            Block* block, 
            BlockIterator* it, 
            string currentLine, 
            int& numberOfLinesReaded, 
            void* mgr );

        InterResult* interpretsEnd( 
            Block* block, string currentLine, int& numberOfLinesReaded );

    public:
        virtual ~TaskInter();

        InterResult* interprets( 
            MainScript* parent, 
            BlockIterator* it, 
            string currentLine, 
            int& numberOfLinesReaded, 
            void* mgr );

};

#endif