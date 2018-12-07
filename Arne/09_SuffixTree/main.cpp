#include <iostream>
#include <fstream>
#include <streambuf>

#include "suffixboom17.h"


using namespace std;

int main() {

    cout << "Hello world!" << endl;

    ifstream t("file.txt");
    string str((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());

    Sboom sboom;
    sboom.voegtoe(str, '#');

}