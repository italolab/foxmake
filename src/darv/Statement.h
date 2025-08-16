#ifndef NO_H
#define NO_H

#include <string>

using std::string;

class Statement {

    private:
        Statement* parent;
        int lineNumber;
        string line;

    public:
        Statement( Statement* parent, int lineNumber, string line );
        virtual ~Statement();

        Statement* getParent();

        int getLineNumber();
        string getLine();
};

#endif
