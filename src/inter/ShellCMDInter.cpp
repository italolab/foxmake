
#include "ShellCMDInter.h"
#include "../darv/ShellCMD.h"
#include "../util/strutil.h"
#include "../msg/messagebuilder.h"

#include "../error_messages.h"

#include <sstream>

using std::stringstream;

InterResult* ShellCMDInter::interprets( Block* parent, BlockIterator* it, string currentLine, int lineNumber, void* mgr ) {
    if ( currentLine.length() == 0 )
        return new InterResult( false );

    int numberOfLines = 0;

    string cmdstr;
    if ( currentLine[ 0 ] == '@' ) {
        cmdstr = currentLine.substr( 1, currentLine.length()-1 );
        cmdstr = strutil::removeStartWhiteSpaces( cmdstr );
        numberOfLines = 1;
    } else {
        string token = strutil::trim( currentLine );
        if ( token != "shellbegin" )
            return new InterResult( false );

        stringstream ss;

        bool shellendFound = false;

        numberOfLines = 1;

        while( !shellendFound && it->hasNextLine() ) {
            string line = it->nextLine();
            string line2 = strutil::removeStartWhiteSpaces( line );

            if ( line2.length() == 0 ) {
                numberOfLines++;
                continue;
            }

            if ( line2[ 0 ] == '#' ) {
                numberOfLines++;
                continue;
            }

            istringstream iss( line2 );
            string token;
            iss >> token;
            if ( token == "shellend" ) {
                if ( iss.peek() != EOF ) {
                    iss >> token;

                    size_t j = line.find_last_of( token );
                    
                    messagebuilder b( errors::END_OF_BLOCK_WITH_UNNECESSARY_TOKEN );
                    b << token;
                    return new InterResult( line, numberOfLines, j, b.str() );
                }

                shellendFound = true;
            } else {
                ss << line2 << "\n";
            }

            numberOfLines++;
        }

        if ( !shellendFound )
            return new InterResult( currentLine, numberOfLines, 0, errors::END_OF_SHELL_BLOCK_NOT_FOUND );

        cmdstr = ss.str();
        if ( cmdstr.length() > 0 )
            cmdstr = cmdstr.substr( 0, cmdstr.length()-1 );
    }

    InterResult* replaceResult = Inter::replacePropsAndVarsAndDollarSigns( cmdstr, lineNumber, parent );
    if ( !replaceResult->isInterpreted() )
        return replaceResult;

    delete replaceResult;

    ShellCMD* shellCMD = new ShellCMD( parent, cmdstr, lineNumber, currentLine );

    if ( parent != nullptr )
        parent->addStatement( shellCMD );

    return new InterResult( nullptr, numberOfLines, currentLine.length() );

}
