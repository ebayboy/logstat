#include <bits/stdc++.h>

#include "BinaryTree.hpp"

using namespace std;

int main(int args, char **argv)
{
    int a[] = {41,27,11,10,13,29,65};
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

    cout << "PreNode(13):" << b.PreNode(13) << endl;

    cout << "PostNode(13):" << b.PostNode(13) << endl;

    cout << "Floor(19):" << b.Floor(19) << endl;

    cout << "Ceilling(19):" << b.Ceilling(19) << endl;

    b.RemoveAll();
    cout << "RemoveAll InOrder:" << endl;
    b.InOrder();


    return 0;
}