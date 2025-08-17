#ifndef ST_EXCEPT_H
#define ST_EXCEPT_H

#include "../darv/Statement.h"
#include "../inter/InterResult.h"

#include <stdexcept>
#include <string>
#include <vector>

using std::runtime_error;
using std::string;
using std::vector;

class st_error : public runtime_error {

    private:
        Statement* st;

    public:
        st_error( Statement*, string );
        st_error( InterResult* );

        string message() const;

};

#endif
