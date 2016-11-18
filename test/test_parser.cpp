#include "Parser.h"
#include <iostream>

using namespace std;

int main(int arg, char **argv) {
    Parser parser(argv[1]);
    try {
        cout << parser.parse() << endl;
    } catch (exception &e) {
        cout << e.what() << endl;
    }
    return 0;
}
