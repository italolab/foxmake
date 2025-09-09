#ifndef VAR_ATTR_EXEC_H
#define VAR_ATTR_EXEC_H

#include "../../darv/VarAttr.h"

#include <string>

using std::string;

class VarAttrExec {

    public:
        void exec( VarAttr* varAttr, void* mgr );

};

#endif
