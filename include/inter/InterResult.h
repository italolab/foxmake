#ifndef INTER_RESULT_H
#define INTER_RESULT_H

#include "../darv/No.h"

#include <string>

using std::string;

class InterResult {

    private:
        bool ok;
        No* no;
        string errorMsg;
        int numberOfLines;
        int numberOfColumns;

    public:
        InterResult( No* no, int numberOfLines );
        InterResult( No* no, int numberOfLines, int numberOfColumns );

        InterResult( string errorMsg );
        InterResult( int numberOfLines, string errorMsg );
        InterResult( int numberOfLines, int numberOfColumns, string errorMsg );

        bool isOk();
        No* getNo();
        string getErrorMsg();
        int getNumberOfLines();

};

#endif
