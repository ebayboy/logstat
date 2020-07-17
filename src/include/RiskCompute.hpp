#ifndef __RiskCompute_HPP_
#define __RiskCompute_HPP_

#include <iostream>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

using namespace std;
using namespace nlohmann;

class StatPolicy
{
    StatPolicy(){};
    StatPolicy(string desc, string name, string expr) : desc(desc), name(name), expr(expr){};
    ~StatPolicy(){};

    friend void to_json(nlohmann::json &j, const StatPolicy &p)
    {
        j = json{
            {"name", p.name},
            {"expr", p.expr},
            {"desc", p.desc}};
    }
    friend void from_json(const nlohmann::json &j, StatPolicy &p)
    {
        j.at("desc").get_to(p.desc);
        j.at("name").get_to(p.name);
        j.at("expr").get_to(p.expr);
    }
    friend ostream &operator<<(ostream &output, const StatPolicy &b)
    {
        cout << "desc:" << b.desc << endl;
        cout << "name:" << b.name << endl;
        cout << "expr:" << b.expr << endl;

        return output;
    }

private:
    string desc;
    string name;
    string expr;
};

class RiskRule
{
public:
    RiskRule(){};
    RiskRule(string desc, string expr) : desc(desc), expr(expr){};
    ~RiskRule(){};

    friend void to_json(nlohmann::json &j, const RiskRule &p)
    {
        j = json{
            {"expr", p.expr},
            {"desc", p.desc}};
    }
    friend void from_json(const nlohmann::json &j, RiskRule &p)
    {
        j.at("desc").get_to(p.desc);
        j.at("expr").get_to(p.expr);
    }
    friend ostream &operator<<(ostream &output, const RiskRule &b)
    {
        cout << "desc:" << b.desc << endl;
        cout << "expr:" << b.expr << endl;

        return output;
    }

private:
    string desc;
    string expr;
};

class RiskPolicy
{
public:
    RiskPolicy(){};
    RiskPolicy(string name, string desc, string logic, vector<RiskRule> rules) : name(name), desc(desc), logic(logic), rules(rules){};
    ~RiskPolicy(){};

    friend class RiskRule;
    friend void to_json(nlohmann::json &j, const RiskPolicy &p)
    {
        j = json{
            {"name", p.name},
            {"desc", p.desc},
            {"logic", p.logic},
            {"rules", p.rules}};
    }

    friend void from_json(const nlohmann::json &j, RiskPolicy &p)
    {
        j.at("name").get_to(p.name);
        j.at("desc").get_to(p.desc);
        j.at("logic").get_to(p.logic);
        j.at("rules").get_to(p.rules);
    }
    friend ostream &operator<<(ostream &output, const RiskPolicy &b)
    {
        cout << "name:" << b.name << endl;
        cout << "desc:" << b.desc << endl;
        cout << "logic:" << b.logic << endl;

        for (auto &&i : b.rules)
        {
            cout << i << endl;
        }

        return output;
    }

private:
    string name;
    string desc;
    string logic;
    vector<RiskRule> rules;
};

class RiskCompute
{
public:
    friend class StatPolicy;
    friend class RiskPolicy;
    RiskCompute(){};
    RiskCompute(vector<StatPolicy> s, vector<RiskPolicy> r) : statspolicys(s), riskpolicys(r){};
    ~RiskCompute(){};

    friend void to_json(nlohmann::json &j, const RiskCompute &p)
    {
        j = json{
            {"statspolicys", p.statspolicys},
            {"riskpolicys", p.riskpolicys}};
    }

    friend void from_json(const nlohmann::json &j, RiskCompute &p)
    {
        j.at("statspolicys").get_to(p.statspolicys);
        j.at("riskpolicys").get_to(p.riskpolicys);
    }

    friend ostream &operator<<(ostream &output, const RiskCompute &b)
    {
        for (auto &&j : b.statspolicys)
        {
            cout << j << endl;
        }

        for (auto &&i : b.riskpolicys)
        {
            cout << i << endl;
        }

        return output;
    }

private:
    std::vector<StatPolicy> statspolicys;
    std::vector<RiskPolicy> riskpolicys;
};

#endif // !__RiskCompute_HPP_