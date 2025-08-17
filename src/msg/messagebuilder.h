#ifndef MESSAGEBUILDER_H
#define MESSAGEBUILDER_H

#include <string>
#include <vector>
#include <sstream>

using std::string;
using std::stringstream;
using std::vector;

class messagebuilder {

    private:
        string message;
        vector<string> params;

    public:
        messagebuilder();
        messagebuilder( string msg );
        virtual ~messagebuilder();

        messagebuilder& operator<<( string param );

        string str();

};

#endif
