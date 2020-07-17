#ifndef __RISKINPUT_HPP_
#define __RISKINPUT_HPP_

#include <iostream>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

class RiskRedis
{
public:
    RiskRedis(){};
    RiskRedis(std::string addr, std::string passwd, int db, std::string sub) : addr(addr), passwd(passwd), db(db), sub(sub){};

    friend void to_json(nlohmann::json &j, const RiskRedis &p)
    {
        j = nlohmann::json{
            {"addr", p.addr},
            {"passwd", p.passwd},
            {"db", p.db},
            {"sub", p.sub},
        };
    }

    friend void from_json(const nlohmann::json &j, RiskRedis &p)
    {
        j.at("addr").get_to(p.addr);
        j.at("passwd").get_to(p.passwd);
        j.at("db").get_to(p.db);
        j.at("sub").get_to(p.sub);
    }

private:
    std::string addr;
    std::string passwd;
    int db = 0;
    std::string sub;
};

class RiskInput
{
public:
    friend class RiskRedis;
    RiskInput(){};
    RiskInput(std::string hkeysplit,
              std::vector<std::string> hkey,
              std::string split,
              std::vector<std::string> cols,
              std::vector<RiskRedis> redis) : hkeysplit(hkeysplit),
                                                hkey(hkey),
                                                split(split),
                                                cols(cols),
                                                redis(redis){};
    ~RiskInput(){};
    friend void to_json(nlohmann::json &j, const RiskInput &p)
    {
        //j = json{{"name", p.name}, {"address", p.address}, {"age", p.age}};
    }
    friend void from_json(const nlohmann::json &j, RiskInput &p)
    {
        /*
        j.at("name").get_to(p.name);
        j.at("address").get_to(p.address);
        j.at("age").get_to(p.age);
        */
    }

private:
    std::string hkeysplit = "_";
    std::vector<std::string> hkey;
    std::string split = "|";
    std::vector<std::string> cols;
    std::vector<RiskRedis> redis;
};

#endif // !__RISKINPUT_HPP_