
#include "MainScript.h"

MainScript::MainScript() : Block( nullptr, 0, "" ) {}

MainScript::~MainScript() {
    for( const auto& pair : propertiesMap )
        delete pair.second;
    for( const auto& pair : tasksMap )
        delete pair.second;
}

void MainScript::putProperty( Prop* prop ) {
    propertiesMap[ prop->getName() ] = prop;
}

string MainScript::getPropertyValue( string name ) {
    Prop* prop = propertiesMap[ name ];
    if ( prop != nullptr )
        return prop->getValue();
    return "";
}

Prop* MainScript::getProperty( string name ) {
    return propertiesMap[ name ];
}

bool MainScript::existsProperty( string name ) {
    return propertiesMap.find( name ) != propertiesMap.end();
}

int MainScript::getPropertiesLength() {
    return propertiesMap.size();
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
    if ( tasksMap.find( taskName ) != tasksMap.end() )
        return tasksMap[ taskName ];
    return nullptr;
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
