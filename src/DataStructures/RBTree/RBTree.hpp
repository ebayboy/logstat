#ifndef __RBTREE_H__
#define __RBTREE_H__

#include <string>
#include <cstdio>

static bool RED = true;
static bool BLACK = false;

struct RBNode
{
    RBNode *left;
    RBNode *right;
    //RBNode *parent;  //增加了处理树的复杂度
    int key;
    std::string value;
    bool color;
    RBNode() : left(nullptr), right(nullptr), parent(nullptr), key(0) {}
    RBNode(int key, std::string value, bool color): key(key), value(value), color(color) {}
    //判断红黑树节点的颜色

#if 0 
    bool __IsRed(RBNode x)
    {
        if (x == nullptr)
            return BLACK;
        return x.color == RED;
    }
#endif
};

class RBTree
{

public:
    RBTree() {}
    ~RBTree() {}


private:
    /* data */
    void __RotateLeft(RBNode *proot);
    void __RotateRight(RBNode *proot);
};

void RBTree::__RotateLeft (RBNode *proot)
{
    RBNode *r = proot->right;
    proot->right = r->left;
    r->left = proot;
    proot->color = BLACK;
    r->left->color = RED;
}

void RBTree::__RotateRight (RBNode *proot)
{
    RBNode *l = proot->left;
    proot->left = l->right;
    l->right = proot;
    proot->color = BLACK;
    l->left->color = RED;
}

#endif // !__RBTREE_H__
