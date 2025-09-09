#ifndef VAR_H
#define VAR_H

#include <string>

using std::string;

class Var {

    private:
        string name;
        string value;
        string line;
        int numberOfLinesReaded;

    public:
        Var( string name, string value, int numberOfLinesReaded, string line );

        string getName();
        string getValue();
        int getNumberOfLinesReaded();
        string getLine();

        void setValue( string value );

};

#endif
