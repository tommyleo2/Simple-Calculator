#include <iostream>
#include "lexical_analyzer.h"

using namespace std;

int main(void) {
    Lexical lex("123 + 22 \t + \t 12312 asd + 12d");
    float token = 0;
    try {
        Type t = lex.getToken(&token);
        while (t != END) {
            if (t == CHAR) {
                cout << *(char *)&token << endl;
            }
            else if (t == FLOAT) {
                cout << token << endl;
            }
            t = lex.getToken(&token);
        }
    } catch (UnrecognizedTokenException e) {
        cout << e.what();
    }
    return 0;
}
