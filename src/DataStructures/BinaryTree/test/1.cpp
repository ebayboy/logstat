/*

*/
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

int main(int args, char **argv)
{
    queue<int> q;
    queue<int> m;

    for (size_t i = 0; i < 5; i++)
    {
        m.push(i);
    }

    m.swap(q);

    cout << "q.size:" << q.size() << endl;
    cout << "m.size:" << m.size() << endl;

    return 0;
}
