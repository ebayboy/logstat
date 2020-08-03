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
    RBNode() {}
    RBNode(int key, std::string value, bool color) : key(key), value(value), color(color) {}
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

    void __Put(int key, std::string value);

private:
    RBNode *m_root;
    /* data */
    RBNode *__RotateLeft(RBNode *h);
    RBNode *__RotateRight(RBNode *h);
    void __FlipColors(RBNode *h);
    RBNode *__Put(RBNode *h, int key, std::string value);
    bool __IsRed(RBNode *x);
};

//判断节点x的颜色
bool RBTree::__IsRed(RBNode *x)
{
    if (x == nullptr)
        return false;
    return x->color == RED;
}

void RBTree::__Put(int key, std::string value)
{
    //查找key，找到则更新它的值，找不到就创建一个新的节点
    m_root = __Put(m_root, key, value);
    m_root->color = BLACK; //根节点永远是黑色的
}

RBNode *RBTree::__Put(RBNode *h, int key, std::string value)
{
    //插入节点
    if (h == nullptr) //标准的插入操作，和父节点用红链接相连
        return new RBNode(key, value, RED);
    if (key < h->key)
        h->left = __Put(h->left, key, value);
    else if (key > h->key)
        h->right = __Put(h->right, key, value); //第一次调整, 左旋转
    else
        h->value = value;

    //如果是左双红，则进行第二次调整节点（右旋转）
    //2. 调整： 左旋转、右旋转、改变颜色

    /* 右单红， 左旋转 */
    if (__IsRed(h->right) && !__IsRed(h->left))
        h = __RotateLeft(h);
    
    /* 左侧双红， 右旋转 */
    if (__IsRed(h->left) && __IsRed(h->left->left))
        h = __RotateRight(h);

    /* 左右双红， 改变颜色 */
    if (__IsRed(h->left) && __IsRed(h->right))
        __FlipColors(h);

    /* 右双红， 不存在这种情况，因为初始时候红链不可能在右边， 违反2-3树和红黑树定义 */

    return h;
}

void RBTree::__FlipColors(RBNode *h)
{
    h->color = RED;
    h->left->color = BLACK;
    h->right->color = BLACK;
}

RBNode *RBTree::__RotateLeft(RBNode *h)
{
    RBNode *r = h->right;
    h->right = r->left;
    r->left = h;
    h->color = BLACK;
    r->left->color = RED;
    return r;
}

RBNode *RBTree::__RotateRight(RBNode *h)
{
    RBNode *l = h->left;
    h->left = l->right;
    l->right = h;
    h->color = BLACK;
    l->left->color = RED;
    return l;
}

#endif // !__RBTREE_H__
