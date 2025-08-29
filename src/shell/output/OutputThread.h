#ifndef OUTPUT_THREAD_H
#define OUTPUT_THREAD_H

#ifdef _WIN32
    #include "windows.h"
#else

#endif


#include <string>
#include <sstream>
#include <queue>
#include <thread>
#include <mutex>

using std::string;
using std::queue;
using std::stringstream;

class OutputThread {

    private:
        string name;
        std::thread* thread;
        bool finishFlag;

        stringstream buffer;
        int bufferLen;

        std::mutex mtx;

    public:
        OutputThread( string name );

        void run( FILE* pipe );
        void finish();
        bool hasNextOutput();
        string nextOutput();

        string getName();
        bool isFinished();

};

#endif