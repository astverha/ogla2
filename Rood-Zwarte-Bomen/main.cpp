#include <iostream>
#include "rzwboom14.h"

int main() {
    vector<int> sleutels = {10, 3, 15, 2, 6, 12, 18, 4, 8, 11, 13, 16, 20};
    vector<int> rodeSleutels = {15, 4, 8};

    RZWboom boom(sleutels, rodeSleutels);
    string filename = "boom.dot";
    boom.tekenAlsBinaireBoom(filename.c_str());

    std::cout << (boom.repOK() ? "juiste boom" : "") << std::endl;



    return 0;
}