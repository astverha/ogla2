/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: arneverhaeghe
 *
 * Created on October 5, 2018, 1:59 PM
 */

#include <cstdlib>
#include "bruggen.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

/*
 * We zouden een klasse "deeloplossing" moeten maken en de deeloplossingen bijhouden 
 * zo kunnen we steeds terugkeren naar een vorige oplossing
 */
int main(int argc, char** argv) {

    Moneymaker mm;

    //read file
    ifstream infile("simpelBrug.dat");
    string line;
    int i = -1;
    while (std::getline(infile, line)) {
        istringstream iss(line);
        if(i == -1){
            iss >> mm.n;
            for(int j=0; j<mm.n; j++){
                mm.verbonden.push_back(false);
            }
            i++;
        } else {
            int a, b;
            iss >> a >> b;
            mm.verbindingen.push_back(make_pair(b, a));
            i++;
        }
    }
    
    vector<bool> result = mm.geefBeste();

    for(int i=0; i<mm.n; i++){
        cout << i << ": " << (result[i] ? "true" : "false") << endl;
    }
    
    return 0;
}

