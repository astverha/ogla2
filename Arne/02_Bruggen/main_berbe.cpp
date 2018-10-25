#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct brug {
  int bedrag;
  int winkelcentrum;
} ;

struct deeloplossing{
	int totaalbedrag;
	int voorloper;
};

int main () {
	vector<brug> gegevens;
	vector<deeloplossing> deeloplossingen;
	int aantal;
	
	//Gegevens inladen en opslaan in vector gegevens
  	ifstream myfile ("versnick.dat");
	if (myfile.is_open())
  	{
  		myfile >> aantal;
  		brug b;
		while ( myfile >> b.bedrag )
		{
			myfile >> b.winkelcentrum;
			gegevens.push_back(b);  //Beter een struct of 2 vectoren 
    	}
    	myfile.close();
  	}
  	
	else cout << "Unable to open file"; 

	//Oplossing construeren
	for(int i = 0; i < aantal ; i++){
		int j = i;
		//We beginnen altijd met deeloplossing = het bouwen van brug i. Hierna controleren we dan of bruggen (<i) ook gebouwd kunnen worden en kijken we naar hun optimale deeloplossing.
		deeloplossing d;
		d.totaalbedrag = gegevens[i].bedrag;
		d.voorloper = i;
		
		//We gaan nu alle bruggen <i af om te zien of ze:
		//1. Geen overlap hebben met onze brug i.
		//2. Een grotere totaalsom opleveren;
		while(j != 0){
			j--;
			if(gegevens[j].winkelcentrum < gegevens[i].winkelcentrum && (deeloplossingen[j].totaalbedrag+gegevens[i].bedrag) > d.totaalbedrag){
				d.totaalbedrag = deeloplossingen[j].totaalbedrag+gegevens[i].bedrag;
				d.voorloper = j;
			}
		}
		deeloplossingen.push_back(d);
	}
	
	//Grooste totaalsom uitschrijven:
	int grootsteIndex = 0;
	for(int i=1; i < aantal; i++){
		if(deeloplossingen[i].totaalbedrag > deeloplossingen[grootsteIndex].totaalbedrag){
			grootsteIndex = i;
		}
	}
	
	cout << "Grootste bedrag: " << deeloplossingen[grootsteIndex].totaalbedrag << endl;
	cout << "Bruggen zullen aan volgende arena's gebouwd worden: " <<endl;
	while (grootsteIndex != deeloplossingen[grootsteIndex].voorloper){
		cout << grootsteIndex << endl;
		grootsteIndex = deeloplossingen[grootsteIndex].voorloper;
	}
	cout << grootsteIndex << endl;
	
  return 0;
}
