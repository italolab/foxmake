#ifndef IF_H
#define IF_H

#include "Statement.h"
#include "IFCondition.h"

class IF : public Statement {

    private:
        IFCondition* condition; 
        Statement* thenStatement;
        Statement* elseStatement;

    public:
        IF( Statement* parent, int numberOfLinesReaded, string line );
        virtual ~IF();

        IFCondition* getCondition();
        Statement* getThenStatement();
        Statement* getElseStatement();

        void setCondition( IFCondition* condition );
        void setThenStatement( Statement* block );
        void setElseStatement( Statement* block );

};

#endif