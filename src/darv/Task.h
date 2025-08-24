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
        bool showErrorsFlag;

    public:
        const static bool BEFORE = true;
        const static bool AFTER = false;

        Task( Statement* parent, int lineNumber, string line );

        string getName();
        bool isBefore();
        bool isVerbose();
        bool isShowErrors();

        void setName( string name );
        void setBefore( bool flag );
        void setVerbose( bool flag );
        void setShowErrors( bool flag );

};

#endif
