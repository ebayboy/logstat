#ifndef __RISKOUTPUT_HPP_
#define __RISKOUTPUT_HPP_

#include <iostream>
#include <string>
#include <vector>

#include "nlohmann/json.hpp"
#include "RiskRedis.hpp"

using namespace std;
using namespace nlohmann;

class RiskOutput
{
public:
    friend class RiskRedis;
    RiskOutput(){};
    RiskOutput(std::string prefix,
               bool hash,
               std::vector<RiskRedis> redis) : prefix(prefix), hash(hash), redis(redis){};
    ~RiskOutput(){};
    friend void to_json(nlohmann::json &j, const RiskOutput &p)
    {
        j = json{{"prefix", p.prefix},
                 {"hash", p.hash},
                 {"redis", p.redis}};
    }

    friend void from_json(const nlohmann::json &j, RiskOutput &p)
    {
        j.at("prefix").get_to(p.prefix);
        j.at("hash").get_to(p.hash);
        j.at("redis").get_to(p.redis);
    }

    friend ostream &operator<<(ostream &output, const RiskOutput &b)
    {
        cout << "prefix:" << b.prefix << endl;
        cout << "hash:" << b.hash << endl;

        //print redis
        for (auto &&j : b.redis)
        {
            cout << "redis: " << j << endl;
        }

        return output;
    }

private:
    std::string prefix;
    bool hash;
    std::vector<RiskRedis> redis;
};

#endif // !__RISKOUTPUT_HPP_