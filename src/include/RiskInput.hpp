#ifndef __RISKINPUT_HPP_
#define __RISKINPUT_HPP_

#include <iostream>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

using namespace std;
using namespace nlohmann;

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

    friend ostream &operator<<(ostream &output, const RiskRedis &b)
    {
        cout << "addr:" << b.addr << endl;
        cout << "passwd:" << b.passwd << endl;
        cout << "db:" << b.db << endl;
        cout << "sub:" << b.sub << endl;

        return output;
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
        //j = json{{"name", p.name}, {"address", p.address}, {"age", p.age}};
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