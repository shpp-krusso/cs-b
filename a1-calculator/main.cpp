#include <calculator.h>

int main(int argc, char *argv[])
{
    string expression = "";
    Calculator calc;
    cout << "This program will calculate an expression, that you'll have entered in console! " << endl;
    if (argc > 1)
    {
        for (int i = 0; i < argc; i++)
        {
            if (argv[i] == "/c")
            {
                i++;
                expression = argv[i];
            }
            else if (argv[i] == "/v")
            {
                i++;
                string variable = argv[i];
                string var = "";
                var += variable[0];
            }
        }
    }
    else
    {
        char ch;
        while (true)
        {
            cout << "Press" << endl << "1 if you want to calculate expression, or"
                 << endl << "2 if you want to set variables, or" << endl << "q to quit." << endl;
            cin >> ch;

            if(ch == '1')
            {
                cout << "Enter an expression!" << endl;
                cin >> expression;
                cout << "The calculation result of: " << expression << " = " << calc.calculate(expression) << endl << endl;

            }
            else if(ch == '2')
            {
                string variable = "";
                double value = 0;
                cout << "Enter char for variable" << endl;
                cin >> variable;
                cout << "Enter value for variable" << endl;
                cin >> value;
                calc.setVariable(variable,value);
            }
            else if(ch == 'q')
            {
                break;
            }
        }
    }
}
