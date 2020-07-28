#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#include <iostream>
#include <cstdlib>

// add shard_ptr

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

    int Max();             //最大值
    int Min();             //最小值
    int PreNode(int data); //前驱结点

    //TODO
    int PostNode(int data); //后继节点
    int Floor(int data);    //向下取整
    int Ceilling(int data); //向上取整
    void RemoveAll();       //删除树
    void RemoveNode(int key);

private:
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

    BinaryNode *p = proot /* point to current */, *pp = nullptr;

    //1. find data by loop
    while (p)
    {
        if (data < p->data)
        {
            pp = p;
            p = p->left;
        }
        else if (data > p->data)
        {
            pp = p;
            p = p->right;
        }
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
    while (p)
    {
        if (p->parent == nullptr || p->parent->left == nullptr)
        {
            continue;
        }
        printf("p->parent:%d left:%d\n", p->parent, p->parent->left);

        if (p->parent->left == p)
        {
            return p->parent->data;
        }
        p = p->parent;
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

    BinaryNode *p = proot /* point to current */, *pp = nullptr /* point to parent */, *ppp = nullptr /* point to parent's parent */;

    //1. find data by loop
    while (p)
    {
        if (data < p->data)
        {
            ppp = pp;
            pp = p;
            p = p->left;
        }
        else if (data > p->data)
        {
            ppp = pp;
            pp = p;
            p = p->right;
        }
        else
            break; //find node
    }

    if (p == nullptr)
        return -1;
    // not found data

    //2.1 have left child tree
    if (p->left)
        return __Max(p->left);

    if (pp && pp->right == p)
    {
        //2.2.1 is pp->right ?
        return pp->data;
    }
    else if (pp && pp->left == p)
    {
        //2.2.2 is pp->left ?
        if (ppp && ppp->right == pp)
            return ppp->data;
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
    if (proot == nullptr)
    {
        return;
    }

    __PostOrder(proot->left);
    __PostOrder(proot->right);

    std::cout << " " << proot->data;
}

void BinaryTree::PostOrder()
{
    __PostOrder(m_root);
    std::cout << std::endl;
}

void BinaryTree::__InOrder(BinaryNode *proot)
{
    if (proot == nullptr)
    {
        return;
    }

    __InOrder(proot->left);
    std::cout << " " << proot->data;
    if (proot->parent)
        printf("\n%d parent:%d\n", proot->data, proot->parent->data);
    __InOrder(proot->right);
}

void BinaryTree::InOrder()
{
    __InOrder(m_root);
    std::cout << std::endl;
}

void BinaryTree::__PreOrder(BinaryNode *proot)
{
    if (proot == nullptr)
    {
        return;
    }

    std::cout << " " << proot->data;
    __PreOrder(proot->left);
    __PreOrder(proot->right);
}

void BinaryTree::PreOrder()
{
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
