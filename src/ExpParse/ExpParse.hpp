#ifndef __EXPPARSE_H__
#define __EXPPARSE_H__

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//AVG(ip, total, 5)
//GT(ip_total_5m, 1)
class ExpParse
{
public:
    ExpParse(string type, string exp) : type(type), exp(exp)
    {

        vector<string> result;
        string temp("");
        for (size_t i = 0; i < exp.size(); i++)
        {
            if (exp[i] == '(' || exp[i] == ')' || exp[i] == ',' || exp[i] == '/')
            {
                result.push_back(temp);
                temp = "";
            }
            else
            {
                temp += exp[i];
            }
        }

        this->funcName = result.at(0);
        this->lastVar = result.at(result.size() - 1);

        if (this->type.compare("stat") == 0)
        {
            this->statField = result.at(1);
            this->vars.assign(result.begin() + 2, result.end() - 1);
        }
        else
        {
            this->vars.assign(result.begin() + 1, result.end() - 1);
        }
    }
    ~ExpParse(){};

    friend ostream &operator<<(ostream &output, const ExpParse &b)
    {
        cout << "exp:" << b.exp << endl;
        cout << "funcName:" << b.funcName << endl;
        cout << "lastVar:" << b.lastVar << endl;
        if (b.statField.size() > 0)
        {
            cout << "statField:" << b.statField << endl;
        }

        for (auto &&i : b.vars)
        {
            cout << "var:" << i << endl;
        }

        return output;
    }

private:
    string type;
    string exp;
    string funcName;
    string statField;
    vector<string> vars;
    string lastVar;
};

#endif // !__EXPPARSE_H__
