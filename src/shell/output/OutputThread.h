#ifndef OUTPUT_THREAD_H
#define OUTPUT_THREAD_H

#ifdef _WIN32
    #include "windows.h"
#else

#endif


#include <string>
#include <queue>
#include <thread>
#include <mutex>

using std::string;
using std::queue;

class OutputThread {

    private:
        string name;
        queue<string> outputQueue;
        std::thread* thread;
        bool finishFlag;

        std::mutex mtx;

        void addOutput( string output );

    public:
        OutputThread( string name );

#ifdef _WIN32
        void run( HANDLE hStdOutRead );
#else
        void run( FILE* pipe );
#endif

        void finish();
        bool hasNextOutput();
        string nextOutput();

        string getName();
        bool isFinished();

};

#endif