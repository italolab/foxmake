
#include "BlockInter.h"
#include "InterManager.h"
#include "../darv/MainScript.h"

#include <vector>

using std::vector;

BlockInter::BlockInter( BlockInterDriver* drv ) {
    this->drv = drv;
}

InterResult* BlockInter::interprets2( Block* parent, string str, int lineNumber, AbstractInterManager* mgr ) {
    InterManager* manager = (InterManager*)mgr;

    vector<string> validCMDs = drv->validMainCMDNames();

    Block* block = createBlock( parent );
    BlockIterator* it = createBlockIterator( str );

    int numberOfLines = 0;
    while( it->hasNextLine() ) {
        string line = it->nextLine();

        if ( line.length() == 0 ) {
            numberOfLines++;
            continue;
        }
        if ( line[ 0 ] == ' ' || line[ 0 ] == '\n' || line[ 0 ] == '\t' || line[ 0 ] == '\r' || line[ 0 ] == '#' ) {
            numberOfLines++;
            continue;
        }

        bool isCmd = false;

        size_t i = line.find( ' ' );
        if ( i != string::npos ) {
            string cmd = line.substr( 0, i );
            int len = validCMDs.size();
            for( int k = 0; !isCmd && k < len; k++ )
                if ( cmd == validCMDs[ k ] )
                    isCmd = true;
        }

        int currentLineNumber = lineNumber + numberOfLines;

        InterResult* result = new InterResult( false );
        if ( isCmd ) {
            MainScript* root = (MainScript*)block->getRoot();
            InterResult* replaceResult = Inter::replaceProps( line, currentLineNumber, root );
            if ( !replaceResult->isOk() )
                return replaceResult;

            result = manager->getCMDInter()->interpreta( block, line, currentLineNumber, manager );
        }

        if ( !result->isOk() )
            result = manager->getVarInter()->interpreta( block, line, currentLineNumber, manager );
        if ( !result->isOk() )
            result = interpretsLine( block, line, currentLineNumber, mgr );

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
