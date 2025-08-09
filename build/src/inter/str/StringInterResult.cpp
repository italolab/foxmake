
#include "StringInterResult.h"

StringInterResult::StringInterResult( int numberOfColumns ) : InterResult( 0, numberOfColumns ) {}

StringInterResult::StringInterResult( string errorMsg ) : InterResult( errorMsg ) {}
