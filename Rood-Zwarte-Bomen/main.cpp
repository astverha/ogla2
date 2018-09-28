#include <iostream>
#include "rzwboom14.h"

int main() {

    string file = "rzboom.txt";
    RZWboom<int> boom(file);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}