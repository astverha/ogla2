#include "knuthmorrispratt.h"
#include <iostream>

using namespace std;

int main(){
	KnuthMorrisPratt kmp((unsigned char*)"ABCDABD", 7);
	cout << kmp.kmptabel.size() << endl;
	for(int i=0; i<kmp.kmptabel.size(); i++){
		cout << kmp.kmptabel[i] << " ";
	}
}
