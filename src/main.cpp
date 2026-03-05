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

//Fonction qui étant donné un pavé de NM rectangles renvoie une matrice qui contient les triangles
vector<Triangle> maillageTR(int N, int M){
    int K = 2*N*M;
    vector<Triangle> TRG(K);

    int l = 0;

    for (int j = 0; j < M; j++){
        for (int i = 0; i < N; i++){
            int bas_gauche = numgb(N, M, i, j);
            int bas_droit = numgb(N,M, i+1, j);
            int haut_gauche = numgb(N, M, i, j+1);
            int haut_droit = numgb(N, M, i+1, j+1);

            if ((i+j) % 2 == 0){
                TRG[l] = Triangle(bas_gauche, haut_gauche, haut_droit);
                TRG[l+1] = Triangle(bas_gauche, bas_droit, haut_droit);
            } else {
                TRG[l] = Triangle(bas_gauche, bas_droit, haut_gauche);
                TRG[l+1] = Triangle(bas_droit, haut_gauche, haut_droit);
            }

            l += 2;
        }
    }
    
    return TRG;
}