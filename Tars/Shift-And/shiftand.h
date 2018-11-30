#include "bitpatroon.h"
#include <queue>
typedef unsigned int uint;
typedef unsigned char uchar;
class Shiftand{
public:
//naaldlengte moet kleiner dan patroonlengte zijn,
//anders wordt een exceptie opgegooid.
    Shiftand(const uchar* naald,uint _naaldlengte);
    void zoek(std::queue<const uchar*>& plaats,
                     const uchar* hooiberg, uint hooiberglengte);
private:
    Bitpatroon letterpatroon[256];
    uint naaldlengte;
};
    
Shiftand::Shiftand(const uchar* naald, uint _naaldlengte){
    naaldlengte = _naaldlengte;

    for (uint i = 0; i < 256; i++)
    {
        Bitpatroon b;
        letterpatroon[i] = b;
    }

    for (uint i = 0; i < naaldlengte; i++)
    {
        // naald[i] = een individuele letter
        Bitpatroon p = letterpatroon[naald[i]];

        // maak een patroon met een 1 bit op plek i
        Bitpatroon extra = Bitpatroon::eenbit(i);

        // sla voor de letter op naald[i] zijn huidige patroon op, uitgebreid met de extra bit
        // letterpatroon heeft een entry voor het hele alfabet en per entry houden we bij op welke plek
        // in de naald die letter voorkwam
        letterpatroon[naald[i]] = p | extra;
    }
}

void Shiftand::zoek(std::queue<const uchar*>& plaats, const uchar* hooiberg, uint hooiberglengte){
    // sliding window opstellen R
    Bitpatroon vorige(0);
    Bitpatroon huidige;
    // matcher vb: naaldlengte = 3 => matcher: 00100..00 (32 bits in totaal)
    Bitpatroon matcher = Bitpatroon::eenbit(naaldlengte - 1);
    for (uint j = 0; j <= hooiberglengte; j++)
    {
        // SHIFT
        // zorg ervoor dat bit 32 altijd 1 is, zodat een vergelijking in de AND stap
        // de 1 zal houden als het patroon op zijn 'hoogste' positie ook die letter heeft want
        // Y = hooiberg[j] = huidig karakter in de tekst
        // letterpatroon[Y] = sequentie van nullen en eenen die toont op welke plekken in het patroon die letter voorkwam
        huidige = vorige.shiftrechts(1);

        //Bij verschuiven komt er vooraan een 0, maar dat willen we niet, zie cursus p143, er moet vooraan een 1 staan
        huidige = huidige | Bitpatroon::eenbit(0);

        // AND
        huidige = huidige & letterpatroon[hooiberg[j]];

        // CHECK MATCH
        if (huidige.en(matcher))
        {
            // locatie = plek in de hooiberg j - lengte van het zoekwoord, maar die lengte werd ingegeven als string length, dus 1 te veel (0-indexing ...)
            plaats.push(&hooiberg[j - naaldlengte + 1]);
        }
        // zo maken we geheugen, de gematchte bits blijven bewaard, want bij de volgende iteratie wordt er een nieuwe 1 in geshift
        vorige = huidige;
    }
}