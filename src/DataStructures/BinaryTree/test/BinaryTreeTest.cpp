#include <bits/stdc++.h>

#include "BinaryTree.hpp"

using namespace  std;


int main(int args, char **argv)
{
    int a[5] = {4, 3, 5, 2, 1};
    BinaryTree b;

    for (size_t i = 0; i < sizeof(a) / sizeof(int); i++)
    {
        b.InsertNode(a[i]);
    }

    cout << "PreOrder:" << endl;
    b.PreOrder();

    cout << "InOrder:" << endl;
    b.InOrder();

    cout << "PostOrder:" << endl;
    b.PostOrder();

    BinaryNode *n = b.FindNode(3);
    if (n)
    {
        cout << "n:" << n->data;
    }
    else
    {
        cout << "not find n!" << endl;
    }

    return 0;
}