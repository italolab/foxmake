#ifndef PROPERTIES_H
#define PROPERTIES_H

#include "BlockInter.h"
#include "MainInterDriver.h"
#include "../WithPropInter.h"
#include "../line/CMDInter.h"

#include <string>
#include <vector>
#include <map>

using namespace std;

class MainInter : public BlockInter, public WithPropInter {

    private:
        MainInterDriver* drv;
        map<string, string> propertiesMap;
        vector<CMDInter*> cmds;

    public:
        MainInter( MainInterDriver* drv );

        void interpreta( BlockIterator* blockIt );

        string getPropertyValue( string name );
        CMDInter* getCMDInter( string name );

        bool existsProperty( string name );

        int getPropertiesLength();
        vector<string> propertyNames();

        int getCMDIntersLength();
        CMDInter* getCMDInterByIndex( int i );
        vector<CMDInter*> getCMDInters();

};

#endif
