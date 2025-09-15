
#include "CMDExec.h"
#include "../ExecManager.h"
#include "../stexcept.h"
#include "../../msg/messagebuilder.h"

#include "../../error_messages.h"

#include <stdexcept>

using std::runtime_error;

#include <iostream>
using namespace std;

CMDExec::CMDExec() {
    cpExec = new CPExec();
    rmExec = new RMExec();
    cdExec = new CDExec();
    mkdirExec = new MKDirExec();
    echoExec = new EchoExec();
}

CMDExec::~CMDExec() {
    delete cdExec;
    delete cpExec;
    delete rmExec;
    delete echoExec;
    delete mkdirExec;
}

/*
Aqui é criado uma cópia do CMD para o caso do CMD ser executado várias vezes, 
não haver problema com a substituição de valores de variáveis e propriedades.

Esse método é executado a cada execução do comando e não seria bom que o replace 
de variáveis e propriedades alterasse o CMD original.
*/

void CMDExec::exec( CMD* cmd, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    InterManager* interManager = manager->getInterManager();

    ExecCMD* execCMD = new ExecCMD( cmd );

    int numberOfLinesReaded = cmd->getNumberOfLinesReaded();
    string line = cmd->getLine();
    Block* parent = (Block*)cmd->getParent();

    vector<string>& args = execCMD->getArgs();
    int len = args.size();
    for( int i = 0; i < len; i++ ) {
        InterResult* replaceResult = interManager->replacePropsAndVarsAndDollarSigns( 
                args[ i ], numberOfLinesReaded, line, parent );
        if ( !replaceResult->isInterpreted() )
            throw st_error( replaceResult );
        delete replaceResult;        
    } 

    string cmdstr = execCMD->getCMDStr();

    InterResult* replaceResult = interManager->replacePropsAndVarsAndDollarSigns( 
            cmdstr, numberOfLinesReaded, line, parent );
    if ( !replaceResult->isInterpreted() )
        throw st_error( replaceResult );
    delete replaceResult;
    
    execCMD->setCMDStr( cmdstr );

    string cmdName = execCMD->getName();
    if ( cmdName == "cd" ) {
        cdExec->exec( execCMD, mgr );
    } else if ( cmdName == "cp" ) {
        cpExec->exec( execCMD, mgr );
    } else if ( cmdName == "rm" ) {
        rmExec->exec( execCMD, mgr );
    } else if ( cmdName == "echo" ) {
        echoExec->exec( execCMD, mgr );
    } else if ( cmdName == "mkdir" ) {
        mkdirExec->exec( execCMD, mgr );
    } else {
        messagebuilder b( errors::runtime::CMD_EXECUTOR_NOT_FOUND );
        b << execCMD->getName();
        throw runtime_error( b.str() );
    }

    delete execCMD;
}