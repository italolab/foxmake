#ifndef INTER_RESULT_H
#define INTER_RESULT_H

#include <string>

using std::string;

class InterResult {

    private:
        bool ok;
        string errorMsg;
        int numberOfLines;

    public:
        InterResult( int numberOfLines );
        InterResult( int numberOfLines, string errorMsg );

        bool isOk();
        string getErrorMsg();
        int getNumberOfLines();

};

#endif
