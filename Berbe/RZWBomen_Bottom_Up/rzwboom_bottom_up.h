#ifndef __RZWboom_H
#define __RZWboom_H
#include <cstdlib>
#include <iostream>
#include <queue>
#include <memory>
#include <functional>
#include <fstream>
#include <sstream>
#include <cassert>
#include <algorithm>

using std::ostream;
using std::ofstream;
using std::ostringstream;
using std::unique_ptr;
using std::cerr;
using std::pair;
using std::string;
/**********************************************************************

   Class: RZWboom
   
   beschrijving: Binaire RZWboom waarin geen duplicaatsleutels zijn toegestaan.
   
***************************************************************************/
enum RZWkleur {rood,zwart};

template <class Sleutel>
class RZWknoop;

template <class Sleutel>
class RZWboom : public unique_ptr<RZWknoop<Sleutel>>{
//....
public:
    using unique_ptr<RZWknoop<Sleutel>>::unique_ptr;
    
    //Self
    RZWboom();
    
    RZWboom(unique_ptr<RZWknoop<Sleutel>>&& a);                                           ;
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
    int geefDiepte() const;
    
    //eigen functies
    RZWboom(const std::vector<Sleutel>& sleutels, const std::vector<Sleutel>& rodeSleutels);
    void herstelBoom(RZWboom<Sleutel> * root);
    void verwijder(const Sleutel& sleutel);
    void herstelBoomNaVerwijderen(RZWboom<Sleutel> * root);
RZWkleur geefKleur() const; //AANMAKEN
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
        os<<"("<<knoop.sleutel<<")";
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
        //std::cout << (*this)->sleutel << " met kleur: " << this->geefKleur() << std::endl;
        if (this->geefKleur() == rood)
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
    Sleutel* vorige;//houdt ref naar eerder gezien sleutel bij.
    bool oke=true;
    inorder([&vorige,&oke](const RZWknoop<Sleutel>& knoop){
        
        // Test of de volgorde klopt
        if (vorige && knoop.sleutel < *vorige){
            //throw "Verkeerde volgorde\n";
            std::cout << "Verkeerde volgorde!\n" << std::endl;
        };
        
        // Test of de kinderen juist zitten
        if (knoop.ouder && knoop.ouder->links.get()!=&knoop &&  knoop.ouder->rechts.get()!=&knoop){
            //std::ostringstream fout;
            //fout<<"Ongeldige ouderpointer bij knoop "<<knoop.sleutel<<"\n";
            //fout<<"wijst naar "<<knoop.ouder->sleutel<<"\n";
            //throw fout;
            std::cout << "Ongeldige ouderpointer!\n" << std::endl;
            return;
        };
        
        // Test of 2 opeenvolgende knopen rood zijn (AANVULLEN met kinderen van huidige knoop)
        if(knoop.kleur == rood && (knoop.ouder->kleur == rood)){
            //throw "Twee opeenvolgende rode knopen zijn niet toegelaten!\n";
            std::cout << "Twee opeenvolgende rode knopen zijn niet toegelaten!\n" << std::endl;
            return;
        }
        
        
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
        //FUNCTIONS
        RZWknoop():ouder(0){}
        RZWknoop(const Sleutel& sl):sleutel{sl},ouder(0),kleur(rood){};
        RZWknoop(Sleutel&& sl):sleutel{move(sl)},ouder(0),kleur(rood){};
        RZWboom<Sleutel>& geefKind(bool links);
        
        RZWboom<Sleutel> * geefZoekboom(RZWboom<Sleutel> * root) const;
        
        
        //VARIABLES
        Sleutel sleutel;
        RZWknoop<Sleutel>* ouder;
        RZWboom<Sleutel> links,rechts;
        RZWkleur kleur;
        bool dubbelZwart;
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
	std::cout << "We draaien naar: " ; 
	naarLinks? std::cout << "links" : std::cout << "rechts" ;
	std::cout << std::endl;
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
};


//EIGEN IMPLEMENTATIES
template<class Sleutel>
RZWboom<Sleutel>::RZWboom(){}

template <class Sleutel>
RZWboom<Sleutel>::RZWboom(const std::vector<Sleutel>& sleutels, const std::vector<Sleutel>& rodeSleutels){
    *this = RZWboom<Sleutel>(std::make_unique<RZWknoop<Sleutel> >(sleutels[0]));
    //(**this).kleur = zwart;   //WERKT OOK
    (*this)->kleur = zwart;
    
    for(Sleutel s : sleutels){
        //  Altijd van de wortel afdalen
        RZWknoop<Sleutel>* ouder;
        RZWboom<Sleutel>* plaats;
        this->zoek(s, ouder, plaats);
        
        //  Ouder bevat de pointer naar de ouder
        //  Plaats bevat de pointer naar de plaats waar de knoop dient toegevoegd te worden
        if(! *plaats){
            RZWboom<Sleutel> nieuw = RZWboom<Sleutel>(std::make_unique<RZWknoop<Sleutel>>(s));
            nieuw->ouder = ouder;   //  RZWboom is friend van RZWknoop, dus boom kan aan members van knoop
            nieuw->kleur = zwart;   // Eerst maken we een volledige zwarte boom
            
            // Zoeken in een vector wordt niet gedaan, want is O(n)!            
            /*if(std::find(rodeSleutels.begin(), rodeSleutels.end(), nieuw->sleutel) == rodeSleutels.end()){
                nieuw->kleur = zwart;
            }*/
            *plaats = std::move(nieuw);                      
        }
    }
    
    // Om het kleur te bepalen steek je dus gewoon alle sleutels in een binaire boom (zie hierboven)
    // Vervolgens ga je alle rode sleutels in de vector gaan opzoeken en hun kleur veranderen.
    for(Sleutel s: rodeSleutels){
        RZWknoop<Sleutel>* ouder;
        RZWboom<Sleutel>* plaats;
        this->zoek(s, ouder, plaats);
        
        if(plaats){
            (**plaats).kleur = rood;
        }
    }
    
}

template <class Sleutel>
RZWkleur RZWboom<Sleutel>::geefKleur() const {
    //return (**this).kleur;
    return (*this)->kleur;    // Ook mogelijk
}

template <class Sleutel>
void RZWboom<Sleutel>::voegtoe(const Sleutel& sleutel){
	    RZWknoop<Sleutel>* ouder;
        RZWboom<Sleutel>* plaats;
        this->zoek(sleutel, ouder, plaats);
        if(! *plaats){
            RZWboom<Sleutel> nieuw = RZWboom<Sleutel>(std::make_unique<RZWknoop<Sleutel>>(sleutel));
            nieuw->ouder = ouder; 
            *plaats = std::move(nieuw);          
        }
        plaats->herstelBoom(this);
}

template <class Sleutel> 
void RZWboom<Sleutel>::herstelBoom(RZWboom<Sleutel> * root){
	std::cout << "Sleutel: " << (*this)->sleutel << std::endl;
	//Je bent root
	if(!(*this)->ouder)
	{
		(*this)->kleur = zwart;
		return;
	}
	//Je ouder is zwart
	if((*this)->ouder->kleur == zwart){
		return;
	}
	
	//Ouder is rood
	bool ouderlinkerkind = (*this)->ouder->ouder->geefKind(true)->sleutel == (*this)->ouder->sleutel ? true : false;	
	ouderlinkerkind ? std::cout << "ouder is linkerkind van grootouder" : std::cout <<"ouder is rechterkind van grootouder";
	std::cout << std::endl;	
	//Als de broer rood is
	if((*this)->ouder->ouder->geefKind(!ouderlinkerkind)->kleur == rood){
		(*this)->ouder->ouder->geefKind(!ouderlinkerkind)->kleur = zwart;
		(*this)->ouder->kleur = zwart;
		(*this)->ouder->ouder->kleur = rood;
		(*this)->ouder->ouder->geefZoekboom(root)->herstelBoom(root);
	}
	//Als de broer zwart is
	else{
		//Als de drie knopen op één lijn liggen
		if((*this)->ouder->geefKind(ouderlinkerkind)->sleutel == (*this)->sleutel){
			std::cout << "We zijn in het geval dat de drie knopen op één lijn liggen" << std::endl;
			(*this)->ouder->kleur = zwart;
			(*this)->ouder->ouder->kleur = rood;
			std::cout << "grootouder knoop: " << (*this)->ouder->ouder->sleutel << std::endl;
			std::cout << "ouder knoop: " << (*this)->ouder->sleutel << std::endl;
			(*this)->ouder->ouder->geefZoekboom(root)->roteer(!ouderlinkerkind);
			(*this)->ouder->geefZoekboom(root)->herstelBoom(root);
		}
		else{
			std::cout << "We zijn in het geval dat de drie knopen NIET op één lijn liggen" << std::endl;
			std::cout << "ouder knoop: " << (*this)->ouder->sleutel << std::endl;
			RZWknoop<Sleutel>* ouder = (*this)->ouder;
			(*this)->ouder->geefZoekboom(root)->roteer(ouderlinkerkind);
			ouder->geefZoekboom(root)->herstelBoom(root);
		}
	}
}     

template <class Sleutel>
RZWboom<Sleutel> * RZWknoop<Sleutel>::geefZoekboom(RZWboom<Sleutel> * root) const
{
	return this->ouder ? (this->ouder->geefKind(true)->sleutel == this->sleutel ? &(this->ouder->links) : &(this->ouder->rechts)) : root;
}      

template <class Sleutel>
void RZWboom<Sleutel>::verwijder(const Sleutel& sleutel)
{
	    RZWknoop<Sleutel>* ouder;
        RZWboom<Sleutel>* plaats;
        
        Sleutel s;
        this->zoek(sleutel, ouder, plaats);
        if(! *plaats){
			std::cout << "knoop zit niet in boom." <<std::endl;          
			return;
    	}
    	
        std::cout << "De te verwijderen knoop " << (*plaats)->sleutel;
        
        //Hier wordt eigenlijk gekeken welke knoop de fysiek te verwijderen knoop is, die knoop vinden we later terug bij plaats.
		if(!((*plaats)->geefKind(true)) && !(*plaats)->geefKind(false)){
        	 std::cout << " heeft geen kinderen" << std::endl;
		}
		else{
			if(((*plaats)->geefKind(true)) && (*plaats)->geefKind(false)){
				std::cout << " heeft twee kinderen" << std::endl;
				while((*plaats)->geefKind(true)){
        		plaats = (&(*plaats)->geefKind(true));
        		ouder = (*plaats)->ouder;
				}
			}
			else{
				std::cout << " heeft een kind" << std::endl;}
				//plaats = (*plaats)->geefKind(true) ? (&(*plaats)->geefKind(true)) : (&(*plaats)->geefKind(false));}
		}
		
		s = (*plaats)->sleutel;
			
		std::cout << "De sleutel die we fysiek gaan verwijderen is: " << (*plaats)->sleutel <<std::endl;

		//De sleutel van de knoop die fysiek verwijderd moet worden, moet op de plaats van de te verwijderen knoop komen te staan.
		//Dit stuk kan en moet waarschijnlijk wel efficiënter
		RZWknoop<Sleutel>* ouder2;
        RZWboom<Sleutel>* plaats2;
		this->zoek(sleutel, ouder2, plaats2);
		(*plaats2)->sleutel = s;
		
		plaats->herstelBoomNaVerwijderen(this);
		
		//Als de fysiek te verwijderen knoop rood is, mogen we gewoon verwijderen
}

template <class Sleutel>
void RZWboom<Sleutel>::herstelBoomNaVerwijderen(RZWboom<Sleutel> * root){
		if((*this)->kleur == rood){
			std::cout << "De fysiek te verwijderen knoop is rood" << std::endl;
			this->reset();
		}
		//Fysiek te verwijderen knoop is zwart: ofwel een rood kind ofwel geen reëele kinderen.
		else{
			//Zwarte knoop is root
			if(!(*this)->ouder){
				return;
			}
			//Zwarte knoop heeft geen 'echte' kinderen
			if(!((*this)->geefKind(true)) && !(*this)->geefKind(false)){
				
				//Slecht gekozen naam, maar deze bool slaat op of this al dan niet een linkerkind is van zijn ouder.
				bool ouderlinkerkind = (*this)->ouder->geefKind(true)->sleutel == (*this)->sleutel ? true : false;
				//Broer ophalen
				RZWboom<Sleutel>* broer = (&(*this)->ouder->geefKind(!ouderlinkerkind));
				
				std::cout << "Broer: " << (*broer)->sleutel << std::endl;
				
				//We controleren het kleur van de broer.
				if((*broer)->kleur == zwart){
					std::cout << "broer is zwart" << std::endl;	
					//Dit is het 2de geval uit de cursus.
					//Er wordt herkleurd en de ouder en broer worden geroteerd in de richting van ouderlinkerkind.
					//Het probleem is hierna opgelost.
					//Met this-reset() verwijderen we de knoop.
					if((*broer)->geefKind(!ouderlinkerkind) && (*broer)->geefKind(!ouderlinkerkind)->kleur == rood){
							std::cout << "2de geval" << std::endl;
							(*broer)->kleur = (*this)->ouder->kleur;
							(*this)->ouder->kleur = zwart;
							(*broer)->geefKind(!ouderlinkerkind)->kleur = zwart;
							(*this)->ouder->geefZoekboom(root)->roteer(ouderlinkerkind);
							this->reset();
					}
					else{
						//Dit is het 3de geval uit de cursus.
						//We hervormen het probleem naar het 2de geval.
						//Er wordt herkleurd en de broer en zijn kinderen worden geroteerd in de richting die tegengesteld is aan de richting van de te verwijderen knoop t.o.v zijn ouder. Hte omgekeerde van ouderlinkerkind dus.
						//Na het roteren moet de boom nog altijd hersteld worden. 
						if((*broer)->geefKind(!ouderlinkerkind) && (*broer)->geefKind(ouderlinkerkind)->kleur == rood && (*broer)->geefKind(!ouderlinkerkind)->kleur == zwart){
							std::cout << "3de geval" << std::endl;
							(*broer)->kleur = rood;
							(*broer)->geefKind(ouderlinkerkind)->kleur = zwart;
							(*broer)->geefZoekboom(root)->roteer(!ouderlinkerkind);
							(*this)->geefZoekboom(root)->herstelBoomNaVerwijderen(root);
						}
						//1ste geval in de cursus. De broer heeft geen kinderen of 2 zwarte kinderen
						//Hier wordt enkel nog wat herkleurd. 
						//Als de ouder zwart was (voor de verkleuring), is die nu dubbel zwart, dus moet de boom opnieuw hersteld worden.
						//Was de ouder rood (voor de verkleuring), dan is alles opgelost.
						//Met this->reset() verwijderen we de knoop.
						else{
							std::cout << "1ste geval" << std::endl;
							(*broer)->kleur = rood;
							if((*this)->ouder->kleur = zwart){
								(*this)->ouder->geefZoekboom(root)->herstelBoomNaVerwijderen(root);
							}
							else{
								(*this)->ouder->kleur = zwart;	
							}
							this->reset();			
						}	
					}
				}
				//Broer is rood
				//4de geval uit de cursus: broer krijgt een zwarte kleur, ouder wordt rood en we roteren de ouder en de broer. De richting van rotatie = de ligging van het kind t.o.v de ouder
				else{
					(*broer)->kleur = zwart;
					(*this)->ouder->kleur = rood;
					(*this)->ouder->geefZoekboom(root)->roteer(ouderlinkerkind);
					(*this)->geefZoekboom(root)->herstelBoomNaVerwijderen(root);	
				}
			}
			//De te verwijderen knoop heeft één rood kind, we zetten sleutel van kind in de te verwijderen knoop en verwijderen daarna het kind (kind->reset()).
			else{
				RZWboom<Sleutel>* kind = (*this)->geefKind(true) ? (&(*this)->geefKind(true)) : (&(*this)->geefKind(false));
				(*this)->sleutel = (*kind)->sleutel;
				kind->reset();
			}
		}
}

//Als er in het algemeen fouten zijn, is dat omdat er knopen (vaak kinderen van knopen) opgehaald worden die niet bestaan. 
//In dat geval kan een extra controle ingebouwd worden, zoals bij het 2de en 3de geval waar we eerst controleren of de broer wel kinderen heeft: (*broer)->geefKind(!ouderlinkerkind).
#endif
