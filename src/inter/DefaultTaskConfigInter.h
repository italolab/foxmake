#ifndef DEFAULT_TASK_CONFIG_INTER_H
#define DEFAULT_TASK_CONFIG_INTER_H

#include "InterResult.h"
#include "../darv/MainScript.h"

#include <string>

using std::string;

class DefaultTaskConfigInter {

    private:
        const string VERBOSE = "verbose";
        const string NOVERBOSE = "noverbose";
        const string SHOWOUTPUT = "showoutput";
        const string NOSHOWOUTPUT = "noshowoutput";

        vector<string> VALID_FLAGS = {
            VERBOSE,
            NOVERBOSE,
            SHOWOUTPUT,
            NOSHOWOUTPUT
        };

        void setFlags( DefaultTaskConfig* task, vector<string>& flags );

    public:
        InterResult* interprets( MainScript* parent, string currentLine, int lineNumber, void* mgr );
        
};

#endif