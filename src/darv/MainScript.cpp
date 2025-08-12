
#include "MainScript.h"

MainScript::MainScript() : Block( nullptr ) {}

void MainScript::putProperty( Prop* prop ) {
    propertiesMap[ prop->getName() ] = prop;
}

int MainScript::getPropertiesLength() {
    return propertiesMap.size();
}

string MainScript::getPropertyValue( string name ) {
    Prop* prop = propertiesMap[ name ];
    if ( prop != nullptr )
        return prop->getValue();
    return "";
}

bool MainScript::existsProperty( string name ) {
    return propertiesMap.find( name ) != propertiesMap.end();
}

vector<string> MainScript::propertyNames() {
    vector<string> names;
    for( const auto& pair : propertiesMap )
        names.push_back( pair.first );
    return names;
}

void MainScript::putTask( Task* task ) {
    tasksMap[ task->getName() ] = task;
}

Task* MainScript::getTask( string taskName ) {
    return tasksMap[ taskName ];
}

int MainScript::getTasksLength() {
    return tasksMap.size();
}

vector<string> MainScript::taskNames() {
    vector<string> names;
    for( const auto& pair : tasksMap )
        names.push_back( pair.first );
    return names;
}
