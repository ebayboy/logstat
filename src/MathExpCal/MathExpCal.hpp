/* 实现数学表达式计算：（中缀表达式转后缀表达式）
1. 基于二叉树

2. 基于堆栈
Pre order -> Post Order
PreOrder:5*(2+3-4)-1
PostOrder:5 2 3 4 - + * 1 -
2*(1+3)-5  -> 2 1 3 + * 5 -
result:
result  operator_stack 
5 *
5 *(
52 *(
52 *(+
523 *(+
523 *(+-
5234 *(+-  因为top +和比较的-为同一优先级， 不输出操作符
5234-+ * 
5234-+* -
5234-+*1 -
5234-+*1-
*/

//usage: MathExpCal m;

#ifndef __MATHEXPCAL_h__
#define __MATHEXPCAL_h__

#include <iostream>
#include <string>
#include <stack>
#include <math.h>

using namespace std;

class MathExpCal
{
public:
    MathExpCal(){};
    ~MathExpCal(){};
    double ExpressionCal(string str);

protected:
    bool Prior(char op1, char op2);
    bool IsOpera(char x);
    string PreToPost(string exp);
    double Calculate(double op1, double op2, char oper);

private:
    stack<double> S; //存放操作数op1 op2
};

bool MathExpCal::Prior(char op1, char op2)
{
    if ((op1 == '*' || op1 == '/') && (op2 == '+' || op2 == '-'))
    {
        return true;
    }

    return false;
}

bool MathExpCal::IsOpera(char x) //操作符判断
{
    if (x == '+' || x == '-' || x == '*' || x == '/' || x == '(' || x == ')')
        return true;
    else
        return false;
}

string MathExpCal::PreToPost(string exp)
{
    string result;    //保存输出后缀表达式
    stack<char> optr; //存放操作符  +-*/()

    for (size_t i = 0; i < exp.size(); i++)
    {
        if (exp[i] == '(')
        {
            optr.push(exp[i]);
        }
        else if (exp[i] == ')')
        {
            while (optr.top() != '(')
            {
                result += optr.top();
                result += " ";
                optr.pop();
            }
            optr.pop();
        }
        else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/')
        {
            while (!optr.empty() && optr.top() != '(' && Prior(optr.top(), exp[i]))
            {
                result += optr.top();
                result += " ";
                optr.pop();
            }
            optr.push(exp[i]);
        }
        else
        {
            result += exp[i];
            if (IsOpera(exp[i + 1]) || exp[i + 1] == '\0') //next is operator or end
            {
                result += " ";
            }
        }
    }

    while (!optr.empty())
    {
        result += optr.top();
        result += " ";
        optr.pop();
    }

    return result;
}

double MathExpCal::Calculate(double op1, double op2, char oper)
{
    switch (oper)
    {
    case '+':
        return op1 + op2;
    case '-':
        return op1 - op2;
    case '*':
        return op1 * op2;
    case '/':
        return op1 / op2;
    }

    return 0;
}

double MathExpCal::ExpressionCal(string str)
{
    string sub_str;

    if (str.length() == 0)
    {
        throw std::invalid_argument("Error: str.length == 0");
    }

    str = PreToPost(str);
    double op1, op2, final_resl;
    size_t i = 0;

    while (i < str.size() - 1)
    {
        if (!IsOpera(str[i]))
        {
            //表达式入栈S
            for (; str[i] != ' '; i++)
            {
                if (!IsOpera(str[i]))
                    sub_str += str[i];
            }
            i++;
            S.push(std::atof(sub_str.c_str()));
            sub_str.erase(0, sub_str.size());
        }
        else
        {
            //操作数入栈
            op2 = S.top();
            S.pop();
            op1 = S.top();
            S.pop();
            final_resl = Calculate(op1, op2, str[i]);
            S.push(final_resl);
            i += 2;
        }
    }

    return final_resl;
}

#endif // !__MATHEXPCAL_h__
