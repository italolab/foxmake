#ifndef IF_H
#define IF_H

#include "Statement.h"

class IF : public Statement {

    private:
        bool conditionValue; 
        Statement* thenStatement;
        Statement* elseStatement;

    public:
        IF( Statement* parent, int numberOfLinesReaded, string line );
        virtual ~IF();

        bool getConditionValue();
        Statement* getThenStatement();
        Statement* getElseStatement();

        void setConditionValue( bool condition );
        void setThenStatement( Statement* block );
        void setElseStatement( Statement* block );

};

#endif