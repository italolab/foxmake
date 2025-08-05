
#include "utilexcept.h"

io_error::io_error( string msg ) : runtime_error( msg ) {

}

prop_error::prop_error( string msg ) : io_error( msg ) {

}
