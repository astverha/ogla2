#include <vector>
#include <queue>
#include <iostream>
#include "graaf.h"

using namespace std;

void geefKorsteAfstandenVanaf(GraafMetTakdata<GERICHT,int>& graaf,  int van, bool print)
{
    // Doe n-1 keer een diepte eerst zoeken
    const int n = graaf.aantalKnopen();
    cout << "# knopen is " << n << endl;


    // Houd de kortste afstanden bij in een map knoopnr -> int
    vector<int> kortste_afstanden;
    vector<int> voorloper;
    for (int i = 0; i < n; i++)
    {
        kortste_afstanden.push_back(INT_MAX);
        voorloper.push_back(-1);
    }
    kortste_afstanden[van] = 0;
    voorloper[van]=0;
    //queue<int> next_iter_q;
    queue<int> q;
    q.push(van);


    //next_iter_q = queue<int>();
    // Diepte eerst zoeken
    while (!q.empty())
    {
        // Haal volgende knoop op
        int huidig = q.front();
        q.pop();

        // Overloop zijn buren
        const typename Graaf<GERICHT>::Burenlijst& burenlijst=graaf[huidig];
        for (typename Graaf<GERICHT>::Burenlijst::const_iterator it = burenlijst.begin(); it != burenlijst.end(); it++)
        {
            // Als de afstand korter is geworden, pas de waarde dan aan in de map
            if (*graaf.geefTakdata(huidig, it->first) + kortste_afstanden[huidig] < kortste_afstanden[it->first])
            {
                kortste_afstanden[it->first] = *graaf.geefTakdata(huidig, it->first) + kortste_afstanden[huidig];
                voorloper[it->first] = huidig;
                // Als deze buur dus de kortste afstand korter heeft gemaakt, zet deze dan op de lijst om te gebruiken bij de volgende iteratie

                //next_iter_q.push(it->first);
                q.push(it->first);
            }
        }
    }


    if(print) cout << "knoop\tafstand\tvoorloper" <<endl;
    for (int i = 0 ; i < graaf.aantalKnopen() ; i++)
    {
        if(print) cout << i << "\t" << kortste_afstanden[i] << "\t" << voorloper[i] <<endl;

    }
    if (print) cout << endl;
}

int main(){
    GraafMetTakdata<GERICHT, int> g(5);
    g.voegVerbindingToe(0,1,4);
    g.voegVerbindingToe(0,3,8);
    g.voegVerbindingToe(1,2,-3);
    g.voegVerbindingToe(0,2,5);
    g.voegVerbindingToe(2,4,4);
    g.voegVerbindingToe(4,3,1);
    g.voegVerbindingToe(3,4,2);

    geefKorsteAfstandenVanaf(g, 0, true);
}

