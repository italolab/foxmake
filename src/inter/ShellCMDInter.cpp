
#include "ShellCMDInter.h"
#include "../darv/ShellCMD.h"
#include "../util/strutil.h"
#include "../msg/messagebuilder.h"

#include "../error_messages.h"

#include <sstream>

using std::stringstream;
using std::istringstream;

InterResult* ShellCMDInter::interprets( 
            Block* parent, 
            BlockIterator* it, 
            string currentLine, 
            int& numberOfLinesReaded, 
            void* mgr ) {

    if ( currentLine.length() == 0 )
        return new InterResult( false );

    string cmdstr;
    if ( currentLine[ 0 ] == '@' ) {
        cmdstr = currentLine.substr( 1, currentLine.length()-1 );
        cmdstr = strutil::removeStartWhiteSpaces( cmdstr );
        numberOfLinesReaded++;
    } else {
        string token = strutil::trim( currentLine );
        if ( token != "shellbegin" )
            return new InterResult( false );

        stringstream ss;

        bool shellendFound = false;

        numberOfLinesReaded++;

        while( !shellendFound && it->hasNextLine() ) {
            string line = it->nextLine();
            string line2 = strutil::removeStartWhiteSpaces( line );

            if ( line2.length() == 0 ) {
                numberOfLinesReaded++;
                continue;
            }

            if ( line2[ 0 ] == '#' ) {
                numberOfLinesReaded++;
                continue;
            }

            istringstream iss( line2 );
            string token;
            iss >> token;
            if ( token == "endshell" ) {
                if ( iss.peek() != EOF ) {
                    iss >> token;

                    size_t j = line.find_last_of( token );
                    
                    messagebuilder b( errors::UNNECESSARY_TOKEN );
                    b << token;
                    return new InterResult( line, numberOfLinesReaded, j, b.str() );
                }

                shellendFound = true;
            } else if ( token == "endtask" ) {
                return new InterResult( currentLine, numberOfLinesReaded, 0, errors::END_OF_SHELL_BLOCK_NOT_FOUND );
            } else {
                ss << line2 << "\n";
            }

            numberOfLinesReaded++;
        }

        if ( !shellendFound )
            return new InterResult( currentLine, numberOfLinesReaded, 0, errors::END_OF_SHELL_BLOCK_NOT_FOUND );

        cmdstr = ss.str();
        if ( cmdstr.length() > 0 )
            cmdstr = cmdstr.substr( 0, cmdstr.length()-1 );
    }

    InterResult* replaceResult = Inter::replacePropsAndVarsAndDollarSigns( currentLine, cmdstr, numberOfLinesReaded, parent );
    if ( !replaceResult->isInterpreted() )
        return replaceResult;

    delete replaceResult;

    ShellCMD* shellCMD = new ShellCMD( parent, cmdstr, numberOfLinesReaded, currentLine );

    if ( parent != nullptr )
        parent->addStatement( shellCMD );

    return new InterResult( nullptr, numberOfLinesReaded, currentLine.length() );

}
