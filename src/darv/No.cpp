
#include "No.h"

No::No( Block* parent ) {
    this->parent = parent;
}

Block* No::getParent() {
    return parent;
}
