#include "bitpatroon.h"
#include <queue>

using namespace std;

typedef unsigned int uint;
typedef unsigned char uchar;

class Shiftand{
public:
    //naaldlengte moet kleiner zijn dan patroonlengte, anders wordt een exceptie opgegooid.
    Shiftand(const uchar* naald, uint _naaldlengte);

    void zoek(queue<const uchar*>& plaats, const uchar* hooiberg, uint hooiberglengte);

    Bitpatroon letterpatroon[256];
    uint naaldlengte;
};

Shiftand::Shiftand(const uchar *naald, uint _naaldlengte) {

    for(int c=0; c<_naaldlengte; c++){
        this->letterpatroon[naald[c]] = 0;
    }

    for(int i=0; i<_naaldlengte; i++){
        this->letterpatroon[naald[i]] = this->letterpatroon[naald[i]] | (1 << i);
    }

    this->naaldlengte = _naaldlengte;
}

void Shiftand::zoek(queue<const uchar*>& plaats, const uchar* hooiberg, uint hooiberglengte){

    Bitpatroon vorige(0);
    int matcher = 1 << (this->naaldlengte-1);

    for(int j=0; j<hooiberglengte; j++){
        vorige = (this->letterpatroon[hooiberg[j]] | 0) & (vorige.shiftrechts(1) | 1);
        if(vorige.en(matcher)){
            plaats.push(&hooiberg[j - this->naaldlengte + 1]);
        }
    }
}