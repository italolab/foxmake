#ifndef DEFAULT_TASK_H
#define DEFAULT_TASK_H

#include "Statement.h"

#include <string>

using std::string;

class DefaultTaskConfig : public Statement {

    private:
        string name;
        bool verboseFlag;
        bool showOutputFlag;

    public:
        DefaultTaskConfig( Statement* parent, string name, int lineNumber, string line );

        string getName();
        bool isVerbose();
        bool isShowOutput();

        void setName( string name );
        void setVerbose( bool flag );
        void setShowOutput( bool flag );

};

#endif