#ifndef NOEUD_H
#define NOEUD_H
class Noeud
{
private:
    double x,y;
    int i,j,s;

public:
    Noeud(double x, double y, int i, int j, int s);

    int getI();
    int getJ();
};
#endif