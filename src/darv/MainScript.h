#ifndef MAIN_SCRIPT_H
#define MAIN_SCRIPT_H

#include "Block.h"
#include "CMD.h"
#include "Var.h"

#include <string>

using std::string;

class MainScript : public Block {

    private:
        map<string, Prop*> propertiesMap;

    public:
        MainScript();

        void addProperty( Prop* prop );
        string getPropertyValue( string name );
        bool existsProperty( string name );
        int getPropertiesLength();
        vector<string> propertyNames();

};

#endif
