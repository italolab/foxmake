#ifndef DEFAULT_TASK_CONFIG_INTER_H
#define DEFAULT_TASK_CONFIG_INTER_H

#include "InterResult.h"
#include "../darv/MainScript.h"

#include <string>

using std::string;

class DefaultTaskConfigInter {

    private:
        vector<string> VALID_FLAGS = {
            "verbose",
            "noverbose",
            "showoutput",
            "noshowoutput"
        };

        void setFlags( DefaultTaskConfig* task, vector<string>& flags );

    public:
        InterResult* interprets( MainScript* parent, string currentLine, int lineNumber, void* mgr );
        
};

#endif