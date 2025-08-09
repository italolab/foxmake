
#include "VarInter.h"
#include "../darv/Var.h"

InterResult* VarInter::interpreta( Block* block, string str, int lineNumber, InterManager* manager ) {
    string name = "a";
    string value = "b";
    int numberOfColumns = 0;
    Var* var = new Var( block, name, value );
    return new InterResult( var, 0, numberOfColumns );
}
