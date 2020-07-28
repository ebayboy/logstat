#include <bits/stdc++.h>

#include "BinaryTree.hpp"

using namespace std;

int main(int args, char **argv)
{
    int a[] = {3,1,6,4,5};
    BinaryTree b;

    for (size_t i = 0; i < sizeof(a) / sizeof(int); i++)
    {
        std::cout << "insert:" << a[i] << endl;
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
    cout << endl;

    cout << "Max:" << b.Max() << endl;

    cout << "Min:" << b.Min() << endl;

    cout << "PreNode(1):" << b.PreNode(1) << endl;

    cout << "PostNode(5):" << b.PostNode(5) << endl;

    return 0;
}