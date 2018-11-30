#include <iostream>

#include "shiftand.h"

using namespace std;

void print_queue(queue<const uchar*> q)
{
    cout << "inhoud queue: " << endl;
    while (!q.empty())
    {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}

int main() {
    cout << "Hello, World!" << endl << endl;

    uchar* naald = (uchar*) "aap";
    uint naaldLengte = 3;

    Shiftand shifty = Shiftand(naald, naaldLengte);

    cout << "Letterpatroon: " << endl;
    for(int i=0; i< naaldLengte; i++){
        cout << shifty.letterpatroon[naald[i]] << endl;
    }
    cout << endl;

    uchar* hooiberg = (uchar*) "jan jaap van der aap";
    uint hooibergLengte = 20;

    queue<const uchar*> teVerwerkenUchars;

    shifty.zoek(teVerwerkenUchars, hooiberg, hooibergLengte);

    print_queue(teVerwerkenUchars);

    return 0;
}