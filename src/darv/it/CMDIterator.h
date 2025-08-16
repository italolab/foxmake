#ifndef CMD_ITERATOR_H
#define CMD_ITERATOR_H

#include "../Block.h"
#include "../CMD.h"
#include "../ShellCMD.h"

class CMDIterator {

    private:
        Block* block;

    public:
        CMDIterator( Block* block );

        CMD* nextCMD();
        ShellCMD* nextShellCMD();

};

#endif
