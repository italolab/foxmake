#ifndef PROPERTIES_H
#define PROPERTIES_H

#include "Inter.h"
#include "../cmd/CMD.h"

#include <vector>
#include <string>

using namespace std;

typedef struct TProperty {
    string name;
    string value;
} Property;

class MainInter : public Inter {

    private:
        vector<Property> properties;
        vector<CMD*> cmds;

    public:
        void interpreta( string file, vector<string> validStrCMDs );

        string getPropertyValue( string name );
        CMD* getCMD( string name );

        bool existsProperty( string name );

        int getPropertiesLength();
        Property getPropertyByIndex( int i );
        vector<Property> getProperties();

        int getCMDLength();
        CMD* getCMDByIndex( int i );
        vector<CMD*> getCMDs();
};

#endif
