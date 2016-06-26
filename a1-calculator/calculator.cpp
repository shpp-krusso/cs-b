#include "calculator.h"

Calculator::Calculator() {

}


/* @param string expr a math expression.
* Returns a result of calculation current expression*/
double Calculator::calculate(string &expr) {
    stack<string> mathActions;
    stack<double> digits;
    vector<string> nextActions;
    string tmp = "";
    for (int i = 0; i < expr.size(); i++) {
        getNextActions(expr, i, mathActions, digits, nextActions, tmp);
        if (!nextActions.empty()) {
            estimateNextActions(nextActions, digits);
        }
    }
    while (!mathActions.empty()) {
        string s = mathActions.top();
        mathActions.pop();
        nextActions.push_back(s);
    }
    estimateNextActions(nextActions, digits);
    return digits.top();
}

/* If operations or functions will have pressed out of the stack, they will have added to a vector nextActions*/
void Calculator::getNextActions(string &expr, int currentPosition, stack<string> &mathActions, stack<double> &digits, vector <string> &nextActions, string &tmp) {
    if (isFunction(tmp)) {
        addActionInOrder(tmp, mathActions, nextActions);
        tmp = "";
    }

    if (isDigit(expr[currentPosition])) {
        if (tmp != "") {
            if (isVariable(tmp)) {
                digits.push(variables[tmp]);
                tmp = "";
            }

        }
        tmp += expr[currentPosition];
        if (!isDigit(expr[currentPosition + 1]) && expr[currentPosition + 1] != '.') {
            digits.push(stringToDouble(tmp));
            tmp = "";
        }
    } else if (isOper(expr[currentPosition])) {
        if (isVariable(tmp)) {
            digits.push(variables[tmp]);
            tmp = "";
        }
        if (tmp != "") {
            tmp = "";
        }
        tmp += expr[currentPosition];
        addActionInOrder(tmp, mathActions, nextActions);
        tmp = "";
    } else {
        tmp += expr[currentPosition];
    }
}


void Calculator::estimateOneAction(string &action, stack<double> &digits) {
    if (isOper(action))
        estimateOneOperation(action, digits);
    else if (isFunction(action))
        estimateOneFunction(action, digits);
}

/* @param - string s
 * Return true if parameter is a variable, that user has entered earlier
*/
bool Calculator::isVariable(string s) {
    return variables.find(s) != variables.end();
}

/* Estimate every action in the vector from [0]'th position to last.*/
void Calculator::estimateNextActions(vector<string> &nextActions, stack<double> &digits) {
    for (int i = 0; i < nextActions.size(); i++) {
        estimateOneAction(nextActions[i], digits);
    }
    nextActions.clear();
}

/* Estimate every action in the stack.*/
void Calculator::estimateNextActions(stack<string> &nextActions, stack<double> &digits) {
    while (!nextActions.empty()) {
        estimateOneAction(nextActions.top(), digits);
        nextActions.pop();
    }
}

/*
 * Return true, if parameter is a digit*/
bool Calculator::isDigit(char c) {
    return (c - '0') >= 0 && (c - '0') <= 9;
}

/* Return true if parameter is a function, that is define in calculator.*/
bool Calculator::isFunction(string s) {
    vector<string> functions = {"sin", "cos", "tg"};
    for (int i = 0; i < functions.size(); i++) {
        if (s == functions[i])
            return true;
    }
    return false;
}

/* Return true if paramater is an operator*/
bool Calculator::isOper(char c) {
    vector<char> opers;
    opers = {'*', '/', '-', '+', '(', ')'};

    for (int i = 0; i < opers.size(); i++) {
        if (c == opers[i]) {
            return true;
        }
    }
    return false;
}

/* Return true if paramater is an operator*/
bool Calculator::isOper(string s) {
    vector<string> operations = {"+", "-", "*", "/", "(", ")"};
    for (int i = 0; i < operations.size(); i++) {
        if (s == operations[i])
            return true;
    }
    return false;
}

/* Convert a string to double.*/
double Calculator::stringToDouble(string s) {
    double d = 0;
    int fractionCoef = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != '.') {
            d *= 10;
            d += s[i] - '0';
            fractionCoef *= 10;
        } else {
            fractionCoef = 1;
        }
    }
    if (fractionCoef) {
        d /= fractionCoef;
    }
    return d;
}

/* Define a behaviour of functions and operations according to its priority*/
void Calculator::addActionInOrder(string action, stack<string> &mathActions, vector<string> &nextActions) {
    if (mathActions.empty()) {
        mathActions.push(action);
    } else {
        if (!getActionPriority(action)) {
            while (getActionPriority(mathActions.top()) != 100) {
                string s = mathActions.top();
                mathActions.pop();
                nextActions.push_back(s);
            }
            mathActions.pop();
        } else {
            while (mathActions.size() > 0 && getActionPriority(action) <= getActionPriority(mathActions.top())) {
                if (getActionPriority(mathActions.top()) == 100) {
                        break;
            }

                string s = mathActions.top();
                mathActions.pop();
                nextActions.push_back(s);
            }
            mathActions.push(action);
        }
    }
}


int Calculator::getActionPriority(string action) {
    map <string, int> actionPriority;
    actionPriority["("] = 100;
    actionPriority[")"] = 0;
    actionPriority["+"] = 1;
    actionPriority["-"] = 1;
    actionPriority["*"] = 2;
    actionPriority["/"] = 2;
    actionPriority["sin"] = 3;
    actionPriority["cos"] = 3;
    actionPriority["tg"] = 3;
    return actionPriority[action];

}

void Calculator::setVariable(string var, double value) {
    variables[var] = value;
}

/* Logic of math operations*/
void Calculator::estimateOneOperation(string &action, stack<double> &digits) {
    double d2 = digits.top();
    digits.pop();
    double d1 = digits.top();
    digits.pop();
    double d3 = 0;

    if (action == "+") {
        d3 = d1 + d2;
        digits.push(d3);

    } else if (action == "-") {
        d3 = d1 - d2;
        digits.push(d3);

    } else if (action == "/") {
        d3 = d1 + d2;
        digits.push(d3);

    } else if (action == "*") {
        d3 = d1 * d2;
        digits.push(d3);
    }

}

/* Logic of math functions*/
void Calculator::estimateOneFunction(string &action, stack<double> &digits) {
    double d1 = digits.top();
    digits.pop();
    double d2 = 0;
    if (action == "sin") {
        d2 = sin (d1 * PI / 180);
        digits.push(d2);

    } else if (action == "cos") {
        d2 = cos (d1 * PI / 180);
        digits.push(d2);

    } else if (action == "tg") {
        d2 = tan (d2 * PI / 180);
        digits.push(d2);
    }

}


