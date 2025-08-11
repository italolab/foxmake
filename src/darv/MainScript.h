#ifndef MAIN_SCRIPT_H
#define MAIN_SCRIPT_H

#include "Block.h"
#include "CMD.h"
#include "Var.h"
#include "Task.h"

#include <string>

using std::string;

class MainScript : public Block {

    private:
        map<string, Prop*> propertiesMap;
        map<string, Task*> tasksMap;

    public:
        MainScript();

        void addProperty( Prop* prop );
        string getPropertyValue( string name );
        bool existsProperty( string name );
        int getPropertiesLength();
        vector<string> propertyNames();

        void addTask( Task* task );
        Task* getTask( string taskName );
        int getTasksLength();
        vector<string> taskNames();

};

#endif
