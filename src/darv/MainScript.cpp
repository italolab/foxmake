
#include "MainScript.h"

MainScript::MainScript() : Block( nullptr, 0, "" ) {}

MainScript::~MainScript() {
    for( const auto& pair : propertiesMap )
        delete pair.second;
    for( Task* task : tasksVect )
        delete task;
}

void MainScript::putProperty( Prop* prop ) {
    propertiesMap[ prop->getName() ] = prop;
}

void MainScript::putProperty( string name, string value ) {
    propertiesMap[ name ] = new Prop( name, value, 0, "" ); 
}

string MainScript::getPropertyValue( string name ) {
    Prop* prop = propertiesMap[ name ];
    if ( prop != nullptr )
        return prop->getValue();
    return "";
}

Prop* MainScript::getProperty( string name ) {
    if ( propertiesMap.find( name ) != propertiesMap.end() )
        return propertiesMap[ name ];
    return nullptr;
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

void MainScript::putPredefinedVar( string name, string value ) {
    predefinedVarsMap[ name ] = new Var( name, value, 0, "" );
}

Var* MainScript::getPredefinedVar( string name ) {
    if ( predefinedVarsMap.find( name ) != predefinedVarsMap.end() )
        return predefinedVarsMap[ name ];
    return nullptr;
}

vector<string> MainScript::predefinedVarNames() {
    vector<string> names;
    for( const auto& pair : predefinedVarsMap )
        names.push_back( pair.first );
    return names;
}

void MainScript::addTask( Task* task ) {
    tasksVect.push_back( task );
}

Task* MainScript::getTask( string taskName, TaskExecution taskExecution ) {
    for( Task* task : tasksVect )
        if ( task->getName() == taskName && task->getTaskExecution() == taskExecution )
            return task;
    return nullptr;
}


bool MainScript::existsTask( string taskName ) {
    for( Task* task : tasksVect )
        if ( task->getName() == taskName )
            return true;
    return false;
}

bool MainScript::existsTask( string taskName, TaskExecution taskExecution ) {
    for( Task* task : tasksVect )
        if ( task->getName() == taskName && task->getTaskExecution() == taskExecution )
            return true;
    return false;
}

vector<Task*>& MainScript::getTasks() {
    return tasksVect;
}

void MainScript::addProc( Proc* proc ) {
    procsVect.push_back( proc );
}
        
Proc* MainScript::getProc( string procName ) {
    for( Proc* proc : procsVect )
        if ( proc->getName() == procName )
            return proc;
    return nullptr;
}
        
bool MainScript::existsProc( string procName ) {
    for( Proc* proc : procsVect )
        if ( proc->getName() == procName )
            return true;
    return false;
}
    
vector<Proc*>& MainScript::getProcs() {
    return procsVect;
}

void MainScript::addDefaultTaskConfig( DefaultTaskConfig* config ) {
    defaultTaskConfigsVect.push_back( config );
}

DefaultTaskConfig* MainScript::getDefaultTaskConfig( string taskName ) {
    for( DefaultTaskConfig* config : defaultTaskConfigsVect )
        if ( config->getName() == taskName )
            return config;
    return nullptr;
}

vector<DefaultTaskConfig*>& MainScript::defaultTaskConfigs() {
    return defaultTaskConfigsVect;
}