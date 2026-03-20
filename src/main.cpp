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

//Fonction qui étant donné un pavé de NM rectangles renvoie un maillage
//triangulaire sous forme d'une liste qui contient les triangles
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


// Fonction qui renvoie les coordonnées des points du triangle
tuple<vector<double>,vector<double>> CoordsTrig(double a, double b, int N,
    int M, Triangle T){
    vector<double> xs = vector<double>(3);
    vector<double> ys = vector<double>(3);

    for (int k = 0; k < 3; k++){
        tuple<int,int> tup = invnumgb(N,M,T.get(k));
        xs[k] = -a + (2*a)/N * get<0>(tup);
        ys[k] = -b + (2*b)/M * get<1>(tup);

    }

    return {xs,ys};
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


vector<double> integ_eta_triang(double (* eta)(double,double),
    vector<Triangle> maillage,int N, int M,double a,double b){

    vector<double> ET = vector<double>(maillage.size());
    int k = 0;

    // Parcours du maillage
    for (Triangle T : maillage){

        tuple<vector<double>,vector<double>> xs_ys = CoordsTrig(a,b,N,M,T);
        vector<double> xs = get<0>(xs_ys);
        vector<double> ys = get<1>(xs_ys);

        double det = (xs[1]-xs[0])*(ys[2]-ys[0]) - (ys[1]-ys[0])*(xs[2]-xs[0]);

        // On determine les milieux des côtes de T
        double m0x = (xs[0] + xs[1])/2.;
        double m0y = (ys[0] + ys[1])/2.;
        double m1x = (xs[1] + xs[2])/2.;
        double m1y = (ys[1] + ys[2])/2.;
        double m2x = (xs[0] + xs[2])/2.;
        double m2y = (ys[0] + ys[2])/2.;

        // Calculs de eta \circ F_T en les milieux des côtés du triangles T^
        double eta0 = eta(m0x,m0y);
        double eta1 = eta(m1x,m1y);
        double eta2 = eta(m2x,m2y);

        ET[k] = 1./6. *det * (eta0 + eta1 + eta2);
        k++;
    }

    return ET;
}

 vector<vector<double>> DiffTerm(tuple<vector<double>,vector<double>> xs_ys, double val){
    vector<double> xs = get<0>(xs_ys);
    vector<double> ys = get<1>(xs_ys);

    vector<vector<double>> BT = CalcMatBT(xs,ys);
    double det = (xs[1]-xs[0])*(ys[2]-ys[0]) - (ys[1]-ys[0])*(xs[2]-xs[0]);

    //Construction de la transposée de l'inverse de BT
    vector<vector<double>> transp_inv_BT;
    transp_inv_BT[0][0] = -1/det * BT[0][0];
    transp_inv_BT[0][1] = 1/det * BT[0][1];
    transp_inv_BT[1][0] = 1/det * BT[1][0];
    transp_inv_BT[0][0] = -1/det * BT[1][1];

    //Calcul des Nabla_lambda^
    vector<double> Nabla_lambdacha0 = {{-1,-1}}; //lambdacha0 = (1-x^-y^)
    vector<double> Nabla_lambdacha1 = {{1,0}}; //lambdacha1 = x^
    vector<double> Nabla_lambdacha2 = {{0,1}}; //lambdacha2 = y^
    
    //Calcul des Nabla_lambda = BT*Nabla_lambdacha
    double nl00 = transp_inv_BT[0][0] * Nabla_lambdacha0[0] + transp_inv_BT[0][1] * Nabla_lambdacha0[1];
    double nl01 = transp_inv_BT[1][0] * Nabla_lambdacha0[0] + transp_inv_BT[1][1] * Nabla_lambdacha0[1];

    double nl10 = transp_inv_BT[0][0] * Nabla_lambdacha1[0] + transp_inv_BT[0][1] * Nabla_lambdacha1[1];
    double nl11 = transp_inv_BT[1][0] * Nabla_lambdacha1[0] + transp_inv_BT[1][1] * Nabla_lambdacha1[1];

    double nl20 = transp_inv_BT[0][0] * Nabla_lambdacha2[0] + transp_inv_BT[0][1] * Nabla_lambdacha2[1];
    double nl21 = transp_inv_BT[1][0] * Nabla_lambdacha2[0] + transp_inv_BT[1][1] * Nabla_lambdacha2[1];

    //Calcul des produits scalaires * ET
    double val00 = val * (nl00 * nl00 + nl01 * nl01);
    double val01 = val * (nl00 * nl10 + nl01 * nl11);
    double val02 = val * (nl00 * nl20 + nl01 * nl21);
    double val11 = val * (nl10 * nl10 + nl11 * nl11);
    double val12 = val * (nl10 * nl20 + nl11 * nl21);
    double val22 = val * (nl20 * nl20 + nl21 * nl21);

    return {{val00, val01, val02}, 
        {val01, val11, val12},
        {val02, val12, val22}
    };
 }


