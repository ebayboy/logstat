#ifndef __RiskCompute_HPP_
#define __RiskCompute_HPP_

#include <iostream>
#include <string>
#include <vector>

#include "nlohmann/json.hpp"

class StatsPolicy
{
public:
    StatsPolicy() = default;
    StatsPolicy(std::string name, std::string desc, std::string expr) : name(name), desc(desc), expr(expr){};
    ~StatsPolicy() = default;

    friend void to_json(nlohmann::json &j, const StatsPolicy &p)
    {
        j = nlohmann::json{
            {"name", p.name},
            {"desc", p.desc},
            {"expr", p.expr}};
    }

    friend void from_json(const nlohmann::json &j, StatsPolicy &p)
    {
        try
        {
            j.at("name").get_to(p.name);
            j.at("desc").get_to(p.desc);
            j.at("expr").get_to(p.expr);
        }
        catch (const nlohmann::json::parse_error &)
        {
            // parse errors are ok, because input may be random bytes
        }
        catch (const nlohmann::json::type_error &)
        {
            // type errors can occur during parsing, too
        }
        catch (const nlohmann::json::out_of_range &)
        {
            // out of range errors can occur during parsing, too
        }
    }

    friend ostream &operator<<(ostream &output, const StatsPolicy &b)
    {
        cout << "name:" << b.name << endl;
        cout << "desc:" << b.desc << endl;
        cout << "expr:" << b.expr << endl;

        return output;
    }

private:
    std::string name;
    std::string desc;
    std::string expr;
};

class RiskRule
{
public:
    RiskRule(){};
    RiskRule(std::string desc, std::string expr) : desc(desc), expr(expr){};
    ~RiskRule(){};

    friend void to_json(nlohmann::json &j, const RiskRule &p)
    {
        j = nlohmann::json{
            {"expr", p.expr},
            {"desc", p.desc}};
    }
    friend void from_json(const nlohmann::json &j, RiskRule &p)
    {
        try
        {
            j.at("desc").get_to(p.desc);
            j.at("expr").get_to(p.expr);
        }
        catch (const nlohmann::json::parse_error &)
        {
            // parse errors are ok, because input may be random bytes
        }
        catch (const nlohmann::json::type_error &)
        {
            // type errors can occur during parsing, too
        }
        catch (const nlohmann::json::out_of_range &)
        {
            // out of range errors can occur during parsing, too
        }
    }
    friend ostream &operator<<(ostream &output, const RiskRule &b)
    {
        cout << "desc:" << b.desc << endl;
        cout << "expr:" << b.expr << endl;

        return output;
    }

private:
    std::string desc;
     std::string expr;
};

class RiskPolicy
{
public:
    RiskPolicy(){};
    RiskPolicy( std::string name,  std::string desc,  std::string logic,  std::vector<RiskRule> rules) 
    : name(name), desc(desc), logic(logic), rules(rules){};
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
        try
        {
            j.at("name").get_to(p.name);
            j.at("desc").get_to(p.desc);
            j.at("logic").get_to(p.logic);
            j.at("rules").get_to(p.rules);
        }
        catch (const nlohmann::json::parse_error &)
        {
            // parse errors are ok, because input may be random bytes
        }
        catch (const nlohmann::json::type_error &)
        {
            // type errors can occur during parsing, too
        }
        catch (const nlohmann::json::out_of_range &)
        {
            // out of range errors can occur during parsing, too
        }
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
    std::string name;
    std::string desc;
    std::string logic;
    vector<RiskRule> rules;
};
class RiskCompute
{
public:
    friend class StatsPolicy;
    friend class RiskPolicy;
    RiskCompute(){};
    RiskCompute(vector<StatsPolicy> statspolicys, vector<RiskPolicy> riskpolicys)
        : statspolicys(statspolicys), riskpolicys(riskpolicys){};
    ~RiskCompute(){};

    friend void to_json(nlohmann::json &j, const RiskCompute &p)
    {
        j = nlohmann::json{{"statspolicys", p.statspolicys},
                 {"riskpolicys", p.riskpolicys}};
    }

    friend void from_json(const nlohmann::json &j, RiskCompute &p)
    {
        try
        {
            j.at("statspolicys").get_to(p.statspolicys);
            j.at("riskpolicys").get_to(p.riskpolicys);
        }
        catch (nlohmann::json::out_of_range &)
        {
        }
    }

    friend ostream &operator<<(ostream &output, const RiskCompute &b)
    {
        cout << "Show StatsPolicys:=================" << endl;
        for (auto &&i : b.statspolicys)
        {
            cout << i << endl;
        }

        cout << "Show RiskPolicys:=================" << endl;
        for (auto &&i : b.riskpolicys)
        {
            cout << i << endl;
        }

        return output;
    }

private:
    vector<StatsPolicy> statspolicys;
    vector<RiskPolicy> riskpolicys;
};

#endif // !__RiskCompute_HPP_