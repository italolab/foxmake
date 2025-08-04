
#include "appexcept.h"

io_error::io_error( string msg ) : runtime_error( msg ) {

}

app_error::app_error( string msg ) : runtime_error( msg ) {

}
