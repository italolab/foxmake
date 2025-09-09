#ifndef PROP_H
#define PROP_H

#include <string>

using std::string;

class Prop {

    private:
        string name;
        string value;
        string line;
        int numberOfLinesReaded;

    public:
        Prop( string name, string value, int numberOfLinesReaded, string line );

        string getName();
        string getValue();
        int getNumberOfLinesReaded();
        string getLine();

};

#endif
