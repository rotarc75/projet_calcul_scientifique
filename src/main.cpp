#include <iostream>
#include <cmath>
#include <fstream>

#include "fonctions.hpp"

using namespace std;

const string BLEU  = "\033[34m";
const string ORANGE = "\033[38;5;208m";
const string BLANC = "\033[0m";

const int m = 1;

void affiche_maillage(int N, int M){

    cout << "Affichage du maillage pour N = "<< N << ", M = "<<M<<".\n";

    // Affichage de la première ligne
    string buffer_haut ="" + BLEU;
    for (int c = 0; c < N; c++) buffer_haut += " _ _";

    buffer_haut += BLANC + "\n";
    cout << buffer_haut ;

    for (int l = M-1; l >= 0; l--){

        string buffer_mil = "";
        string buffer_bas = "";

        for (int c = 0; c < N; c++){

            bool direction = ((l + c) % 2 == 0);

            if (c == 0){
                buffer_mil += BLEU + "|" + BLANC;
                buffer_bas += BLEU + "|" + BLANC;
            }

            if (direction){ // CAS 1 : direction "croissante"
                buffer_mil += ORANGE + "  /" + BLEU + "|" + BLANC;
                buffer_bas += BLEU + "_"+ ORANGE +"/" + BLEU + "_|" + BLANC;
            } else {  // CAS 2 : direction "décroissante"
                buffer_mil += ORANGE + "\\  "+ BLEU + "|"+ BLANC ;
                buffer_bas += BLEU + "_"+ ORANGE +"\\"+BLEU + "_|" + BLANC;
            }
       }

        cout << buffer_mil << endl << buffer_bas << endl;
    }

}


double up(double x, double y){
    double c = (2.*m*m*M_PI*M_PI + 1);
    return (cos(m*M_PI*x)*cos(m*M_PI*y)) /c ;
}

// Se référer à la question 32)a. Pour la formule
double f(double x, double y, double eta0, double (* eta) (double,double)){
    double k = -(eta0*m*M_PI)/(4.*m*m*M_PI*M_PI +2);
    double t = x*sin(m*M_PI*x)*cos(m*M_PI*y) + y*cos(m*M_PI*x)*sin(m*M_PI*y);
    double o = 2*m*m*M_PI*M_PI*eta(x,y) +1;
    return k*t + o*up(x,y);
}


double f0(double x, double y){
    return f(x,y,0,[](double,double){return 1.;});
}


double eta(double eta0, double x, double y){
    return 1. - eta0/4 * (x*x+y*y);
}


int main(){
    cout << "Début des tests numériques\n";

    // Déclaration des paramètres
    //const double eta0 = 0.;
    const double a = 1.;
    const double b = 1.;


    auto lambda = [](double,double){ return 1.;};

    auto eta1 = lambda;

    // Tests numériques

    //affiche_maillage(10,14);

    vector<int> valeurs_tests = {4,8,16,20,32,64,128};

    ofstream fichier("erreurs.txt");
    if (!fichier.is_open()) {
        cout << "Erreur lors de l'ouverture du fichier.\n";
        return 1;
    }

    fichier << "N e0 e1 e_inf\n";

    for (int N : valeurs_tests){
        maillage maillageNxN = maillageTR(N,N);


        //auto f0 = std::bind(&f,_1,_2,eta0,m,[](double,double){return 1.;});

        vector<double> B = scdmembre(f0,N,N,maillageNxN,a,b);


        vector<double> uh = bicg_stab(B,maillageNxN,N,N,a,b,1e-10,100000,eta1);

        auto up0 = [](double x, double y){ return up(x,y);};
        vector<double> tab_err = erreurs(up0,uh,maillageNxN,N,N,a,b);

        cout << "e0(2/" << N << ") = " << tab_err[0] << ", ";
        cout << "e1(2/" << N << ") = " << tab_err[1] << ", ";
        cout << "e2(2/" << N << ") = " << tab_err[2] << endl;


        fichier << N << " " << tab_err[0] << " " << tab_err[1] << " " << tab_err[2] << "\n";
    }

}




