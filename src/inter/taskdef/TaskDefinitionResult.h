#ifndef TASK_CONFIG_RESULT_H
#define TASK_CONFIG_RESULT_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class TaskDefinitionResult {

    private:
        string taskName;
        vector<string> flags;
        int status;
        string errorMsg;
        bool finish;

    public:
        static const int OK = 0;
        static const int NO_CONFIG = 1;
        static const int ERROR = 2;

        TaskDefinitionResult( string taskName, vector<string>& flags, bool finish );
        TaskDefinitionResult( string errorMsg );
        TaskDefinitionResult( int status );

        string getTaskName();
        vector<string>& getFlags();
        int getStatus();
        string getErrorMsg();
        bool isFinish();

};

#endif