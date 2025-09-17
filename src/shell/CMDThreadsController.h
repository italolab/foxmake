#ifndef CMD_THREADS_CONTROLLER_H
#define CMD_THREADS_CONTROLLER_H

#include "shell.h"
#include "threadpipe.h"
#include "output/OutputController.h"

class CMDThreadsController {

    private:
        Shell* shell;
        OutputController* outputController;

        std::mutex mtx;
        std::condition_variable cv;
        bool isWait;
        long numberOfThreads;

        vector<ThreadPipe*> threadPipes;

    public:
        CMDThreadsController( Shell* shell, OutputController* outputController );

        void run();
        void commandProcessedNotify();

        vector<ThreadPipe*>& getThreadPipes();

};

#endif