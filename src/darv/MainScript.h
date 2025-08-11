#ifndef MAIN_SCRIPT_H
#define MAIN_SCRIPT_H

#include "Block.h"
#include "CMD.h"
#include "Var.h"
#include "Goal.h"

#include <string>

using std::string;

class MainScript : public Block {

    private:
        map<string, Prop*> propertiesMap;
        map<string, Goal*> goalsMap;

    public:
        MainScript();

        void addProperty( Prop* prop );
        string getPropertyValue( string name );
        bool existsProperty( string name );
        int getPropertiesLength();
        vector<string> propertyNames();

        void addGoal( Goal* goal );
        Goal* getGoal( string goalName );
        int getGoalsLength();
        vector<string> goalsNames();

};

#endif
