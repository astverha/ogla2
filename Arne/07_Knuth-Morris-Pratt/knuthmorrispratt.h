#include <queue>
#include <vector>
#include <iostream>
typedef unsigned int uint;
typedef unsigned char uchar;

using namespace std;

class KnuthMorrisPratt{

public:
    vector<int> kmptabel;

    KnuthMorrisPratt(const uchar* naald,uint _naaldlengte);

    // Prefixfunctie
    void computeKmpTabel(const uchar* naald, uint _naaldlengte);

    void zoek(queue<const uchar*>& plaats, const uchar* hooiberg, uint hooiberglengte);

};

//Constructor
KnuthMorrisPratt::KnuthMorrisPratt(const uchar* naald,uint _naaldlengte){
    this->kmptabel.resize(_naaldlengte);
    this->computeKmpTabel(naald, _naaldlengte);
}

// Prefixfunctie (als de return value gelijk wordt aan de naaldlengte is het patroon gevonden)
void KnuthMorrisPratt::computeKmpTabel(const uchar* naald, uint _naaldlengte){
    int result;
    this->kmptabel[0] = -1;
    this->kmptabel[1] = 0;
    for(int i=2; i<_naaldlengte; i++){
        int vorig = this->kmptabel[i-1];
        while(vorig > 0 && naald[i-1] != naald[vorig]){
            vorig = this->kmptabel[vorig];
        }
        if(naald[i-1] == naald[vorig]){
            vorig++;
        }
        result = vorig;
        this->kmptabel[i] = result;
    }
}

void KnuthMorrisPratt::zoek(queue<const uchar *> &plaats, const uchar *hooiberg, uint hooiberglengte) {
    if (hooiberg.empty()) {
        plaats =  queue<const uchar*>{};
    }

    // int aantal = 0; // DEBUG
    std::queue<const uchar*> gevonden;
    int prefix_lengte = 0;
    for (size_t i = 1; i <= hooiberg.size(); i++) // Let op de <= in de for-voorwaarde! bv. "aba" zoeken in "ababa"
    {
        while ((prefix_lengte >= 0) && (hooiberg[i - 1] != naald[prefix_lengte]))   {
            prefix_lengte = tabel[prefix_lengte];
            // aantal++; // DEBUG
        }

        prefix_lengte++;

        assert(prefix_lengte <= std::numeric_limits<int>::max());
        if (prefix_lengte == static_cast<int>(naald.size())) {
            gevonden.push(i - naald.size());
            prefix_lengte = tabel[prefix_lengte]; // Is dit nodig? Zie CLRS
        }
    }
    // std::cout << "aantal:" << aantal << std::endl; // DEBUG

    plaats =  gevonden;
}
