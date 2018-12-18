#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> men = {
	{2,1,0,3,4},
	{3,4,2,1,0},
	{4,2,1,3,0},
	{2,1,0,4,3},
	{3,2,1,4,0}
};

vector<vector<int>> women = {
		{ 0,3,4,2,1 },
		{ 4,2,1,3,0 },
		{ 0,1,2,3,4 },
		{ 4,3,2,1,0 },
		{ 4,2,3,1,0 },
};

vector<vector<int>> women_men_indexed(women.size(), vector<int>(men.size())); // women_men_indexed[woman][man] = "index van man in women tabel"
vector<vector<int>> men_women_indexed(men.size(), vector<int>(women.size())); 

vector<int> partner_of_men(men.size(), -1);		// partner_of_men[man] = "huidige bruid"
vector<int> partner_of_women(women.size(), -1);	// partner_of_women[woman] = "huidige bruidegom"



void doeAanzoek(int i){
	int potential_bride = partner_of_men[i] == -1 ? men[i][0] : men[i][men_women_indexed[i][partner_of_men[i]]+1] ; 
		cout << i << " doet aanzoek aan "  << potential_bride << endl;
		// Als deze vrouw beschikbaar was dan passen we de partnertabellen aan en gaan we naar de volgende vrije man
		if (partner_of_women[potential_bride] == -1)
		{
			partner_of_women[potential_bride] = i;
			partner_of_men[i] = potential_bride;
		}
		else
		{
				// Anders wanneer de vrouw liever bij haar huidige man blijft bepalen we de volgende potent��le bruid
				if(women_men_indexed[potential_bride][partner_of_women[potential_bride]] < women_men_indexed[potential_bride][i])
				{
					partner_of_men[i]= potential_bride;
					doeAanzoek(i);
				}
				// Dit is het geval waar de vrouw al een partner had meer liever met "man" zou samen zijn
				else
				{
					int freeMan = partner_of_women[potential_bride];
				
					partner_of_women[potential_bride] = i;
					partner_of_men[i] = potential_bride;
					
					doeAanzoek(freeMan);
				}
		}
}


int main(){

for(int i = 0 ; i < women.size(); i++)
{
	for(int j = 0 ; j < men.size(); j++)
	{
		women_men_indexed[i][women[i][j]]=j;
		men_women_indexed[i][men[i][j]]=j;		
	}
}
	for(int i = 0 ; i < men.size(); i++){
		if(partner_of_men[i] ==-1)
		{
			doeAanzoek(i);
		}
	}
	
	for (unsigned int m = 0; m < men.size(); m++)
		cout << m << "->" << partner_of_men[m] << endl;
}
