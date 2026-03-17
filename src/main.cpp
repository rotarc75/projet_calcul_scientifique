#include <tuple>
#include <vector>


#include "triangle.hpp"

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
tuple<int,int> invnumgb(int N, int M,int s){
    return {s % (N+1),s / (N+1)};
}

//Fonction qui étant donné un pavé de NM rectangles renvoie un maillage triangulaire sous forme d'une liste qui contient les triangles
vector<Triangle> maillageTR(int N, int M){
    vector<Triangle> TRG(2*N*M);
    int k = 0;
    bool direction = true; // true pour / et false pour \

    for (int l = 0; l < M; l++){
        for (int c = 0; c < N ; c++){

            //Pour alterner le sens des triangles à chaque petit rectangle
            direction = (l+c)%2 == 0;

            // Calcul des coordonnées des quatres sommets du rectangle
            int bas_g = numgb(N,M,c,l);
            int bas_d = numgb(N,M,c+1,l);
            int haut_g = numgb(N,M,c,l+1);
            int haut_d = numgb(N,M,c+1,l+1);

            // Création des triangles
            if (direction){
                TRG[k] = Triangle(bas_g,haut_g,haut_d);
                TRG[k+1] = Triangle(bas_g,bas_d,haut_d);
            } else {
                TRG[k] = Triangle(bas_g,haut_g,bas_d);
                TRG[k+1] = Triangle(haut_g,haut_d,bas_d);
            }

            k += 2;
        }
    }

    return TRG;
}

// Fonction qui renvoie la jacobienne de F_T
// Voir question 20, elle justifie ce calcul
vector<vector<double>> CalcMatBT(vector<double> xs, vector<double> ys){
    double bt_00 = xs[1] - xs[0];
    double bt_10 = ys[1] - ys[0];
    double bt_01 = xs[2] - xs[0];
    double bt_11 = ys[2] - ys[0];

    return {{bt_00,bt_01},{bt_10,bt_11}};
}

