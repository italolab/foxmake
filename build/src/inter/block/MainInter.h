#ifndef PROPERTIES_H
#define PROPERTIES_H

#include "BlockInter.h"
#include "MainInterDriver.h"
#include "../WithPropInter.h"
#include "../str/CMDInter.h"

#include <string>
#include <vector>
#include <map>

using namespace std;

class MainInter : public BlockInter, public WithPropInter {

    private:
        MainInterDriver* drv;
        map<string, string> propertiesMap;
        vector<CMDInter*> cmdIntersVect;

    public:
        MainInter( MainInterDriver* drv );

        InterResult* interpreta( BlockIterator* blockIt, int lineNumber );

        string getPropertyValue( string name );
        bool existsProperty( string name );
        int getPropertiesLength();
        vector<string> propertyNames();

        CMDInter* getCMDInter( string name );
        int getCMDIntersLength();
        CMDInter* getCMDInterByIndex( int i );
        vector<CMDInter*> cmdInters();

};

#endif
