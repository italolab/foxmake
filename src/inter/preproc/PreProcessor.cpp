
#include "PreProcessor.h"
#include "../../util/strutil.h"
#include "../../msg/messagebuilder.h"

#include "../../error_messages.h"

#include <sstream>

using std::stringstream;
using std::istringstream;

InterResult* PreProcessor::preProcess( BlockIterator* it, string& preProcessedText ) {
    bool isWin32 = false;

    #ifdef _WIN32
        isWin32 = true;
    #endif

    stringstream blockSS;
    int numberOfLinesReaded = 0;

    InterResult* endNotFoundIR = nullptr;

    bool isIgnore = false;
    bool endIFNotFound = false;
    while( it->hasNextLine() ) {
        string line = it->nextLine();

        istringstream iss( line );
        if ( iss.peek() == EOF ) {
            blockSS << line << "\n";
            numberOfLinesReaded++;
            continue;
        }

        string token;
        iss >> token;

        token = strutil::trim( token );

        if ( endIFNotFound && token == "ENDIF" ) {
            endIFNotFound = false;
            isIgnore = false;
            blockSS << "#" << line << "\n";
            numberOfLinesReaded++;
            continue;                            
        } 

        if ( token == "IFWIN32" || token == "IFNOWIN32" ) {
            if ( !isIgnore ) {
                endIFNotFound = true;

                if ( iss.peek() != EOF ) {
                    iss >> token;
                    if ( strutil::trim( token ) != "" ) {
                        messagebuilder b( errors::UNNECESSARY_TOKEN );
                        b << token;
                        return new InterResult( line, numberOfLinesReaded, 0, b.str() );
                    }
                }
            }
                 
            bool isIgnore2 = false;
            if ( isWin32 ) {
                isIgnore2 = token == "IFNOWIN32";
            } else {
                isIgnore2 = token == "IFWIN32";
            }

            if ( isIgnore2 ) {
                isIgnore = true;

                if ( endNotFoundIR != nullptr )
                    delete endNotFoundIR;
                endNotFoundIR = new InterResult( line, numberOfLinesReaded, 0, errors::END_OF_BLOCK_NOT_FOUND );  
            }

            numberOfLinesReaded++;
            blockSS << "#" << line << "\n";
            continue;
        }
        
        if ( isIgnore )
            blockSS << "#" << line << "\n";
        else blockSS << line << "\n";
          
        numberOfLinesReaded++;
    }

    if ( endIFNotFound && endNotFoundIR != nullptr )
        return endNotFoundIR;

    preProcessedText = blockSS.str();
        
    return new InterResult( true );
}