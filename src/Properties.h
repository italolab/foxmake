#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <vector>
#include <string>

using namespace std;

typedef struct TProperty {
    string name;
    string value;
} Property;

class Properties {

    private:
        vector<Property> properties;

    public:
        void load( string file );

        string getProperty( string name );

        void add( string name, string value );
        int length();
        Property get( int i );
        vector<Property> getAll();

};

#endif
