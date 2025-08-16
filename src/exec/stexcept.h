#ifndef PROCEXCEPT_H
#define PROCEXCEPT_H

#include "../darv/Statement.h"
#include "../inter/InterResult.h"

#include <stdexcept>
#include <string>

using std::runtime_error;
using std::string;

class st_error : public runtime_error {

    private:
        Statement* st;

    public:
        st_error( string msg );
        st_error( Statement* st, string msg );
        st_error( InterResult* result );

        string message() const;

};

#endif
