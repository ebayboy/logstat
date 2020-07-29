#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#include <iostream>
#include <cstdlib>

// add shard_ptr
// 函数实现通过指针引用类型实现  *&

struct BinaryNode
{
    int key;
    BinaryNode *left;
    BinaryNode *right;
    BinaryNode *parent;

    //struct constructor
    BinaryNode() : key(0), left(nullptr), right(nullptr){};
};

class BinaryTree
{
public:
    BinaryTree();
    ~BinaryTree();

    void PostOrder();
    void InOrder();
    void PreOrder();

    void InsertNode(int key);
    BinaryNode *FindNode(int key);

    int Max(); //最大值
    int Min(); //最小值

    int PreNode(int key);  //前驱结点
    int PostNode(int key); //后继节点

    int Floor(int key);    //向下取整是指小于等于key的最小值
    int Ceilling(int key); //向上取整是指大于key的最小键

    void RemoveAll(); //删除树
    void Remove(int key);

private:
    void __Remove(BinaryNode *proot, int key);
    BinaryNode *__RemoveAll(BinaryNode *proot);
    int __Floor(BinaryNode *proot, int key);
    int __Ceilling(BinaryNode *proot, int key);
    void __PostOrder(BinaryNode *proot);
    void __InOrder(BinaryNode *proot);
    void __PreOrder(BinaryNode *proot);
    BinaryNode *__InsertNode(BinaryNode *proot, int key);
    BinaryNode *__FindNode(BinaryNode *proot, int key);
    int __Max(BinaryNode *proot);
    int __Min(BinaryNode *proot);
    int __PreNode(BinaryNode *proot, int key);
    int __PostNode(BinaryNode *proot, int key);

    BinaryNode *m_root;
    size_t m_size;
};

void BinaryTree::Remove(int key)
{
    return __Remove(m_root, key);
}

void BinaryTree::__Remove(BinaryNode *proot, int key)
{
    BinaryNode *p = proot;
    if (proot == nullptr)
        return;

    //find node
    while (p && p->key != key)
    {
        if (key < proot->key)
            p = p->left;
        else
            p = p->right;
    }

    if (p == nullptr)
        return;

    //don't have child
    if (p->left == nullptr && p->right == nullptr)
        delete p;

    //have one child, set child->parent to it's parent
    if (p->left == nullptr || p->right == nullptr)
    {
        if (p->left)
        {
            if (p->parent->left == p)
                p->parent->left == p->left;
            else
                p->parent->right == p->left;
        }
        else
        {
            if (p->parent->left == p)
                p->parent->left == p->right;
            else
                p->parent->right == p->right;
        }
    }

    //p have tow child
}

void BinaryTree::RemoveAll()
{
    m_root = __RemoveAll(m_root);
}

BinaryNode *BinaryTree::__RemoveAll(BinaryNode *proot)
{
    if (proot == nullptr)
        return proot;

    if (proot->left)
    {
        proot->left = __RemoveAll(proot->left);
    }
    if (proot->right)
    {
        proot->right = __RemoveAll(proot->right);
    }

    proot->left = nullptr;
    proot->right = nullptr;
    proot->parent = nullptr;
    m_size -= 1;

    delete proot;
    proot = nullptr;

    return proot;
}

//向上取整是指>该键的最小键； key > proot->key
int BinaryTree::Ceilling(int key)
{
    return __Ceilling(m_root, key);
}

int BinaryTree::__Ceilling(BinaryNode *proot, int key)
{
    if (proot == nullptr)
        return -1;

    if (proot->key <= key)
    {
        return __Ceilling(proot->right, key);
    }
    else
    {
        //proot->key > key: 有可能是Ceilling, 但是还要看左子树中值是否有>key, 如果有则更接近key
        if (proot->left == nullptr)
        {
            return proot->key;
        }
        else
        {
            int tmp = __Ceilling(proot->left, key);
            if (tmp == -1)
                return proot->key;

            return tmp;
        }
    }

    return -1;
}

//向下取整是指小于等于该键的最小值。
int BinaryTree::Floor(int key)
{
    return __Floor(m_root, key);
}

int BinaryTree::__Floor(BinaryNode *proot, int key)
{
    if (proot == nullptr)
        return -1;

    if (proot->key > key)
    {
        return __Floor(proot->left, key);
    }
    else
    {
        //proot->key : 有可能是floot, 但是还要看右子树中值是否有<=key, 如果有则更接近key
        if (proot->right == nullptr)
        {
            return proot->key;
        }
        else
        {
            int tmp = __Floor(proot->right, key);
            if (tmp == -1)
                return proot->key;

            return tmp;
        }
    }

    return -1;
}

int BinaryTree::PostNode(int key)
{
    if (m_root == nullptr)
        return -1;
    return __PostNode(m_root, key);
}

int BinaryTree::__PostNode(BinaryNode *proot, int key)
{
    if (proot == nullptr)
        return -1;

    BinaryNode *p = proot;

    //1. find key by loop
    while (p)
    {
        if (key < p->key)
            p = p->left;
        else if (key > p->key)
            p = p->right;
        else
            break; //find node
    }

    if (p == nullptr)
        return -1;
    // not found key

    //1. have right child tree
    if (p->right)
        return __Min(p->right);

    //若该节点node没有右子树，则沿着parent节点一次往上找，
    //直至parent的左节点==node节点，
    //那么parent就是node的后继节点向上
    for (p; p && p->parent; p = p->parent)
    {
        if (p->parent->left && p->parent->left == p)
            return p->parent->key;
    }

    return -1;
}

int BinaryTree::PreNode(int key)
{
    if (m_root == nullptr)
        return -1;
    return __PreNode(m_root, key);
}

int BinaryTree::__PreNode(BinaryNode *proot, int key)
{
    if (proot == nullptr)
        return -1;

    BinaryNode *p = proot;

    //1. find key by loop
    while (p)
    {
        if (key < p->key)
            p = p->left;
        else if (key > p->key)
            p = p->right;
        else
            break; //find node
    }

    if (p == nullptr)
        return -1;
    // not found key

    //2.1 have left child tree
    if (p->left)
        return __Max(p->left);

    if (p->parent && p->parent->right == p)
    {
        //2.2.1 is pp->right ?
        return p->parent->key;
    }
    else if (p->parent && p->parent->left == p)
    {
        //2.2.2 is pp->left ?
        if (p->parent->parent)
        {
            if (p->parent->parent->right == p->parent)
                return p->parent->parent->key;
        }
    }

    return -1;
}

int BinaryTree::Max()
{
    return __Max(m_root);
}

int BinaryTree::__Max(BinaryNode *proot)
{
    if (proot == nullptr)
        return -1;
    else if (proot->right)
        return __Max(proot->right);
    else
        return proot->key;
}

int BinaryTree::Min()
{
    return __Min(m_root);
}

int BinaryTree::__Min(BinaryNode *proot)
{
    if (proot == nullptr)
        return -1;
    else if (proot->left)
        return __Min(proot->left);
    else
        return proot->key;
}

BinaryTree::BinaryTree() : m_root(nullptr), m_size(0)
{
}

BinaryTree::~BinaryTree()
{
}

void BinaryTree::InsertNode(int key)
{
    m_root = __InsertNode(m_root, key);
}

BinaryNode *BinaryTree::__InsertNode(BinaryNode *proot, int key)
{
    //find null node
    if (proot == nullptr)
    {
        //new 不初始化， new()进行初始化
        BinaryNode *node = new BinaryNode();
        if (node != nullptr)
        {
            node->key = key;
            proot = node;
            m_size += 1;
        }

        return proot;
    }

    if (key < proot->key)
    {
        proot->left = __InsertNode(proot->left, key);
        proot->left->parent = proot;
    }
    else if (key > proot->key)
    {
        proot->right = __InsertNode(proot->right, key);
        proot->right->parent = proot;
    }

    //相等不插入
    return proot;
}

void BinaryTree::__PostOrder(BinaryNode *proot)
{
    std::cout << "m_size: " << m_size << std::endl;
    if (proot == nullptr)
        return;

    __PostOrder(proot->left);
    __PostOrder(proot->right);

    std::cout << " " << proot->key;
}

void BinaryTree::PostOrder()
{
    std::cout << "m_size: " << m_size << std::endl;
    __PostOrder(m_root);
    std::cout << std::endl;
}

void BinaryTree::__InOrder(BinaryNode *proot)
{
    if (proot == nullptr)
        return;

    __InOrder(proot->left);
    std::cout << " " << proot->key;
    if (proot->parent)
        printf("\n%d parent:%d\n", proot->key, proot->parent->key);
    __InOrder(proot->right);
}

void BinaryTree::InOrder()
{
    std::cout << "m_size: " << m_size << std::endl;
    __InOrder(m_root);
    std::cout << std::endl;
}

void BinaryTree::__PreOrder(BinaryNode *proot)
{
    if (proot == nullptr)
        return;

    std::cout << " " << proot->key;
    __PreOrder(proot->left);
    __PreOrder(proot->right);
}

void BinaryTree::PreOrder()
{
    std::cout << "m_size: " << m_size << std::endl;
    __PreOrder(m_root);
    std::cout << std::endl;
}

BinaryNode *BinaryTree::__FindNode(BinaryNode *proot, int key)
{
    if (proot == NULL)
    {
        return nullptr;
    }

    if (proot->key > key)
    {
        return __FindNode(proot->left, key);
    }
    else if (proot->key < key)
    {
        return __FindNode(proot->right, key);
    }

    // find node proot
    return proot;
}

BinaryNode *BinaryTree::FindNode(int key)
{
    return __FindNode(m_root, key);
}

#endif // !__BINARY_TREE_H__
