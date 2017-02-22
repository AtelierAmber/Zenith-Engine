#include "Tester.h"

int main(int argc, char** argss) {
    Tester tester;
    if (tester.begin() != 0) {
        return -1;
    }
    tester.end();
    return 0;
}