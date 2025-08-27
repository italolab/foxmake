#ifndef GOAL_INTER_H
#define GOAL_INTER_H

#include "Inter.h"
#include "it/BlockIterator.h"
#include "../darv/MainScript.h"
#include "../darv/Task.h"

#include <vector>

using std::vector;

class TaskInter : public Inter {

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
            void* mgr );
        
        void setFlags( Task* task, vector<string>& flags );
        TaskExecution getTaskExecution( vector<string>& flags );
        bool isValidFlag( string flag );

    public:
        InterResult* interprets( MainScript* parent, BlockIterator* it, string currentLine, int lineNumber, void* mgr );

};

#endif