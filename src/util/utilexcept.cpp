
#include "utilexcept.h"

io_error::io_error( string msg ) : runtime_error( msg ) {

}

not_end_double_quote_error::not_end_double_quote_error( string msg ) : runtime_error( msg ) {

}
