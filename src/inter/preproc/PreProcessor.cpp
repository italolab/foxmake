
#include "PreProcessor.h"
#include "../../util/strutil.h"
#include "../../msg/messagebuilder.h"

#include "../../error_messages.h"

#include <sstream>

using std::stringstream;
using std::istringstream;

PreProcessor::PreProcessor() {
    this->ifConditionInter = new IFConditionInter();
}

PreProcessor::~PreProcessor() {
    delete ifConditionInter;
}

InterResult* PreProcessor::preProcess( Block* block, BlockIterator* it, string& preProcessedText, void* mgr ) {
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

        if ( token == "IF" ) {
            if ( !isIgnore )
                endIFNotFound = true;

            if ( line.length() < 3 )
                return new InterResult( line, numberOfLinesReaded, 0, errors::IF_CONDITION_EXPECTED );

            string line2 = strutil::removeStartWhiteSpaces( line );
            string condition = line2.substr( 3, line2.length()-3 );
            condition = strutil::removeStartWhiteSpaces( condition );
            condition = strutil::removeEndWhiteSpaces( condition );
                 
            string value1;
            string value2;
            string compOperator;
            InterResult* result = ifConditionInter->interprets( 
                    block, condition, value1, value2, compOperator, line, numberOfLinesReaded, mgr );
                    
            if ( result->isErrorFound() )
                return result;

            bool isIgnore2 = false;
            if ( compOperator == "==" ) {
                isIgnore2 = ( value1 != value2 );
            } else {
                isIgnore2 = ( value1 == value2 );
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