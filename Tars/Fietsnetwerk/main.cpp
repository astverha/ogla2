#include "stroomnet17.h"


using std::cout;
using std::endl;
int main(){
    /*
    GraafMetTakdata <GERICHT,int> gr(8);
    gr.voegVerbindingToe(1,2,7 );
    gr.voegVerbindingToe(7,1,2 );
    gr.voegVerbindingToe(7,3,6 );
    gr.voegVerbindingToe(3,4,7 );
    gr.voegVerbindingToe(4,5,1 );
    gr.voegVerbindingToe(2,5,4 );
    gr.voegVerbindingToe(1,0,9 );
    gr.voegVerbindingToe(0,2,3 );
    gr.voegVerbindingToe(0,7,5 );
    gr.voegVerbindingToe(0,6,6 );
    gr.voegVerbindingToe(5,6,6 );
    gr.voegVerbindingToe(6,3,2 );
    gr.voegVerbindingToe(6,4,8 );
    */

    GraafMetTakdata <GERICHT,int> gr(4);
    gr.voegVerbindingToe(0,1,7 );
    gr.voegVerbindingToe(1,3,2 );
    gr.voegVerbindingToe(0,2,5 );
    gr.voegVerbindingToe(1,2,1 );
    gr.voegVerbindingToe(2,3,6 );

    gr.teken("begin.dot");


    Stroomnetwerk<int> sn(gr,0,3);
    sn.teken("sn.dot");
    Stroomnetwerk<int> oplossing=sn.geefStroom();
    oplossing.teken("oplossing.dot");
    //assert(oplossing.geefCapaciteit()==13);
}
