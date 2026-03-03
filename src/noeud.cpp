#include "noeud.hpp"

Noeud::Noeud(double x, double y, int i, int j,int s){
    x = x;
    y = y;
    i = i;
    j = j;
    s = s;
}

int Noeud::getI(){ return i;}

int Noeud::getJ(){ return j;}