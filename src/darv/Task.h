#ifndef TASK_H
#define TASK_H

#include "Block.h"

#include <string>

using std::string;

class Task : public Block {

    private:
        string name;
        bool beforeFlag;
        bool verboseFlag;
        bool showCMDOutputFlag;

    public:
        static const bool BEFORE = true;
        static const bool AFTER = false;

        Task( Statement* parent, int lineNumber, string line );

        string getName();
        bool isBefore();

        void setName( string name );
        void setBefore( bool flag );

};

#endif
