/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   bruggen.h
 * Author: arneverhaeghe
 *
 * Created on October 5, 2018, 1:59 PM
 */

#ifndef BRUGGEN_H
#define BRUGGEN_H

#include <vector>
#include <utility>
#include <iostream>

using namespace std;

class Moneymaker {
public:
    int n;
    vector<pair<int, int> > verbindingen; // index is arenanr, pair<winkelnr, bedrag>
    vector<bool> verbonden;

    void deelProbleem(int);
    int berekenHuidigeWaarde();

    vector<bool> geefBeste();

};

void Moneymaker::deelProbleem(int i) {
    cout << "Deelprobleem " << i << endl;
    
    verbonden[i] = true;
    
    int som = 0;
    vector<bool> kruisers(this->n, false);
    for (int j = 0; j < i; j++) {
        cout << verbindingen[i].first << " " << verbindingen[j].first << endl;
        if (verbindingen[i].first < verbindingen[j].first) {
            som += verbindingen[j].second;
            kruisers[j] = true;
            //cout << "\t" << i << " kruist met " << j << endl;
        }
    }

    if (verbindingen[i].second > som) {
        //cout << i << " is een lucratieve verbinding." << endl;
        for (int j = 0; j < i; j++) {
            if (kruisers[j]) {
                verbonden[j] = false;
                cout << "\t" << i << " is beter dan " << j << ". " << j << " wordt verwijderd." << endl;
            }
        }
    }
    
    cout << "---------------------\n\n";
}

int Moneymaker::berekenHuidigeWaarde(){
    int waarde = 0;
    for(int i=0; i<this->n; i++){
        if(verbonden[i]){
            waarde += verbindingen[i].second;
        }
    }
    return waarde;
}

vector<bool> Moneymaker::geefBeste() {
    int best = -1;
    int bestWaarde = -1;
    
    this->verbonden[0] = true;
    
    for (int i = 1; i<this->n; i++) {
        this->deelProbleem(i);
        
        int waarde = this->berekenHuidigeWaarde();
        if(waarde > bestWaarde){
            bestWaarde = waarde;
            best = i;
        }
    }
    
    this->deelProbleem(best);
    return verbonden;
}











#endif /* BRUGGEN_H */

