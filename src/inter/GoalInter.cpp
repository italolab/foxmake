
#include "GoalInter.h"
#include "it/StringIterator.h"
#include "../darv/Goal.h"
#include "../util/strutil.h"

#include <sstream>

using std::stringstream;
using std::istringstream;

GoalInter::GoalInter( BlockInterDriver* drv ) : BlockInter( drv ) {}

InterResult* GoalInter::extInterpretsLine( Block* block, BlockIterator* it, string currentLine, int lineNumber, void* mgr ) {
    return new InterResult( false );
}

InterResult* GoalInter::interprets( Block* parent, BlockIterator* it, string currentLine, int lineNumber, void* mgr ) {
    istringstream iis( currentLine );

    if ( iis.peek() == EOF )
        return new InterResult( false );

    string goalName;
    iis >> goalName;

    if( iis.peek() == EOF )
        return new InterResult( false );

    string openBraces;
    iis >> openBraces;
    openBraces = strutil::trim( openBraces );

    if ( openBraces != "{" || iis.peek() != EOF )
        return new InterResult( false );

    goal = ((MainScript*)parent)->getGoal( goalName );
    if ( goal == nullptr ) {
        goal = new Goal( parent );
        goal->setName( goalName );

        ((MainScript*)parent)->addGoal( goal );
    }

    stringstream ss;
    int lineNumber2 = lineNumber + 1;

    int bracesCount = 1;
    while( it->hasNextLine() && bracesCount > 0 ) {
        string line = it->nextLine();
        int len = line.length();
        for( int i = 0; bracesCount > 0 && i < len; i++ ) {
            switch( line[ i ] ) {
                case '{':
                    bracesCount++;
                    break;
                case '}':
                    bracesCount--;
                    break;
            }

            if ( bracesCount > 0 )
                ss << line[ i ];
        }

        if ( bracesCount > 0 )
            ss << "\n";
        lineNumber2++;
    }

    string blockStr = ss.str();

    return BlockInter::interpretsBlock( parent, blockStr, lineNumber2, mgr );
}

string GoalInter::errorMSGForNotRecognizedStatement() {
    return "Linha nao reconhecida como comando ou variavel.";
}

BlockIterator* GoalInter::createBlockIterator( string text ) {
    return new StringIterator( text );
}

Block* GoalInter::getBlock() {
    return goal;
}
