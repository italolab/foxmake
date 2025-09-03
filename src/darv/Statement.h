#ifndef NO_H
#define NO_H

#include <string>

using std::string;

class Statement {

    private:
        Statement* parent;
        int numberOfLinesReaded;
        string line;

    public:
        Statement( Statement* parent, int lineNumber, string line );
        virtual ~Statement();

        Statement* getRoot();
        Statement* getParent();
        Statement* getTask();
        Statement* getProc();

        int getNumberOfLinesReaded();
        string getLine();

};

#endif
