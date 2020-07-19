#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

template<class x, class y>
class MapFunction
{

public:
    MapFunction()
    {
        this->RegisteFunc("-", std::minus<float>());
        this->RegisteFunc("+", std::plus<float>());
        this->RegisteFunc("*", std::multiplies<float>());
        this->RegisteFunc("/", std::divides<float>());

        this->RegisteFunc("EQ", [](float x, float y) { return x == y; });
        this->RegisteFunc("GT", [](float x, float y) { return x > y; });
        this->RegisteFunc("LT", [](float x, float y) { return x < y; });
        this->RegisteFunc("GE", [](float x, float y) { return x >= y; });
        this->RegisteFunc("LE", [](float x, float y) { return x <= y; });

        this->RegisteFunc("and", [](vector<bool> v) { std::accumulate(v.begin(), v.end(), [](bool x, bool y) { return x & y; }); });
    };

    ~MapFunction(){};

    void RegisteFunc(string name, std::function<float(float, float)> func)
    {
        this->_funcs.insert(make_pair(name, func));
    }

private:
    map<string, function<float(float, float)>> _funcs;
};
