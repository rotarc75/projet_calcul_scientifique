#include <iostream>
#include <cmath>
#include <fstream>

#include <functional>

#include "fonctions.hpp"

using namespace std;

const string BLEU  = "\033[34m";
const string ORANGE = "\033[38;5;208m";
const string BLANC = "\033[0m";

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


double up(double x, double y, int m){
    double c = (2.*m*m*M_PI*M_PI + 1);
    return (cos(m*M_PI*x)*cos(m*M_PI*y)) /c ;
}

// Se référer à la question 32)a. Pour la formule
double f(double x, double y, int m, double eta0, double (* eta) (double,double)){
    double k = -(eta0*m*M_PI)/(4.*m*m*M_PI*M_PI +2);
    double t = x*sin(m*M_PI*x)*cos(m*M_PI*y) + y*cos(m*M_PI*x)*sin(m*M_PI*y);
    double o = 2*m*m*M_PI*M_PI*eta(x,y) +1;
    return k*t + o*up(x,y,m);
}

// Cas eta0=0
double f0(double x, double y, int m){
    return f(x,y,m,0,[](double,double){return 1.;});
}

// Cas eta0=1
double f1(double x, double y, int m){
    return f(x,y,m,1.,[](double,double){return 1.;});
}

double eta(double eta0, double x, double y){
    return 1. - eta0/4 * (x*x+y*y);
}

double eval_uh(double x, double y, vector<double> uh, maillage TRG, int N, int M, double a, double b){
    // On cherche à identifier dans quel triangle se trouve (x,y)
    double h1 = (2*a)/N;
    double h2 = (2*b)/M;
    int i = (int) ((x+a)/h1);
    int j = (int) ((y+b)/h2);

    int l = 2*j*N+2*i;

    // (x,y) est dans T_l ou T_{l+1} (q31)
    // On a besoin du signe des lambdas

    for (int t = l; t < l + 2; t++){
        Triangle T = TRG[t];

        duplix xs_ys = CoordsTrig(a, b, N, M, T);
        vector<double> xs = get<0>(xs_ys);
        vector<double> ys = get<1>(xs_ys);

        matrix BT = CalcMatBT(xs, ys);

        double detBT = BT[0][0]*BT[1][1] - BT[0][1]*BT[1][0];

        // Inversion BT
        matrix inv_BT = {{BT[1][1]/detBT, -BT[0][1]/detBT},
                        {-BT[1][0]/detBT, BT[0][0]/detBT}};
        
        // Calcul des lambdas
        double lambda_1 = inv_BT[0][0]*(x - xs[0]) + inv_BT[0][1]*(y - ys[0]);
        double lambda_2 = inv_BT[1][0]*(x - xs[0]) + inv_BT[1][1]*(y - ys[0]);
        double lambda_0 = 1. - lambda_1 - lambda_2;

        // Test signe
        if (lambda_0 >= 0 && lambda_1 >= 0 && lambda_2 >= 0){

            // Alors (x,y) est dans ce triangle
            double eval = lambda_0*uh[T.get(0)] + lambda_1*uh[T.get(1)] + lambda_2*uh[T.get(2)];
            
            return eval;
        }
    }

    return 0.;
}

int main(){
    cout << "Début des tests numériques\n";

    // Déclaration des paramètres
    // Const double eta0 = 0.;
    const double a = 1.;
    const double b = 1.;
    int m = 1;

    auto lambda = [](double,double){ return 1.;};

    auto eta1 = lambda;

    // Tests numériques

    affiche_maillage(10,14);

    cout << "Calcul des erreurs en cours...\n";

    vector<int> valeurs_tests = {4,8,16,20,32,64};

    ofstream fichier("erreurs.txt");
    if (!fichier.is_open()) {
        cout << "Erreur lors de l'ouverture du fichier.\n";
        return 1;
    }

    fichier << "N e0 e1 e_inf\n";

    for (int N : valeurs_tests){
        maillage maillageNxN = maillageTR(N,N);


        // auto f0 = std::bind(&f,_1,_2,eta0,m,[](double,double){return 1.;});

        vector<double> B = scdmembre(f0,N,N,maillageNxN,a,b,m);

        vector<double> uh = bicg_stab(B,maillageNxN,N,N,a,b,1e-10,100000,eta1);

        auto up0 = [](double x, double y, int m){ return up(x,y,m);};
        vector<double> tab_err = erreurs(up0,uh,maillageNxN,N,N,a,b,m);

        cout << "e0(2/" << N << ") = " << tab_err[0] << ", ";
        cout << "e1(2/" << N << ") = " << tab_err[1] << ", ";
        cout << "e2(2/" << N << ") = " << tab_err[2] << endl;


        fichier << N << " " << tab_err[0] << " " << tab_err[1] << " " << tab_err[2] << "\n";
    }

    // debut tests question 32d, maillage 32x32, 50 points par courbe

    cout << "Génération des courbes en cours...\n";

    ofstream fichier1("courbes.txt");
    if (!fichier1.is_open()) {
        cout << "Erreur lors de l'ouverture du fichier.\n";
        return 1;
    }

    fichier1 << "m x u^h u^p\n";
    double pas = 2./50;
    int N_courbes = 32;

    maillage maillage_courbes = maillageTR(N_courbes, N_courbes);

    // Tests sur differents m
    vector<int> valeurs_m = {2, 4, 8, 12};

    for (int m_courbe : valeurs_m){
        auto f1_courbe = [](double x, double y, int m_courbe){ return f1(x, y, m_courbe);};
        vector<double> B_courbe = scdmembre(f1_courbe, N_courbes, N_courbes, maillage_courbes, a, b, m_courbe);
    
        auto eta1_courbe = [](double x, double y){return eta(1.,x,y);};
        vector<double> uh_courbe = bicg_stab(B_courbe, maillage_courbes, N_courbes, N_courbes, a, b, 1e-10, 100000, eta1_courbe);

        double ctr = -1.;

        while (ctr <= 1.){
            double u_app = eval_uh(ctr, 0.5, uh_courbe, maillage_courbes, N_courbes, N_courbes, a, b);
            double u_exa = up(ctr, 0.5, m_courbe);

            fichier1 << m_courbe << " " << ctr << " " << u_app << " " << u_exa << "\n";
            ctr += pas;
        }

    }

    cout << "Tests terminés, les fichiers .txt sont prêts !\n";

}




