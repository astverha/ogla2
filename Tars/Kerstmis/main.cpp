#include <iostream>
#include <fstream>
#include <streambuf>

#include "suffixboom17.h"


using namespace std;

int main() {

    std::ifstream t("file.txt");
    std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

    Sboom boomken;
    boomken.voegtoe(str, '#');

}