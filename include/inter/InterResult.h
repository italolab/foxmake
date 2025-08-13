#ifndef INTER_RESULT_H
#define INTER_RESULT_H

#include "../darv/Statement.h"

#include <string>

using std::string;

class InterResult {

    private:
        bool interpreted;
        bool errorFound;
        Statement* no;
        string line;
        string errorMsg;
        int numberOfLines;
        int numberOfColumns;

    public:
        InterResult( bool interpreted );
        InterResult( Statement* no, int numberOfLines );
        InterResult( Statement* no, int numberOfLines, int numberOfColumns );

        InterResult( string line, string errorMsg );
        InterResult( string line, int numberOfLines, string errorMsg );
        InterResult( string line, int numberOfLines, int numberOfColumns, string errorMsg );

        bool isInterpreted();
        bool isErrorFound();
        Statement* getStatement();
        string getLine();
        string getErrorMsg();
        int getNumberOfLines();

};

#endif
