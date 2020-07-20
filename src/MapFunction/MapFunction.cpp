#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <numeric>
#include <vector>
#include <functional>

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

        this->RegisteFunc("and", [](std::vector<bool> v) {
            return std::accumulate(v.begin(), v.end(), 1, [](bool a, bool b) { return a & b; });
        });
    };

    ~MapFunction(){};

    void RegisteFunc(std::string name, std::function<float(float, float)> func)
    {
        this->_funcs.insert(make_pair(name, func));
    }

    void RegisteFunc(std::string name, std::function<int(std::vector<bool>)> func)
    {
        this->_funcs_logic.insert(make_pair(name, func));
    }

    friend std::ostream &operator<<(std::ostream &output, const MapFunction &b)
    {
        std::cout << "FUNCS:" << std::endl;
        for (auto &&i : b._funcs)
        {
            std::cout << i.first << std::endl;
        }

        std::cout << "FUNCS_LOGIC:" << std::endl;
        for (auto &&i : b._funcs_logic)
        {
            std::cout << i.first << std::endl;
        }

        return output;
    }

private:
    std::map<std::string, std::function<float(float, float)>> _funcs;
    std::map<std::string, std::function<int(std::vector<bool>)>> _funcs_logic;
};
