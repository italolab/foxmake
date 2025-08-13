
#include "Task.h"

Task::Task( Statement* parent, int lineNumber ) : Block( parent, lineNumber ) {}

string Task::getName() {
    return name;
}

void Task::setName( string name ) {
    this->name = name;
}
