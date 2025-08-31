#ifndef INTER_RESULT_H
#define INTER_RESULT_H

#include "../darv/Statement.h"

#include <string>

using std::string;

class InterResult {

    private:
        bool interpreted;
        bool errorFound;
        Statement* statement;
        string line;
        string errorMsg;
        int numberOfLinesReaded;
        int numberOfColumnsReaded;

    public:
        InterResult( bool interpreted );
        InterResult( Statement* statement, int numberOfLines, int numberOfColumns );
        InterResult( string line, int numberOfLines, int numberOfColumns, string errorMsg );

        bool isInterpreted();
        bool isErrorFound();
        Statement* getStatement();
        string getLine();
        string getErrorMsg();
        int getNumberOfLinesReaded();
        int getNumberOfColumnsReaded();

};

#endif
