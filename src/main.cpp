#include <iostream>
#include <tuple>
#include <vector>

#include "noeud.hpp"

using namespace std;

// Fonction qui renvoie une subdivision uniforme de [-a,a]
vector<double> Subdiv(double a, int N){
    vector<double> subdiv = vector<double>(N+1);
    double pas = 2*a / N;

    for (int k = 0; k <= N; k++) subdiv[k] = -a + k*pas;

    return subdiv;
}

// Fonction qui renvoie le numéro associé à des coordonnées
int numgb(int N, int M, int i, int j){ return (N+1)*j + i; }

//Fonction qui étant donné entier s valide, donne les coordonnées du noeud
tuple<int> invnumbg(int N, int M,int s){
    return (s % (N+1),s / (N+1));
}

