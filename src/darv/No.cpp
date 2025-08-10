
#include "No.h"
#include <typeinfo>

No::No( Block* parent ) {
    this->parent = parent;
}

Block* No::getParent() {
    return parent;
}
