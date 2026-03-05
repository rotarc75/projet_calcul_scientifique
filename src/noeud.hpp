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

class Triangle {
private:
    int n_1, n_2, n_3; 

public:
    Triangle();
    Triangle(int n_1, int n_2, int n_3);
};
#endif