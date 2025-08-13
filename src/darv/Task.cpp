
#include "Task.h"

Task::Task( Statement* parent, int lineNumber, string line ) : Block( parent, lineNumber, line ) {}

string Task::getName() {
    return name;
}

void Task::setName( string name ) {
    this->name = name;
}
