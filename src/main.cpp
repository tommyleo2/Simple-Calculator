#include <iostream>
#include <string>
#include "Calculator.h"

using namespace std;

int main(void) {
    Calculator cal;
    string exp;
    cout << "----------Simple calculator----------" << endl
         << "press Ctrl + D to exit" << endl << endl;
    cout << "> ";
    while (getline(cin, exp)) {
        if (exp == "") {
            cout << "> ";
            continue;
        }
        try {
            cout << endl << cal.calculate(exp) << endl << endl;
        } catch (exception &e) {
            cout << endl << e.what() << endl;
        }
        cout << "> ";
    }
    cout << endl;
    return 0;
}
