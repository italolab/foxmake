
#include "PreProcessor.h"
#include "../../util/strutil.h"
#include "../../msg/messagebuilder.h"

#include "../../error_messages.h"

#include <sstream>

using std::stringstream;
using std::istringstream;

#include <iostream>
using namespace std;

InterResult* PreProcessor::preProcess( BlockIterator* it, string& preProcessedText ) {
    bool isWin32 = false;

    #ifdef _WIN32
        isWin32 = true;
    #endif

    bool isIgnore = false;

    stringstream blockSS;

    int numberOfLinesReaded = 0;

    InterResult* endNotFoundIR = nullptr;

    int count = 0;
    while( count > 0 && it->hasNextLine() ) {
        string line = it->nextLine();

        istringstream iss( line );
        if ( iss.peek() == EOF ) {
            blockSS << line;
            numberOfLinesReaded++;
            continue;
        }

        string token;
        iss >> token;

        token = strutil::trim( token );

        if ( isIgnore ) {
            if ( token == "IFWIN32" || token == "IFNOWIN32" ) {
                count++;
            } else if ( token == "ENDIF" ) {
                count--;
            }

            if ( count == 0 ) {
                isIgnore = false;
                numberOfLinesReaded++;
                continue;
            }
        } else {
            if ( token == "IFWIN32" || token == "IFNOWIN32" ) {
                if ( iss.peek() != EOF ) {
                    iss >> token;
                    if ( strutil::trim( token ) != "" ) {
                        messagebuilder b( errors::UNNECESSARY_TOKEN );
                        b << token;
                        return new InterResult( line, numberOfLinesReaded, 0, b.str() );
                    }
                }
            }

            if ( isWin32 ) {
                isIgnore = token == "IFNOWIN32";
                count = 1;
            } else {
                isIgnore = token == "IFWIN32";
                count = 1;
            }

            if ( isIgnore )
                endNotFoundIR = new InterResult( line, numberOfLinesReaded, 0, errors::END_OF_BLOCK_NOT_FOUND );  
        }
        
        if ( !isIgnore )
            if ( token != "IFWIN32" && token != "IFNOWIN32" )
                blockSS << line << "\n";

        numberOfLinesReaded++;
    }

    if ( count > 0 && endNotFoundIR != nullptr )
        return endNotFoundIR;

    preProcessedText = blockSS.str();

    cout << preProcessedText << endl;
        
    return new InterResult( true );
}