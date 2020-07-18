#ifndef __RISKREDIS__H__
#define __RISKREDIS__H__

#include <iostream>
#include <string>
#include <vector>

#include "nlohmann/json.hpp"

using namespace std;
using namespace nlohmann;

class RiskRedis
{
public:
    RiskRedis(){};
    RiskRedis(string addr, string passwd, int db, string sub, std::string pub) 
    : addr(addr), passwd(passwd), db(db), pub(pub){};

    friend void to_json(json &j, const RiskRedis &p)
    {
        j = json{
            {"addr", p.addr},
            {"passwd", p.passwd},
            {"db", p.db},
            {"pub", p.sub},
            {"pub", p.pub}
        };
    }

    friend void from_json(const json &j, RiskRedis &p)
    {
        j.at("addr").get_to(p.addr);
        j.at("passwd").get_to(p.passwd);
        j.at("db").get_to(p.db);
        j.at("sub").get_to(p.sub);
        j.at("pub").get_to(p.pub);
    }

    friend ostream &operator<<(ostream &output, const RiskRedis &b)
    {
        cout << "addr:" << b.addr << endl;
        cout << "passwd:" << b.passwd << endl;
        cout << "db:" << b.db << endl;
        cout << "sub:" << b.sub << endl;
        cout << "pub:" << b.pub << endl;

        return output;
    }

private:
    string addr;
    string passwd;
    int db = 0;
    string sub;
    string pub;
};

#endif  //!__RISKREDIS__H__