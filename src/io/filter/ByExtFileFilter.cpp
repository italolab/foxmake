
#include "ByExtFileFilter.h"
#include "../../util/strutil.h"

ByExtFileFilter::ByExtFileFilter( string extension ) : ext( extension ) {}

bool ByExtFileFilter::match( string file ) {
    return strutil::endsWith( file, "." + ext );
}


