
#include "MainScriptInter.h"
#include "InterManager.h"
#include "it/FileIterator.h"
#include "../darv/MainScript.h"

#include <fstream>
#include <sstream>
#include <iostream>

MainScriptInter::MainScriptInter( MainScriptInterDriver* drv ) {
    this->drv = drv;
}

InterResult* MainScriptInter::interpreta( string file, int lineNumber, InterManager* manager ) {
    return interpreta( nullptr, file, lineNumber, manager );
}

InterResult* MainScriptInter::interpreta( Block* block, string file, int lineNumber, InterManager* manager ) {
    vector<string> validCMDs = drv->validMainCMDNames();

    MainScript* script = new MainScript();
    FileIterator* it = new FileIterator( file );

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

        if ( isCmd ) {
            InterResult* replaceResult = Inter::replaceProps( line, lineNumber, script );
            if ( !replaceResult->isOk() )
                return replaceResult;

            delete replaceResult;

            InterResult* result = manager->getCMDInter()->interpreta( script, line, currentLineNumber, manager );

            numberOfLines += result->getNumberOfLines();

            if ( result->isOk() ) {
                script->addCMD( (CMD*)result->getNo() );
            } else {
                return new InterResult( numberOfLines, result->getErrorMsg() );
            }
        } else {
            InterResult* result = manager->getPropInter()->interpreta( script, line, currentLineNumber, manager );
            if ( result->isOk() )
                script->addProperty( (Prop*)result->getNo() );
        }

        numberOfLines++;
    }

    return new InterResult( script, numberOfLines );
}
