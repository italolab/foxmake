
#include "Task.h"

Task::Task( Block* parent ) : Block( parent ) {}

string Task::getName() {
    return name;
}

void Task::setName( string name ) {
    this->name = name;
}
