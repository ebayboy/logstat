#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#include <iostream>

struct Node {
    Node *left;
    Node *right;
    int value;
};

class Tree {
    void Find(int key);
    void RemoveNode(int key);
    int  Max();
    int Min();
    int PreNode();
    int PostNode();
    int Floor();  //向下取整
    int Ceilling(); //向上取整
    void RemoveAll();

    void PreOrder();
    void InOrder();
    void PostOrder();
};

#endif // !__BINARY_TREE_H__
