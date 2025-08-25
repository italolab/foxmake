#ifndef TASK_CONFIG_RESULT_H
#define TASK_CONFIG_RESULT_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class TaskConfigResult {

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

        TaskConfigResult( string taskName, vector<string>& flags, bool finish );
        TaskConfigResult( string errorMsg );
        TaskConfigResult( int status );

        string getTaskName();
        vector<string>& getFlags();
        int getStatus();
        string getErrorMsg();
        bool isFinish();

};

#endif