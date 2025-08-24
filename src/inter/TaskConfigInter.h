#ifndef TASK_CONFIG_INTER_H
#define TASK_CONFIG_INTER_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class TaskConfigInter {

    private:
        bool isValidFlag( vector<string>& validFlags, string flag );

    public:
        static const int OK = 0;
        static const int NO_CONFIG = 1;
        static const int ERROR = 2;
        
        void interpretsConfig( 
                    string& taskName, 
                    vector<string>& flags, 
                    int& status, 
                    string& errorFlag,
                    vector<string>& validFlags,
                    string currentLine,
                    char finalizer, 
                    void* mgr );

};

#endif