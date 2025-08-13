#ifndef NO_H
#define NO_H

#include <string>

using std::string;

class Statement {

    private:
        Statement* parent;
        int lineNumber;

    public:
        Statement( Statement* parent, int lineNumber );

        Statement* getParent();

        int getLineNumber();
};

#endif
