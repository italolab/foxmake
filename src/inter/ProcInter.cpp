
#include "ProcInter.h"
#include "InterManager.h"
#include "it/StringIterator.h"
#include "taskdef/TaskDefinitionResult.h"
#include "../darv/Task.h"
#include "../util/strutil.h"
#include "../msg/messagebuilder.h"

#include "../error_messages.h"

#include <sstream>

using std::stringstream;
using std::istringstream;

ProcInter::~ProcInter() {}

InterResult* ProcInter::interpretsLine( 
            Block* block, 
            BlockIterator* it, 
            string currentLine, 
            int& numberOfLinesReaded, 
            void* mgr ) {
                
    InterManager* manager = (InterManager*)mgr;

    return manager->interpretsVarAttr( block, currentLine, numberOfLinesReaded );
}

/*
O atributo endTokenNotFoundIResult é carregado dentro da função interprets. Logo, 
depende dela para não ser nulo.
*/
InterResult* ProcInter::interprets( 
            MainScript* parent, 
            BlockIterator* it, 
            string currentLine, 
            int& numberOfLinesReaded, 
            void* mgr ) {

    istringstream iss( currentLine );

    if ( iss.peek() == EOF )
        return new InterResult( false );

    string token;
    iss >> token;

    if ( token != "proc" )
        return new InterResult( false );

    if ( iss.peek() == EOF )
        return new InterResult( currentLine, numberOfLinesReaded, 0, errors::PROC_NAME_NOT_INFORMED );

    string procName;
    iss >> procName;

    if ( iss.peek() != EOF ) {
        iss >> token;
        if ( strutil::trim( token ) != "" ) {
            messagebuilder b ( errors::UNNECESSARY_TOKEN );
            b << token;
            return new InterResult( currentLine, numberOfLinesReaded, 0, b.str() );
        }
    }
        
    InterResult* endTokenNotFoundIResult = new InterResult( currentLine, numberOfLinesReaded, 0, errors::END_OF_PROC_BLOCK_NOT_FOUND );

    numberOfLinesReaded++;

    Proc* proc = new Proc( parent, procName, numberOfLinesReaded, currentLine );

    if ( parent != nullptr )
        parent->addProc( proc );
       
    string endToken = "endproc";
    
    InterResult* blockIResult = BlockInter::interpretsBlock( 
                    proc, 
                    it, 
                    numberOfLinesReaded, 
                    endToken, 
                    endTokenNotFoundIResult, 
                    mgr );

    if ( blockIResult->isErrorFound() )
        return blockIResult;
        
    return new InterResult( proc, numberOfLinesReaded, 0 );
}