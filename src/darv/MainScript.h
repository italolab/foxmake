#ifndef MAIN_SCRIPT_H
#define MAIN_SCRIPT_H

#include "Block.h"
#include "CMD.h"
#include "Var.h"
#include "Task.h"
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
        map<string, Task*> tasksMap;

    public:
        MainScript();

        void putProperty( Prop* prop );
        Prop* getProperty( string name );
        string getPropertyValue( string name );
        bool existsProperty( string name );
        int getPropertiesLength();
        vector<string> propertyNames();

        void putTask( Task* task );
        Task* getTask( string taskName );
        int getTasksLength();
        vector<string> taskNames();

};

#endif
