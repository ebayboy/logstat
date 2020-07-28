#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__



#include <iostream>
#include <string>
#include <cstdio>

struct BinaryNode
{
    int data;
    BinaryNode *left;
    BinaryNode *right;

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

private:
    void __PostOrder(BinaryNode *proot);
    void __InOrder(BinaryNode *proot);
    void __PreOrder(BinaryNode *proot);
    BinaryNode *__InsertNode(BinaryNode *proot, int data);
    BinaryNode *__FindNode(BinaryNode *proot, int data);

    BinaryNode *m_root;
    size_t m_size;
};

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

    if (data < m_root->data)
    {
        proot->left = __InsertNode(proot->left, data);
    }
    else if (data > proot->data)
    {
        proot->right = __InsertNode(proot->right, data);
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
