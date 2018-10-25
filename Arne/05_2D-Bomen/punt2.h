#ifndef __PUNT2_h
#define __PUNT2_h

#include <iostream>
#include <iomanip>
using std::setw;
struct punt2 {
public:
    int x, y;

    // default constructor
    punt2() {}

    // constructor met coordinaten
    punt2(int _x, int _y) : x(_x), y(_y) {}

    // copy constructor
    punt2(const punt2& p):x(p.x),y(p.y){}

    // set coordinaten
    void set(int _x, int _y) { x = _x; y = _y; }

    // is equal operator
    bool operator==(const punt2& p) const{
        return p.x==x && p.y==y;
    }

    // print operator
    friend std::ostream& operator<<(std::ostream& os, const punt2 p2){
        return os<<"("<<setw(5)<<p2.x<<","<<setw(5)<<p2.y<<")";
    }

    // euclidische afstand
    // opletten voor overflow!
    unsigned int kwadafstand(const punt2& p) const{
        return (p.x-x)*(p.x-x) + (p.y-y)*(p.y-y);
    }
};
#endif

