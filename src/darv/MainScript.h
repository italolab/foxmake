#ifndef MAIN_SCRIPT_H
#define MAIN_SCRIPT_H

#include "Block.h"
#include "CMD.h"
#include "Var.h"
#include "Task.h"
#include "Proc.h"
#include "Var.h"
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
        map<string, Var*> predefinedVarsMap;
        vector<Task*> tasksVect;
        vector<Proc*> procsVect;
        vector<DefaultTaskConfig*> defaultTaskConfigsVect;

    public:
        MainScript();
        virtual ~MainScript();

        void putProperty( Prop* prop );
        void putProperty( string name, string value );
        Prop* getProperty( string name );
        string getPropertyValue( string name );
        bool existsProperty( string name );
        int getPropertiesLength();
        vector<string> propertyNames();

        void putPredefinedVar( string name, string value );
        Var* getPredefinedVar( string name );
        vector<string> predefinedVarNames();

        void addTask( Task* task );
        Task* getTask( string taskName, TaskExecution taskExecution );
        bool existsTask( string taskName );
        bool existsTask( string taskName, TaskExecution taskExecution );
        vector<Task*>& getTasks();

        void addProc( Proc* proc );
        Proc* getProc( string procName );
        bool existsProc( string procName );
        vector<Proc*>& getProcs();

        void addDefaultTaskConfig( DefaultTaskConfig* config );
        DefaultTaskConfig* getDefaultTaskConfig( string taskName );
        vector<DefaultTaskConfig*>& defaultTaskConfigs();

};

#endif
