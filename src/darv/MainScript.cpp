
#include "MainScript.h"

MainScript::MainScript() : Block( nullptr ) {}

void MainScript::addProperty( Prop* prop ) {
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

void MainScript::addGoal( Goal* goal ) {
    goalsMap[ goal->getName() ] = goal;
}

Goal* MainScript::getGoal( string goalName ) {
    return goalsMap[ goalName ];
}

int MainScript::getGoalsLength() {
    return goalsMap.size();
}

vector<string> MainScript::goalsNames() {
    vector<string> names;
    for( const auto& pair : goalsMap )
        names.push_back( pair.first );
    return names;
}
