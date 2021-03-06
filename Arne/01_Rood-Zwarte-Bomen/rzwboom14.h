#ifndef __RZWboom_H
#define __RZWboom_H
#include <cstdlib>
#include <iostream>
#include <queue>
#include <memory>
#include <functional>
#include <fstream>
#include <sstream>
#include <vector>


using std::ostream;
using std::ofstream;
using std::ifstream;
using std::ostringstream;
using std::unique_ptr;
using std::cerr;
using std::cout;
using std::pair;
using std::string;

using namespace std;
/**********************************************************************

   Class: RZWboom
   
   beschrijving: Binaire RZWboom waarin geen duplicaatsleutels zijn toegestaan.

   1. Testomgeving opstellen
   2. Hoe kan ik bomen in mijn programma krijgen? + implementeren
        De structuur van de boom hangt volledig af vam de toevoegvolgorde
        Geef de knopen in vorgorde mee
        Rode en zwarte knopen in een aparte lijst
        bvb: {10,5,0,15,20}Z
             {15,20}


   3. repOK implementeren en testen aan de hand van voorbeeldjes
        repOk geeft aan of de RZ-boom in orde is
   4. voegToe implementeren
   5. voegToe testen
   
***************************************************************************/
enum RZWkleur {rood,zwart};

template <class Sleutel>
class RZWknoop;

template <class Sleutel>
class RZWboom : public unique_ptr<RZWknoop<Sleutel>>{
//....
public:
    using unique_ptr<RZWknoop<Sleutel>>::unique_ptr;

    RZWboom(const vector<Sleutel>& sleutels, const vector<Sleutel>& rodeSleutels);
    bool repOk() const;

    RZWboom(unique_ptr<RZWknoop<Sleutel>>&& a);
    void roteer(bool naarlinks);
    void inorder(std::function<void(const RZWknoop<Sleutel>&)> bezoek) const;
    //schrijf als tekst
    void schrijf(ostream& os) const;
    //tekenfuncties
    void tekenAls234Boom(const char * bestandsnaam) const;
    string tekenrec234(ostream& uit,int&nullteller, int&knoop34teller) const;
    void tekenAlsBinaireBoom(const char * bestandsnaam) const;
    string tekenrecBinair(ostream& uit,int&nullteller) const;
    bool repOKZoekboom() const;
    bool repOK() const;
    int geefDiepte() const;
    RZWkleur geefKleur() const;


void zetKleur(RZWkleur kl);
//noot: volgende functie mag alleen opgeroepen worden bij hoofdboom, niet bij deelboom!

void voegtoe(const Sleutel& sleutel);

protected:
//zoekfunctie zoekt sleutel en geeft de boom in waaronder de sleutel zit (eventueel een lege boom als de sleutel
//ontbreekt) en de pointer naar de ouder (als die bestaat, anders nulpointer).
//noot: alhoewel de functie niets verandert aan de boom is ze geen const functie,
//      omdat ze een niet-const pointer naar het inwendige van de boom teruggeeft.
    void zoek(const Sleutel& sleutel, RZWknoop<Sleutel>*& ouder, RZWboom<Sleutel>*& plaats);
};
template <class Sleutel>
RZWboom<Sleutel>::RZWboom(unique_ptr<RZWknoop<Sleutel >>&& a):unique_ptr<RZWknoop<Sleutel>>(move(a)){}



template <class Sleutel>
void RZWboom<Sleutel>::inorder(std::function<void(const RZWknoop<Sleutel>&)> bezoek) const{
    if (*this){
        (*this)->links.inorder(bezoek);
        bezoek(**this);
        (*this)->rechts.inorder(bezoek);
    };
}

template <class Sleutel>
void RZWboom<Sleutel>::schrijf(ostream& os) const{
    inorder([&os](const RZWknoop<Sleutel>& knoop){
        os<<"("<<knoop.sleutel<<") - "<<knoop.kleur;
        os<<"\n  Linkerkind: ";
        if (knoop.links)
            os<<knoop.links->sleutel;
        else
            os<<"-----";
        os<<"\n  Rechterkind: ";
        if (knoop.rechts)
            os<<knoop.rechts->sleutel;
        else
            os<<"-----";
        os<<"\n";
    });
}

template <class Sleutel>
void RZWboom<Sleutel>::tekenAls234Boom(const char * bestandsnaam) const{
    ofstream uit(bestandsnaam);
    assert(uit);
    int nullteller=0;//nullknopen moeten een eigen nummer krijgen.
    int knoop34teller=0;//3-knopen en 4-knopen worden ook genummerd
    uit<<"digraph {\n";
    this->tekenrec234(uit,nullteller,knoop34teller);
    uit<<"}";
}

template <class Sleutel>
string RZWboom<Sleutel>::tekenrec234(ostream& uit,int&nullteller ,int&knoop34teller ) const{
    ostringstream wortelstring;
    if (!*this){
        wortelstring<<"null"<<++nullteller;
        uit<<wortelstring.str()<<" [shape=point];\n";
    }
    else{
        wortelstring<<'"'<<(*this)->sleutel<<'"';
        uit<<wortelstring.str()<<"[label=\""<<(*this)->sleutel<<"\"]";
        if (this->geefKleur()==rood)
            uit<<"[color=red]";
        uit<<";\n";
        string linkskind=(*this)->links.tekenrec234(uit,nullteller,knoop34teller);;
        string rechtskind=(*this)->rechts.tekenrec234(uit,nullteller,knoop34teller);;
        if ((*this)->links.geefKleur()==rood ||
            (*this)->rechts.geefKleur()==rood){
            uit<<"subgraph cluster_"<<++knoop34teller<<" {\n   { rank=\"same\"; ";
            if ((*this)->links.geefKleur()==rood)
                uit<<linkskind<<" , ";
            if ((*this)->rechts.geefKleur()==rood)
                uit<<rechtskind<<" , ";
            uit<<wortelstring.str()<<"}\n";
            if ((*this)->links.geefKleur()==rood)
                uit<<"   "<<linkskind<<" ->"<<wortelstring.str()<<"[dir=back];\n";
            if ((*this)->rechts.geefKleur()==rood)
                uit<<"   "<<wortelstring.str()<<" -> "<<rechtskind<<";\n";
            uit<<"color=white\n}\n";
        };
        if ((*this)->links.geefKleur()==zwart)
            uit<<wortelstring.str()<<" -> "<<linkskind<<";\n";
        if ((*this)->rechts.geefKleur()==zwart)
            uit<<wortelstring.str()<<" -> "<<rechtskind<<";\n";
    };
    return wortelstring.str();
}

template <class Sleutel>
void RZWboom<Sleutel>::tekenAlsBinaireBoom(const char * bestandsnaam) const{
    ofstream uit(bestandsnaam);
    assert(uit);
    int nullteller=0;//nullknopen moeten een eigen nummer krijgen.
    uit<<"digraph {\n";
    this->tekenrecBinair(uit,nullteller);
    uit<<"}";
}

template <class Sleutel>
string RZWboom<Sleutel>::tekenrecBinair(ostream& uit,int&nullteller ) const{
    ostringstream wortelstring;
    if (!*this){
        wortelstring<<"null"<<++nullteller;
        uit<<wortelstring.str()<<" [shape=point];\n";
    }
    else{
        wortelstring<<'"'<<(*this)->sleutel<<'"';
        uit<<wortelstring.str()<<"[label=\""<<(*this)->sleutel<<"\"]";
        if (this->geefKleur()==rood)
            uit<<"[color=red]";
        uit<<";\n";
        string linkskind=(*this)->links.tekenrecBinair(uit,nullteller);
        string rechtskind=(*this)->rechts.tekenrecBinair(uit,nullteller);
        uit<<wortelstring.str()<<" -> "<<linkskind<<";\n";
        uit<<wortelstring.str()<<" -> "<<rechtskind<<";\n";
    };
    return wortelstring.str();
}

template <class Sleutel>
bool RZWboom<Sleutel>::repOKZoekboom() const{
    Sleutel* vorige=0;//houdt ref naar eerder gezien sleutel bij.
    bool oke=true;
    inorder([&vorige,&oke](const RZWknoop<Sleutel>& knoop){
        if (vorige && knoop.sleutel < *vorige){
            throw "Verkeerde volgorde\n";
        };
        if (knoop.ouder && knoop.ouder->links.get()!=&knoop &&  knoop.ouder->rechts.get()!=&knoop){
            std::ostringstream fout;
            fout<<"Ongeldige ouderpointer bij knoop "<<knoop.sleutel<<"\n";
            fout<<"wijst naar "<<knoop.ouder->sleutel<<"\n";
            throw fout;
            return;
        };
        //...nog tests?
        return;
    });
    return oke;
}

template <class Sleutel>
RZWkleur RZWboom<Sleutel>::geefKleur() const{
    return (*this)->kleur;
}

template <class Sleutel>
bool RZWboom<Sleutel>::repOK() const{
    Sleutel* vorige=0;//houdt ref naar eerder gezien sleutel bij.
    bool oke=true;
    inorder([&vorige,&oke](const RZWknoop<Sleutel>& knoop){
        if (vorige && knoop.sleutel < *vorige){
            throw "Verkeerde volgorde\n";
        }
        if (knoop.ouder && knoop.ouder->links.get()!=&knoop &&  knoop.ouder->rechts.get()!=&knoop){
            std::ostringstream fout;
            fout<<"Ongeldige ouderpointer bij knoop "<<knoop.sleutel<<"\n";
            fout<<"wijst naar "<<knoop.ouder->sleutel<<"\n";
            throw fout;
            return;
        }
        if (knoop.links && knoop.kleur == rood && knoop.links->kleur == rood) {
            std::ostringstream fout;
            fout<<"2 rode knopen na elkaar bij knoop "<<knoop.sleutel<<"\n";
            fout<<" en "<<knoop.links->sleutel<<"\n";
            throw fout;
        }
        if (knoop.rechts && knoop.kleur == rood && knoop.rechts->kleur == rood) {
            std::ostringstream fout;
            fout<<"2 rode knopen na elkaar bij knoop "<<knoop.sleutel<<"\n";
            fout<<" en "<<knoop.rechts->sleutel<<"\n";
            throw fout;
        }
        //...nog tests?
        return;
    });
    return oke;
}

template <class Sleutel>
int RZWboom<Sleutel>::geefDiepte() const{
    if (*this)
        return 1+std::max((*this)->links.geefDiepte(),(*this)->rechts.geefDiepte());
    else
        return 0;
}

template <class Sleutel>
class RZWknoop {
    friend class RZWboom<Sleutel>;
    public:
        RZWknoop():ouder(0){}
        RZWknoop(const Sleutel& sl):sleutel{sl},ouder(0),kleur(rood){};
        RZWknoop(Sleutel&& sl):sleutel{move(sl)},ouder(0),kleur(rood){};
        RZWboom<Sleutel>& geefKind(bool links);
        Sleutel sleutel;
        RZWknoop<Sleutel>* ouder;
        RZWboom<Sleutel> links,rechts;
        RZWkleur kleur;
};

template <class Sleutel>
void RZWboom<Sleutel>::zoek(const Sleutel& sleutel, RZWknoop<Sleutel>*& ouder, RZWboom<Sleutel>*& plaats){
    plaats=this;
    ouder=0;
    while (*plaats && (*plaats)->sleutel !=sleutel){
        ouder=plaats->get();
        plaats=&((*plaats)->geefKind(((*plaats)->sleutel > sleutel)));
    };
};

template <class Sleutel>
RZWboom<Sleutel>& RZWknoop<Sleutel>:: geefKind(bool linkerkind){
    if (linkerkind)
        return links;
    else
        return rechts;
};

//preconditie: wortel en nodige kind bestaan
template <class Sleutel>
void RZWboom<Sleutel>::roteer(bool naarLinks){
    RZWboom<Sleutel> kind=move((*this)->geefKind(!naarLinks));
    //beta verhangen
    (*this)->geefKind(!naarLinks)=move(kind->geefKind(naarLinks));
    //wortel verhangen
    kind->geefKind(naarLinks)=move(*this);
    //kind verhangen
    *this=move(kind);
    //ouderpointers goed zetten
    (*this)->ouder=(*this)->geefKind(naarLinks)->ouder;
    (*this)->geefKind(naarLinks)->ouder=this->get();
    if ((*this)->geefKind(naarLinks)->geefKind(!naarLinks))//alpha niet leeg
        (*this)->geefKind(naarLinks)->geefKind(!naarLinks)->ouder=(*this)->geefKind(naarLinks).get();
}


void print(vector<string> &v){
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << endl;
}



template<class Sleutel>
RZWboom<Sleutel>::RZWboom(const vector<Sleutel>& sleutels, const vector<Sleutel>& rodeSleutels) {
    // sleutels bevat alles sleutels in level order
    // rodeSleutels bevat alle rode sleutels in level order

    //root maken
    (*this) = move(make_unique<RZWknoop<Sleutel> >(sleutels[0]));
    (*this)->kleur = zwart;

    int j = 0;
    for (int i = 1; i < sleutels.size(); ++i) {
        RZWkleur kleur = zwart;
        if(sleutels[i] == rodeSleutels[j]){
            kleur = rood;
            j++;
        }

        RZWknoop<Sleutel>* ouder;
        RZWboom<Sleutel>* plaats;
        this->zoek(sleutels[i], ouder, plaats);


        //Eigenlijk moet je niet checken voor links of rechts
        if(sleutels[i] > ouder->sleutel){
            ouder->rechts = (make_unique<RZWknoop<Sleutel> >(sleutels[i]));
            ouder->rechts->kleur = kleur;
        } else {
            ouder->links = (make_unique<RZWknoop<Sleutel> >(sleutels[i]));
            ouder->links->kleur = kleur;
        }
    }

    this->schrijf(cout);
};




#endif
