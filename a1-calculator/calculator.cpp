#include "calculator.h"
#include <algorithm>

Calculator::Calculator() {
    opers = {"*", "/", "-", "+", "(", ")"};
    functions = {"sin", "cos", "tg"};
    actionPriority["("] = 4;
    actionPriority[")"] = 0;
    actionPriority["+"] = 1;
    actionPriority["-"] = 1;
    actionPriority["*"] = 2;
    actionPriority["/"] = 2;
    actionPriority["sin"] = 3;
    actionPriority["cos"] = 3;
    actionPriority["tg"] = 3;
}


/* @param - string expr a math expression.
* Returns a result of calculation current expression*/
double Calculator::calculate(string expr) {
    stack<string> mathActions;
    stack<double> digits;
    vector<string> nextActions;
    string buffer = "";
    for (int i = 0; i < expr.size(); i++) {
        fillVectorNextActions(expr, i, mathActions, digits, nextActions, buffer);
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

/* If operations of functions will have pressed out of the stack, they will have added to a vector nextActions*/
void Calculator::fillVectorNextActions(string &expr, int currentPosition, stack<string> &mathActions, stack<double> &digits, vector <string> &nextActions, string &buffer) {
    if (isFunction(buffer)) {
        addActionInOrder(buffer, mathActions, nextActions);
        buffer = "";
    }
    string s = "";
    s += expr[currentPosition];
    if (isdigit(expr[currentPosition])) {
        if (buffer != "") {
            if (isVariable(buffer)) {
                digits.push(variables[buffer]);
                buffer = "";
            }

        }
        buffer += expr[currentPosition];
        if (!isdigit(expr[currentPosition + 1]) && expr[currentPosition + 1] != '.') {
            size_t numOfPoints = count(buffer.begin(), buffer.end(), '.');
            if (numOfPoints > 1) {
                size_t posOfSecPoint = buffer.find(".", buffer.find('.') + 1);
                buffer = buffer.substr(0, posOfSecPoint);
                cout << buffer << " buffer" << endl;
            }
            digits.push(stod(buffer));
            buffer = "";
        }
    } else if (isOper(s)) {
        if (isVariable(buffer)) {
            digits.push(variables[buffer]);
            buffer = "";
        }
        if (buffer != "") {
            buffer = "";
        }
        buffer += expr[currentPosition];
        addActionInOrder(buffer, mathActions, nextActions);
        buffer = "";
    } else {
        buffer += expr[currentPosition];
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


/* Return true if parameter is a function, that is define in calculator.*/
bool Calculator::isFunction(string s) {
    for (int i = 0; i < functions.size(); i++) {
        if (s == functions[i])
            return true;
    }
    return false;
}

/* Return true if paramater is an operator*/
bool Calculator::isOper(string &s) {
    return (find(opers.begin(), opers.end(), s) != opers.end());
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
            while (mathActions.top() != "(") {
                string s = mathActions.top();
                mathActions.pop();
                nextActions.push_back(s);
            }
            mathActions.pop();
        } else {
            while (mathActions.size() > 0 && getActionPriority(action) <= getActionPriority(mathActions.top())) {
                if (mathActions.top() == "(") {
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


