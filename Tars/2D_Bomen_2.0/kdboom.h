#ifndef __KDBOOM_H
#define __KDBOOM_H
#include <cstdlib>
#include <iostream>
#include <queue>
#include <memory>
#include <functional>
#include <fstream>
#include <sstream>
#include "punt2.h"

using std::ostream;
using std::ofstream;
using std::ostringstream;
using std::unique_ptr;
using std::cerr;
using std::pair;
using std::string;

using namespace std;

/**********************************************************************

   Class: Boom2D en Knoop2D
   
   beschrijving: 2dboom met punten uit de punt2-klasse
   
***************************************************************************/
class Knoop2D;
class Boom2D : public unique_ptr<Knoop2D>{
//....
    using unique_ptr<Knoop2D>::unique_ptr;
public:
    void inorder(std::function<void(const Knoop2D&)> bezoek) const;
    void schrijf(ostream& os) const;
    void teken(const char * bestandsnaam);
    string tekenrec(ostream& uit,int&nullteller);
    int geefDiepte();
    void voegtoe(const punt2& punt);
    //zoekdichtste geeft geen foutmelding bij een lege boom, maar geeft wel 0 bezochteknopen.
    punt2 zoekdichtste(const punt2&, int& bezochteknopen);
protected:
    Boom2D* zoek(const punt2& punt);
    //preconditie: boom is niet leeg;
    void zoekdichtsteRec(const punt2&zoekpunt,punt2&beste,int& bezochteknopen,int niveau);
};


class Knoop2D {
    friend class Boom2D;
    public:
        Knoop2D();
        Knoop2D(const punt2& pt):punt{pt}{};
        Boom2D& geefKind(bool links);
        punt2 punt;
        Boom2D links, rechts;
};

void Boom2D::schrijf(ostream& os) const{
    inorder([&os](const Knoop2D& knoop){
        os<<"("<<knoop.punt<<")";
        os<<"\n  Linkerkind: ";
        if (knoop.links)
            os<<knoop.links->punt;
        else
            os<<"-----";
        os<<"\n  Rechterkind: ";
        if (knoop.rechts)
            os<<knoop.rechts->punt;
        else
            os<<"-----";
        os<<"\n";
    });
}

void Boom2D::teken(const char * bestandsnaam){
    ofstream uit(bestandsnaam);
    assert(uit);
    int nullteller=0;//nullknopen moeten een eigen nummer krijgen.
    uit<<"digraph {\n";
    this->tekenrec(uit,nullteller);
    uit<<"}";
}

string Boom2D::tekenrec(ostream& uit,int&nullteller ){
    ostringstream wortelstring;
    if (!*this){
        wortelstring<<"null"<<++nullteller;
        uit<<wortelstring.str()<<" [shape=point];\n";
    }
    else{
        wortelstring<<'"'<<(*this)->punt<<'"';
        uit<<wortelstring.str()<<"[label=\""<<(*this)->punt<<"\"]";
        uit<<";\n";
        string linkskind=(*this)->links.tekenrec(uit,nullteller);
        string rechtskind=(*this)->rechts.tekenrec(uit,nullteller);
        uit<<wortelstring.str()<<" -> "<<linkskind<<";\n";
        uit<<wortelstring.str()<<" -> "<<rechtskind<<";\n";
    };
    return wortelstring.str();
}

int Boom2D::geefDiepte(){
    if (*this)
        return 1+std::max((*this)->links.geefDiepte(),(*this)->rechts.geefDiepte());
    else
        return 0;
}

void Boom2D::inorder(std::function<void(const Knoop2D&)> bezoek) const{
    if (*this){
        (*this)->links.inorder(bezoek);
        bezoek(**this);
        (*this)->rechts.inorder(bezoek);
    };
};

Boom2D& Knoop2D:: geefKind(bool linkerkind){
    if (linkerkind)
        return links;
    else
        return rechts;
};

/**
 * MIJN TOEVOEGINGEN, groetjes Arnerd.
 */


void Boom2D::voegtoe(const punt2& punt){

    bool wisselaar = false;

    if (!(*this)){
        (*this) = move(make_unique<Knoop2D>(punt));
    } else {

        //zolang het geen blad is
        while(  ){
            // elke loop de wisselaar veranderen
            wisselaar = !wisselaar;
            if (wisselaar){
                // x
                if (punt.x >= (*this)->punt.x ){
                    //rechts afdalen
                    (*this) = (*this)->rechts;
                } else {
                    (*this) = (*this)->links;
                }
            }
            else {
                // y
                if (punt.y >= (*this)->punt.y ){
                    //rechts afdalen
                    (*this) = (*this)->rechts;
                } else {
                    (*this) = (*this)->links;
                }
            }
        }

        //knoop nu toevoegen

        if (wisselaar){
            // x
            if (punt.x >= (*this)->punt.x ){
                //rechts afdalen
                (*this)->rechts = move(make_unique<Knoop2D>(punt));
            } else {
                (*this)->links = move(make_unique<Knoop2D>(punt));
            }
        }
        else {
            // y
            if (punt.y >= (*this)->punt.y ){
                //rechts afdalen
                (*this)->rechts = move(make_unique<Knoop2D>(punt));
            } else {
                (*this)->links = move(make_unique<Knoop2D>(punt));
            }
        }
    }
}

#endif
