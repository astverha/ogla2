#include <vector>
#include <iostream>
#include "graaf.h"

using namespace std;


void DFS(int knoop, Graaf<GERICHT>& graaf,vector<bool>& visited, stack<int> &postorderknopen)
{
    visited[knoop] = true;
    const typename Graaf<GERICHT>::Burenlijst& burenLijst=graaf[knoop];
    for(typename Graaf<GERICHT>::Burenlijst::const_iterator it=burenLijst.begin() ; it !=burenLijst.end(); it++)
    {
        if(!visited[it->first])
        {
            DFS(it->first, graaf, visited, postorderknopen);
        }
    }
    postorderknopen.push(knoop);
}

void DFSTweeKeer(int knoop, Graaf<GERICHT>& graaf,vector<bool>& visited)
{
    visited[knoop] = true;
    cout << knoop << " ";
    const typename Graaf<GERICHT>::Burenlijst& burenLijst=graaf[knoop];
    for(typename Graaf<GERICHT>::Burenlijst::const_iterator it=burenLijst.begin() ; it !=burenLijst.end(); it++)
    {
        if(!visited[it->first])
        {
            DFSTweeKeer(it->first, graaf, visited);
        }
    }
}

int main(){
    Graaf<GERICHT> gr(11);
    gr.voegVerbindingToe(0,1);
    gr.voegVerbindingToe(1,2);
    gr.voegVerbindingToe(2,0);
    gr.voegVerbindingToe(1,3);
    gr.voegVerbindingToe(3,4);
    gr.voegVerbindingToe(4,5);
    gr.voegVerbindingToe(5,3);
    gr.voegVerbindingToe(6,5);
    gr.voegVerbindingToe(6,7);
    gr.voegVerbindingToe(7,8);
    gr.voegVerbindingToe(8,9);
    gr.voegVerbindingToe(9,6);
    gr.voegVerbindingToe(9,10);

    gr.teken("origineel.dot");

    vector<bool> visited(gr.aantalKnopen(), false);
    stack<int> postorderknopen;

    //Graaf omdraaien
    Graaf<GERICHT> omggr(11);
    for(int i = 0; i < gr.aantalKnopen(); i++)
    {
        const typename Graaf<GERICHT>::Burenlijst& burenLijst=gr[i];
        for (typename Graaf<GERICHT>::Burenlijst::const_iterator it=burenLijst.begin(); it!=burenLijst.end();it++){
            omggr.voegVerbindingToe(it->first, i);
        }
    }
    omggr.teken("omgekeerd.dot");

    //Postordernummeren van de knopen in de omgekeerde graaf
    for(int i = 0; i < omggr.aantalKnopen(); i++)
    {
        if(!visited[i])
        {
            DFS(i, omggr, visited, postorderknopen);
        }
    }

    //Visited tabel opnieuw instellen op false
    for(int i = 0 ; i < gr.aantalKnopen(); i++)
    {
        visited[i]=false;
    }

    //Samenhangende componenten uitschrijven
    while (!postorderknopen.empty()) {
        int knoop = postorderknopen.top();
        postorderknopen.pop();
        if(!visited[knoop]){
            DFSTweeKeer(knoop, gr, visited);
            cout << endl << endl;
        }
    }
};
