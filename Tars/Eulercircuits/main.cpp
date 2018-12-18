#include <iostream>
#include <vector>
#include <list>
#include "graaf.h"
using namespace std;

vector<typename Graaf<ONGERICHT>::Burenlijst::const_iterator> vrijeVerbindingen;
list<int> oplossing;
vector<bool> ReedsGevolgd;
bool positiefGezet = 0;


void zoekCircuitRec(int knoop, Graaf<ONGERICHT>& graaf, vector<typename Graaf<ONGERICHT>::Burenlijst::const_iterator>& vrijeVerbindingen, list<int>& oplossing, vector<bool>& ReedsGevolgd, list<int>::iterator& it)
{
	ReedsGevolgd[graaf.verbindingsnummer(knoop, vrijeVerbindingen[knoop]->first)] = true;
	it++;
	int next = vrijeVerbindingen[knoop]->first;
	vrijeVerbindingen[knoop]++;
	it = oplossing.insert(it, next);
	const typename Graaf<GERICHT>::Burenlijst& burenlijst=graaf[next];
	while(vrijeVerbindingen[next] != burenlijst.end() && ReedsGevolgd[graaf.verbindingsnummer(next, vrijeVerbindingen[next]->first)])
	{
		vrijeVerbindingen[next]++;
	}
	if(vrijeVerbindingen[next] != burenlijst.end())
	{
		zoekCircuitRec(next, graaf, vrijeVerbindingen, oplossing, ReedsGevolgd, it);
	}
}

int main()
{
	Graaf<ONGERICHT> gr(10);
	gr.voegVerbindingToe(0,1);
	gr.voegVerbindingToe(1,2);
	gr.voegVerbindingToe(2,3);
	gr.voegVerbindingToe(3,4);
	gr.voegVerbindingToe(4,5);
	gr.voegVerbindingToe(5,6);
	gr.voegVerbindingToe(6,7);
	gr.voegVerbindingToe(7,4);
	gr.voegVerbindingToe(4,1);
	gr.voegVerbindingToe(1,8);
	gr.voegVerbindingToe(8,9);
	gr.voegVerbindingToe(9,0);


	for(int i = 0; i < gr.aantalKnopen() ; i++)
	{
		const typename Graaf<ONGERICHT>::Burenlijst& burenlijst=gr[i];
		vrijeVerbindingen.push_back(burenlijst.begin());
	}

	for(int i = 0; i < gr.aantalVerbindingen() ; i++)
	{
		ReedsGevolgd.push_back(false);
	}

	list<int>::iterator it = oplossing.begin();
	it = oplossing.insert(it,0);

	zoekCircuitRec(0, gr, vrijeVerbindingen, oplossing, ReedsGevolgd, it);

	it = oplossing.begin();
	while(it != oplossing.end())
	{
		const typename Graaf<ONGERICHT>::Burenlijst& burenlijst=gr[*it];
		while(vrijeVerbindingen[*it] != burenlijst.end() && ReedsGevolgd[gr.verbindingsnummer(*it, vrijeVerbindingen[*it]->first)])
		{
			vrijeVerbindingen[*it]++;
		}
		if(vrijeVerbindingen[*it] != burenlijst.end())
		{
			list<int>::iterator resetit = it;
			zoekCircuitRec(*it, gr, vrijeVerbindingen, oplossing, ReedsGevolgd,  it);
			it = resetit;
		}
			it++;
	}

	cout << "Oplossing: " << endl;
	for(auto v : oplossing){
		cout << v << endl;
	}
}