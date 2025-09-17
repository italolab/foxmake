
#ifndef THREAD_PIPE_H
#define THREAD_PIPE_H

#include <thread>

typedef struct TThreadPipe {
    int exitCode;
    std::thread* thread;
} ThreadPipe;

#endif