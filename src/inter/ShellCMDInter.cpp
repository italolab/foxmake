
#include "ShellCMDInter.h"
#include "../darv/ShellCMD.h"
#include "../util/strutil.h"

InterResult* ShellCMDInter::interprets( Block* parent, string line, int lineNumber, void* mgr ) {
    if ( line.length() == 0 )
        return new InterResult( false );
    if ( line[ 0 ] != '@' )
        return new InterResult( false );

    string cmdstr = line.substr( 1, line.length()-1 );
    cmdstr = strutil::removeStartWhiteSpaces( cmdstr );

    InterResult* replaceResult = Inter::replacePropsAndVarsAndDollarSigns( cmdstr, lineNumber, parent );
    if ( !replaceResult->isInterpreted() )
        return replaceResult;

    delete replaceResult;

    ShellCMD* shellCMD = new ShellCMD( parent, cmdstr, lineNumber, line );

    if ( parent != nullptr )
        parent->addStatement( shellCMD );

    return new InterResult( nullptr, 1, line.length() );

}
