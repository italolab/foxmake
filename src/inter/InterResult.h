#ifndef INTER_RESULT_H
#define INTER_RESULT_H

#include "../darv/No.h"

#include <string>

using std::string;

class InterResult {

    private:
        bool interpreted;
        bool errorFound;
        No* no;
        string line;
        string errorMsg;
        int numberOfLines;
        int numberOfColumns;

    public:
        InterResult( bool interpreted );
        InterResult( No* no, int numberOfLines );
        InterResult( No* no, int numberOfLines, int numberOfColumns );

        InterResult( string line, string errorMsg );
        InterResult( string line, int numberOfLines, string errorMsg );
        InterResult( string line, int numberOfLines, int numberOfColumns, string errorMsg );

        bool isInterpreted();
        bool isErrorFound();
        No* getNo();
        string getLine();
        string getErrorMsg();
        int getNumberOfLines();

};

#endif
