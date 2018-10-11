#include <iostream>
#include "rzwboom14.h"

int main() {
    vector<int> sleutels = {10, 3, 15, 2, 6, 12, 18, 4, 8, 11, 13, 16, 20};
    vector<int> rodeSleutels = {15, 4, 8};
    
    vector<int> sleutels2 = {0, -4, 30, -5, -2, 15, 45, 8, 23, 37, 52, 4, 11, 19, 26, 34, 40, 48, 60, 1, 5, 9, 13, 16, 21, 24, 28, 31, 35, 39, 43, 46, 51, 54, 61};
    vector<int> rodeSleutels2 = {30, 8, 23, 37, 52, 1, 5, 9, 13, 16, 21, 24, 28, 31, 35, 39, 43, 46, 51, 54, 61};

    RZWboom<int> boom(sleutels2, rodeSleutels2);
    string filename = "boom.dot";
    boom.tekenAlsBinaireBoom(filename.c_str());

    std::cout << (boom.repOK() ? "juiste boom" : "") << std::endl;


    return 0;
}