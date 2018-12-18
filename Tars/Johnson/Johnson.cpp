#include <vector>
#include <iostream>
#include <queue>
#include <list>
#include <utility>
#include "graaf.h"

using namespace std;

void geefAlleKortsteAfstanden(GraafMetTakdata<GERICHT,int> graaf)
{

	int nieuweKnoop = graaf.voegKnoopToe();
	
	// Connect extra node to all other nodes with weigth 0
	for(int i = 0 ; i < graaf.aantalKnopen(); i++)
	{
		if ( i != nieuweKnoop)
		{
			graaf.voegVerbindingToe(nieuweKnoop, i , 0);
		}
	}
	
	// Do bellman-ford to find shortest distance from new node to all other nodes 
	vector<int> kortste_afstanden(graaf.aantalKnopen(), INT_MAX);
	kortste_afstanden[nieuweKnoop] = 0;

	queue<int> q;
	q.push(nieuweKnoop);
	//next_iter_q = queue<int>();

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
				// Als deze buur dus de kortste afstand korter heeft gemaakt, zet deze dan op de lijst om te gebruiken bij de volgende iteratie
				q.push(it->first);
			}
		}
	}

	/*
	cout << "knoop\tafstand" <<endl;
	for (int i = 0 ; i < graaf.aantalKnopen() ; i++)
	{
		cout << i << "\t" << kortste_afstanden[i] <<endl;
		
	}
	cout << endl;*/
	
	
	
	// Reweight the edges [newweight = old weight + new weight from node - new weight to node]
	for (int i = 0; i < graaf.aantalKnopen(); i++)
	{
		if (i != nieuweKnoop)
		{
			const typename Graaf<GERICHT>::Burenlijst& burenlijst=graaf[i];
			for (typename Graaf<GERICHT>::Burenlijst::const_iterator it = burenlijst.begin(); it != burenlijst.end(); it++)
			{
				*graaf.geefTakdata(i, it->first) = *graaf.geefTakdata(i, it->first) + kortste_afstanden[i] - kortste_afstanden[it->first];
			}
		}
	}
	
	//graaf.teken("nieuweVerbindingen.dot");


	// Do n times dijkstra because weights are now all positive
	vector<vector<int>> distances_from(graaf.aantalKnopen(), vector<int>(graaf.aantalKnopen()));
	//map<int, map<int, list<int>>> paths;
	
	//distances_from initialiseren
	for (int i = 0; i < graaf.aantalKnopen(); i++)
	{
		if (i != nieuweKnoop){
			for (int j = 0; j < graaf.aantalKnopen(); j++)
			{
				if (j != nieuweKnoop){
					distances_from[i][j] = (i == j) ? 0 : INT_MAX;
					//if (i == j) paths[i][j] = list<int>(1, i);	
				}
			}	
		}
	}
	
	//In deze for-loop de negatieve, korste afstanden bepalen -> met nog een tweede vector<vector>> werken die enkel die afstanden bijhoudt.
	for (int i = 0; i < graaf.aantalKnopen(); i++)
	{
		if (i != nieuweKnoop)
		{
			auto cmp = [](pair<int,int> left, pair<int,int> right) { return (left.second) > (right.second); };
			priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> q(cmp);
		
		q.push(make_pair(i,distances_from[i][i]));

		while (!q.empty())
		{
			pair<int,int> huidig = q.top();
			q.pop();

			const typename Graaf<GERICHT>::Burenlijst& burenlijst=graaf[huidig.first];
			for (typename Graaf<GERICHT>::Burenlijst::const_iterator it = burenlijst.begin(); it != burenlijst.end(); it++)
			{
				if (*graaf.geefTakdata(huidig.first, it->first) + distances_from[i][huidig.first] < distances_from[i][it->first])
				{
					distances_from[i][it->first] = *graaf.geefTakdata(huidig.first, it->first) + distances_from[i][huidig.first];
					//paths[i][it->first] = paths[i][huidig.first];
					//paths[i][it->first].push_back(it->first);
					
					q.push(make_pair(it->first, distances_from[i][it->first]));
				}
			}
		}
		}
	}
	
	cout << endl<< "ALLE AFSTANDEN:" << endl;
		// Start-iterator
		for (int i = 0 ; i < graaf.aantalKnopen(); i++)
		{
			if (i != nieuweKnoop)
			{
			
			cout << "Van " << i << endl;

			// Naar-iterator
			
				for(int j = 0; j < graaf.aantalKnopen(); j++)
				{
					if (j != nieuweKnoop && i != j && distances_from[i][j] != INT_MAX){
					cout << "\tNaar " << j << ": ";
					cout << "[" << distances_from[i][j]- kortste_afstanden[i] + kortste_afstanden[j]<< "]";
					cout << endl;					
				}	
				}
			}
		}	
		cout << endl << endl;
}

int main(){
	GraafMetTakdata<GERICHT, int> g(6);
	g.voegVerbindingToe(0,1,-2);
	g.voegVerbindingToe(1,2,-1);
	g.voegVerbindingToe(2,3,-3);
	g.voegVerbindingToe(4,3,-4);
	g.voegVerbindingToe(4,5,1);
	g.voegVerbindingToe(2,5,2);
	g.voegVerbindingToe(2,0,4);

	geefAlleKortsteAfstanden(g);
}
