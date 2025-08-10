#ifndef NO_H
#define NO_H

class Block;

class No {

    private:
        Block* parent;

    public:
        No( Block* parent );

        Block* getParent();
};

#endif
