#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#include <iostream>
#include <cstdlib>

// add shard_ptr
// 函数实现通过指针引用类型实现  *&

struct BinaryNode
{
    int data;
    BinaryNode *left;
    BinaryNode *right;
    BinaryNode *parent;

    //struct constructor
    BinaryNode() : data(0), left(nullptr), right(nullptr){};
};

class BinaryTree
{
public:
    BinaryTree();
    ~BinaryTree();

    void PostOrder();
    void InOrder();
    void PreOrder();

    void InsertNode(int data);
    BinaryNode *FindNode(int data);

    int Max(); //最大值
    int Min(); //最小值

    int PreNode(int data);  //前驱结点
    int PostNode(int data); //后继节点

    int Floor(int data);    //向下取整是指小于等于data的最小值
    int Ceilling(int data); //向上取整是指大于data的最小键

    void RemoveAll(); //删除树

    //TODO
    void RemoveNode(int key);

private:
    BinaryNode *__RemoveAll(BinaryNode *proot);
    int __Floor(BinaryNode *proot, int data);
    int __Ceilling(BinaryNode *proot, int data);
    void __PostOrder(BinaryNode *proot);
    void __InOrder(BinaryNode *proot);
    void __PreOrder(BinaryNode *proot);
    BinaryNode *__InsertNode(BinaryNode *proot, int data);
    BinaryNode *__FindNode(BinaryNode *proot, int data);
    int __Max(BinaryNode *proot);
    int __Min(BinaryNode *proot);
    int __PreNode(BinaryNode *proot, int data);
    int __PostNode(BinaryNode *proot, int data);

    BinaryNode *m_root;
    size_t m_size;
};

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

//向上取整是指>该键的最小键； data > proot->key
int BinaryTree::Ceilling(int data)
{
    return __Ceilling(m_root, data);
}

int BinaryTree::__Ceilling(BinaryNode *proot, int data)
{
    if (proot == nullptr)
        return -1;

    if (proot->data <= data)
    {
        return __Ceilling(proot->right, data);
    }
    else
    {
        //proot->data > data: 有可能是Ceilling, 但是还要看左子树中值是否有>data, 如果有则更接近data
        if (proot->left == nullptr)
        {
            return proot->data;
        }
        else
        {
            int tmp = __Ceilling(proot->left, data);
            if (tmp == -1)
                return proot->data;

            return tmp;
        }
    }

    return -1;
}

//向下取整是指小于等于该键的最小值。
int BinaryTree::Floor(int data)
{
    return __Floor(m_root, data);
}

int BinaryTree::__Floor(BinaryNode *proot, int data)
{
    if (proot == nullptr)
        return -1;

    if (proot->data > data)
    {
        return __Floor(proot->left, data);
    }
    else
    {
        //proot->data : 有可能是floot, 但是还要看右子树中值是否有<=data, 如果有则更接近data
        if (proot->right == nullptr)
        {
            return proot->data;
        }
        else
        {
            int tmp = __Floor(proot->right, data);
            if (tmp == -1)
                return proot->data;

            return tmp;
        }
    }

    return -1;
}

int BinaryTree::PostNode(int data)
{
    if (m_root == nullptr)
        return -1;
    return __PostNode(m_root, data);
}

int BinaryTree::__PostNode(BinaryNode *proot, int data)
{
    if (proot == nullptr)
        return -1;

    BinaryNode *p = proot;

    //1. find data by loop
    while (p)
    {
        if (data < p->data)
            p = p->left;
        else if (data > p->data)
            p = p->right;
        else
            break; //find node
    }

    if (p == nullptr)
        return -1;
    // not found data

    //1. have right child tree
    if (p->right)
        return __Min(p->right);

    //若该节点node没有右子树，则沿着parent节点一次往上找，
    //直至parent的左节点==node节点，
    //那么parent就是node的后继节点向上
    for (p; p && p->parent; p = p->parent)
    {
        if (p->parent->left && p->parent->left == p)
            return p->parent->data;
    }

    return -1;
}

int BinaryTree::PreNode(int data)
{
    if (m_root == nullptr)
        return -1;
    return __PreNode(m_root, data);
}

int BinaryTree::__PreNode(BinaryNode *proot, int data)
{
    if (proot == nullptr)
        return -1;

    BinaryNode *p = proot;

    //1. find data by loop
    while (p)
    {
        if (data < p->data)
            p = p->left;
        else if (data > p->data)
            p = p->right;
        else
            break; //find node
    }

    if (p == nullptr)
        return -1;
    // not found data

    //2.1 have left child tree
    if (p->left)
        return __Max(p->left);

    if (p->parent && p->parent->right == p)
    {
        //2.2.1 is pp->right ?
        return p->parent->data;
    }
    else if (p->parent && p->parent->left == p)
    {
        //2.2.2 is pp->left ?
        if (p->parent->parent)
        {
            if (p->parent->parent->right == p->parent)
                return p->parent->parent->data;
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
        return proot->data;
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
        return proot->data;
}

BinaryTree::BinaryTree() : m_root(nullptr), m_size(0)
{
}

BinaryTree::~BinaryTree()
{
}

void BinaryTree::InsertNode(int data)
{
    m_root = __InsertNode(m_root, data);
}

BinaryNode *BinaryTree::__InsertNode(BinaryNode *proot, int data)
{
    //find null node
    if (proot == nullptr)
    {
        //new 不初始化， new()进行初始化
        BinaryNode *node = new BinaryNode();
        if (node != nullptr)
        {
            node->data = data;
            proot = node;
            m_size += 1;
        }

        return proot;
    }

    if (data < proot->data)
    {
        proot->left = __InsertNode(proot->left, data);
        proot->left->parent = proot;
    }
    else if (data > proot->data)
    {
        proot->right = __InsertNode(proot->right, data);
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

    std::cout << " " << proot->data;
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
    std::cout << " " << proot->data;
    if (proot->parent)
        printf("\n%d parent:%d\n", proot->data, proot->parent->data);
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

    std::cout << " " << proot->data;
    __PreOrder(proot->left);
    __PreOrder(proot->right);
}

void BinaryTree::PreOrder()
{
    std::cout << "m_size: " << m_size << std::endl;
    __PreOrder(m_root);
    std::cout << std::endl;
}

BinaryNode *BinaryTree::__FindNode(BinaryNode *proot, int data)
{
    if (proot == NULL)
    {
        return nullptr;
    }

    if (proot->data > data)
    {
        return __FindNode(proot->left, data);
    }
    else if (proot->data < data)
    {
        return __FindNode(proot->right, data);
    }

    // find node proot
    return proot;
}

BinaryNode *BinaryTree::FindNode(int data)
{
    return __FindNode(m_root, data);
}

#endif // !__BINARY_TREE_H__
