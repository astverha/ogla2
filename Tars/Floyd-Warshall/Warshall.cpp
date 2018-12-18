#include "graaf.h"
#include <vector>
#include <iostream>

using namespace std;
void Warshall(Graaf<GERICHT> g)
{
	vector<vector<bool>> oplossing(g.aantalKnopen(), vector<bool>(g.aantalKnopen()));
	
	for(int i = 0; i < g.aantalKnopen(); i++)
	{
		for(int j = 0; j < g.aantalKnopen(); j++)
		{
			if(i == j || g.verbindingsnummer(i,j) != -1)
			{
				oplossing[i][j] = true;
			}
			else{
				oplossing[i][j]=false;
			}
		}
	}
	
	for(int k = 0; k < g.aantalKnopen(); k++)
	{
		for(int i = 0 ; i < g.aantalKnopen(); i++)
		{
			for(int j = 0 ; j < g.aantalKnopen() ; j++)
			{
				oplossing[i][j] = oplossing[i][j] || (oplossing[i][k] && oplossing[k][j]);
			}
		}
	}
	
	for(int i = 0; i < g.aantalKnopen(); i++)
	{
		for(int j = 0 ; j < g.aantalKnopen(); j++)
		{
			cout << oplossing[i][j] << "\t";
		}
		cout << endl;
	}
}

int main()
{
	Graaf<GERICHT> g(4);
	g.voegVerbindingToe(0,2);
	g.voegVerbindingToe(1,0);
	g.voegVerbindingToe(1,3);
	g.voegVerbindingToe(3,1);
	
	Warshall(g);	
}
