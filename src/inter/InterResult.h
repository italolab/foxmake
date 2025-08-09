#ifndef INTER_RESULT_H
#define INTER_RESULT_H

#include <string>

using std::string;

class InterResult {

    private:
        bool ok;
        string errorMsg;
        int numberOfLines;
        int numberOfColumns;

    public:
        InterResult( int numberOfLines );
        InterResult( string errorMsg );
        InterResult( int numberOfLines, int numberOfColumns );
        InterResult( int numberOfLines, string errorMsg );
        InterResult( int numberOfLines, int numberOfColumns, string errorMsg );

        bool isOk();
        string getErrorMsg();
        int getNumberOfLines();

};

#endif
