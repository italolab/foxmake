#ifndef MAIN_SCRIPT_H
#define MAIN_SCRIPT_H

#include "Block.h"
#include "CMD.h"
#include "Var.h"
#include "Task.h"
#include "DefaultTaskConfig.h"
#include "Prop.h"

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

class MainScript : public Block {

    private:
        map<string, Prop*> propertiesMap;
        vector<Task*> tasksVect;
        vector<DefaultTaskConfig*> defaultTaskConfigsVect;

    public:
        MainScript();
        virtual ~MainScript();

        void putProperty( Prop* prop );
        Prop* getProperty( string name );
        string getPropertyValue( string name );
        bool existsProperty( string name );
        int getPropertiesLength();
        vector<string> propertyNames();

        void addTask( Task* task );
        Task* getTask( string taskName, bool beforeFlag );
        vector<Task*>& tasks();

        void addDefaultTaskConfig( DefaultTaskConfig* config );
        DefaultTaskConfig* getDefaultTaskConfig( string taskName );
        vector<DefaultTaskConfig*>& defaultTaskConfigs();

};

#endif
