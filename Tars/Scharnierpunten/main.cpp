#include <iostream>
#include <vector>
#include "graaf.h"
using namespace std;

vector<bool> visited(7);
vector<int> parent(7);
vector<int> laagst(7);
vector<int> pre(7);
stack<int> verbindingen;
int num;

void rec_zoek_scharnierpunten(int i, Graaf<ONGERICHT> & graaf){
    //Voor alle knopen bereikbaar vanuit knoop i berekenen we preordernummer en laagst bereikbare knoopnummerslaagst[]
    visited[i] = true;
    pre[i] = num++;

    //Initialisatie: elke knoop bereikt minstens zichzelf
    laagst[i] = pre[i];
    const typename Graaf<GERICHT>::Burenlijst& burenlijst=graaf[i];
    for(typename Graaf<GERICHT>::Burenlijst::const_iterator it=burenlijst.begin() ; it != burenlijst.end(); it++)
    {
        if(!visited[it->first])
        {
            verbindingen.push(it->first);
            parent[it->first]=i;
            rec_zoek_scharnierpunten(it->first, graaf);
            if(laagst[it->first] < laagst[i])
            {
                laagst[i]=laagst[it->first];
            }
            else if(laagst[it->first]>=pre[i])
            {
                if(i != 0)
                {
                    cout << i << " is een scharnierpunt voor " << it->first;
                    while(verbindingen.top() !=  it->first)
                    {
                        cout << "-" << verbindingen.top();
                        verbindingen.pop();
                    }
                    cout << endl;
                }
            }
        }
        else{
            if( it->first != parent[i])
            {
                if(pre[it->first] < laagst[i])
                {
                    laagst[i] = pre[it->first];
                }
            }
        }
    }
}

void zoekScharnierpunten(Graaf<ONGERICHT> &g){
    for(int i =0 ; i<g.aantalKnopen(); i++)
    {
        visited[i] = false;
        parent[i]=-1;
    }

    num = 0; //initialisatie preorderingnummer
    rec_zoek_scharnierpunten(0,g);
}

int main()
{
    Graaf<ONGERICHT> g(7);
    g.voegVerbindingToe(0,1);
    g.voegVerbindingToe(1,2);
    g.voegVerbindingToe(2,0);
    g.voegVerbindingToe(2,3);
    g.voegVerbindingToe(3,4);
    g.voegVerbindingToe(4,2);
    g.voegVerbindingToe(3,5);
    g.voegVerbindingToe(5,6);
    g.voegVerbindingToe(3,6);

    g.teken("Ongericht.dot");

    //Scharnierpunten zoeken die NIET de wortel zijn, efficiÎnt?
    zoekScharnierpunten(g);
    int count = 0;
    for(int i = 1; i <g.aantalKnopen() ; i++){
        if(parent[i] == 0)
        {
            count ++;
        }
    }

    count > 1 ? cout << "De wortel(0) is ook een scharnierpunt " << endl : cout << endl;
}
