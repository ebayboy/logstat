#include <iostream>
#include <string>
#include <vector>

#include "../MathExpCal.hpp"

using namespace std;

int main()
{
    string str = "5*(2+3-4)-1";
    MathExpCal m;
    double final_resl = 0;
    try
    {
        final_resl = m.ExpressionCal(str);
        cout << "final_resl:" << final_resl << endl;
    }
    catch (exception &ex)
    {
        cout << ex.what() << endl;
    }

    return 0;
}