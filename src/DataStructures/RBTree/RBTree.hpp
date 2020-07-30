#ifndef __RBTREE_H__
#define __RBTREE_H__

struct RBNode
{
    RBNode *left;
    RBNode *right;
    RBNode *parent;
    int key;

    RBNode() : left(nullptr), right(nullptr), parent(nullptr), key(0) {}
};

class RBTree
{

public:
    RBTree() {}
    ~RBTree() {}

private:
    /* data */
};

#endif // !__RBTREE_H__
