#ifndef CALCULATOR_H
#define CALCULATOR_H
#include "calculator.h"
#include <stack>
#include <string>
#include <vector>
#include <map>
#include  <iostream>
#include <math.h>
using namespace std;

class Calculator
{
public:
    Calculator();
    double calculate(string &expr);
    void setVariable(string var, double value);

private:
    const double PI = 3.14159265359;
    map <string, double> variables; // stores names and values of variables
    void getNextActions(string &expr, int currentPosiotion, stack<string> &mathActions, stack<double> &digits, vector <string> &nextActions, string &tmp);
    void estimateOneAction(string &action, stack<double> &digits);
    void estimateNextActions(vector<string> &nextActions, stack<double> &digits);
    void estimateNextActions(stack<string> &nextActions, stack<double> &digits);
    void estimateOneOperation(string &action, stack<double> &digits);
    void estimateOneFunction(string &action, stack<double> &digits);
    bool isDigit(char c);
    bool isFunction(string s);
    bool isOper(char c);
    bool isOper(string s);
    bool isVariable(string s);
    double stringToDouble(string s);
    void addActionInOrder(string s, stack <string> &mathActions, vector<string> &nextActions);
    int getActionPriority(string action);

};

#endif // CALCULATOR1_H


