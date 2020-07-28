#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#include <iostream>

struct Node
{
    Node *left;
    Node *right;
    int data;
};

class Tree
{
public:
    Tree(){};
    ~Tree(){};
    void Insert(int key);
    void Find(int key);
    void RemoveNode(int key);
    int Max();
    int Min();
    int PreNode();
    int PostNode();
    int Floor();    //向下取整
    int Ceilling(); //向上取整
    void RemoveAll();
    void PreOrder();
    void InOrder();
    void PostOrder();

private:
};

void Tree::InOrder(Node root){
	if(root==null) return;
	inOrder(root.left);
	Systrm.out.println(root.data);
	inOrder(root.right);
}

#endif // !__BINARY_TREE_H__
