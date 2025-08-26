#ifndef ST_EXCEPT_H
#define ST_EXCEPT_H

#include "../darv/Statement.h"
#include "../inter/InterResult.h"
#include "../output/Output.h"

#include <stdexcept>
#include <string>
#include <vector>

using std::runtime_error;
using std::string;
using std::vector;

class st_error : public runtime_error {

    private:
        int lineNumber;
        string line;
        bool isShowLine;

    public:
        st_error( Statement*, string );
        st_error( InterResult* );

        void printMessage( Output& out, Output& err ) const;

};

#endif
