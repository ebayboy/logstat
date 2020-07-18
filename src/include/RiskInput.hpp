#ifndef __RISKINPUT_HPP_
#define __RISKINPUT_HPP_

#include <iostream>
#include <string>
#include <vector>

#include "nlohmann/json.hpp"
#include "RiskRedis.hpp"

using namespace std;
using namespace nlohmann;

class RiskInput
{
public:
    friend class RiskRedis;
    RiskInput(){};
    RiskInput(std::string hkeysplit,
              std::string split,
              std::vector<std::string> hkey,
              std::vector<std::string> cols,
              std::vector<RiskRedis> redis) : hkeysplit(hkeysplit),
                                              split(split),
                                              hkey(hkey),
                                              cols(cols),
                                              redis(redis){};
    ~RiskInput(){};
    friend void to_json(nlohmann::json &j, const RiskInput &p)
    {
        j = json{
            {"hkeysplit", p.hkeysplit},
            {"split", p.split},
            {"hkey", p.hkey},
            {"cols", p.cols},
            {"redis", p.redis}};
    }

    friend void from_json(const nlohmann::json &j, RiskInput &p)
    {
        j.at("hkeysplit").get_to(p.hkeysplit);
        j.at("split").get_to(p.split);
        j.at("hkey").get_to(p.hkey);
        j.at("cols").get_to(p.cols);
        j.at("redis").get_to(p.redis);
    }

    friend ostream &operator<<(ostream &output, const RiskInput &b)
    {
        //print cols
        cout << "cols:" << endl;
        for_each(b.cols.begin(), b.cols.end(), [&](string x) -> void { cout << x << " "; });
        cout << endl;

        //print  hkey
        cout << "hkey: " << endl;
        for (auto &&i : b.hkey)
        {
            cout << i << " ";
        }
        cout << endl;

        //print redis
        for (auto &&j : b.redis)
        {
            cout << "redis: " << j << endl;
        }

        cout << "split:" << b.split << endl;
        cout << "hkeysplit:" << b.hkeysplit << endl;

        return output;
    }

private:
    std::string hkeysplit;
    std::string split;
    std::vector<std::string> hkey;
    std::vector<std::string> cols;
    std::vector<RiskRedis> redis;
};

#endif // !__RISKINPUT_HPP_