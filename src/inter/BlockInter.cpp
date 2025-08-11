
#include "BlockInter.h"
#include "InterManager.h"
#include "../util/strutil.h"

#include <vector>

using std::vector;

BlockInter::BlockInter( BlockInterDriver* drv ) {
    this->drv = drv;
}

InterResult* BlockInter::interpretsBlock( Block* parent, string blockStr, int lineNumber, void* mgr ) {
    InterManager* manager = (InterManager*)mgr;

    vector<string> validCMDs = drv->validCMDNames();

    Block* block = getBlock();
    BlockIterator* it = createBlockIterator( blockStr );

    int numberOfLines = 0;
    while( it->hasNextLine() ) {
        string line = it->nextLine();
        line = strutil::removeStartWhiteSpaces( line );

        if ( line.length() == 0 ) {
            numberOfLines++;
            continue;
        }
        if ( strutil::isWhiteSpace( line[ 0 ] ) || line[ 0 ] == '#' ) {
            numberOfLines++;
            continue;
        }

        bool isCmd = manager->isValidCMD( line, validCMDs );

        int currentLineNumber = lineNumber + numberOfLines;

        InterResult* result = new InterResult( false );
        if ( isCmd ) {
            InterResult* replaceResult = Inter::replacePropsAndVars( line, currentLineNumber, block );
            if ( !replaceResult->isOk() )
                return new InterResult( lineNumber + numberOfLines, replaceResult->getErrorMsg() );

            result = manager->interpretsCMD( block, line, currentLineNumber );
        }

        if ( !result->isOk() )
            result = manager->interpretsVar( block, line, currentLineNumber );
        if ( !result->isOk() )
            result = extInterpretsLine( block, it, line, currentLineNumber, mgr );

        if ( result->isOk() ) {
            numberOfLines += result->getNumberOfLines();
        } else {
            string error;
            if ( result->getErrorMsg() != "" )
                error = result->getErrorMsg();
            else error = "Linha nao reconhecida como comando, propriedade ou variavel.";

            return new InterResult( lineNumber + numberOfLines, error );
        }

        numberOfLines++;
    }

    return new InterResult( block, numberOfLines );
}
