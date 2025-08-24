#ifndef DEFAULT_TASK_H
#define DEFAULT_TASK_H

#include "Statement.h"

#include <string>

using std::string;

class DefaultTaskConfig : public Statement {

    private:
        string name;
        bool verboseFlag;
        bool showCMDOutputFlag;

    public:
        DefaultTaskConfig( Statement* parent, string name, int lineNumber, string line );

        string getName();
        bool isVerbose();
        bool isShowCMDOutput();

        void setName( string name );
        void setVerbose( bool flag );
        void setShowCMDOutput( bool flag );

};

#endif