#include <stdlib.h>

#include "fonctions.hpp";
#include "triangle.hpp"





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
duplix CoordsTrig(double a, double b, int N,
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
matrix CalcMatBT(vector<double> xs, vector<double> ys){
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

        duplix xs_ys = CoordsTrig(a,b,N,M,T);
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


matrix DiffTerm(duplix xs_ys, double val){
    vector<double> xs = get<0>(xs_ys);
    vector<double> ys = get<1>(xs_ys);

    matrix BT = CalcMatBT(xs,ys);
    double det = (xs[1]-xs[0])*(ys[2]-ys[0]) - (ys[1]-ys[0])*(xs[2]-xs[0]);

    //Construction de la transposée de l'inverse de BT
    matrix trsp_inv_BT;
    trsp_inv_BT[0][0] = -1/det * BT[0][0];
    trsp_inv_BT[0][1] = 1/det * BT[0][1];
    trsp_inv_BT[1][0] = 1/det * BT[1][0];
    trsp_inv_BT[0][0] = -1/det * BT[1][1];

    //Calcul des Nabla_lambda^
    vector<double> NLcha0 = {{-1,-1}}; //lambdacha0 = (1-x^-y^)
    vector<double> NLcha1 = {{1,0}}; //lambdacha1 = x^
    vector<double> NLcha2 = {{0,1}}; //lambdacha2 = y^
    //Calcul des Nabla_lambda = BT*Nabla_lambdacha
    double nl00 = trsp_inv_BT[0][0] * NLcha0[0] + trsp_inv_BT[0][1] * NLcha0[1];
    double nl01 = trsp_inv_BT[1][0] * NLcha0[0] + trsp_inv_BT[1][1] * NLcha0[1];

    double nl10 = trsp_inv_BT[0][0] * NLcha1[0] + trsp_inv_BT[0][1] * NLcha1[1];
    double nl11 = trsp_inv_BT[1][0] * NLcha1[0] + trsp_inv_BT[1][1] * NLcha1[1];

    double nl20 = trsp_inv_BT[0][0] * NLcha2[0] + trsp_inv_BT[0][1] * NLcha2[1];
    double nl21 = trsp_inv_BT[1][0] * NLcha2[0] + trsp_inv_BT[1][1] * NLcha2[1];

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


matrix ReacTerm(duplix xs_ys, double val){
    vector<double> xs = get<0>(xs_ys);
    vector<double> ys = get<1>(xs_ys);

    double det = (xs[1]-xs[0])*(ys[2]-ys[0]) - (ys[1]-ys[0])*(xs[2]-xs[0]);

    //Calcul des integrales des lambda_i * lambda_j
    double int_lambda_ii = abs(det) * 1.0/12.0;
    double int_lambda_ij = abs(det) * 1.0/24.0;

    return {{int_lambda_ii, int_lambda_ij, int_lambda_ij},
        {int_lambda_ij, int_lambda_ii, int_lambda_ij},
        {int_lambda_ij, int_lambda_ij,int_lambda_ii}};
}




vector<double> matvec(vector<double> V, vector<Triangle> maillage, int N, int M,
    double a, double b, double (* eta)(double,double)){

    int K = 2*N*M;
    vector<double> W((N+1)*(M+1));

    // Contient les valeurs de l'integrales de eta sur chaque T
    vector<double> VALS = integ_eta_triang(eta,maillage, N,M,a,b);

    for (int t = 0; t < K; t++){
        Triangle T = maillage[t];

        // Calcul de B_T
        duplix xs_ys = CoordsTrig(a,b,N,M,T);
        matrix BT = CalcMatBT(get<0>(xs_ys),get<1>(xs_ys));
        matrix D = DiffTerm(xs_ys,VALS[t]);
        matrix R = ReacTerm(xs_ys,VALS[t]);

        for (int i = 0; i < 3; i++){
            int k = T.get(i);

            // Calcul de la contribution
            double res = 0;

            for (int r = 0; r < 3; r++){
                int j = T.get(r);

                // aT = Diff + Reac
                double PROD2 = D[r][i]+R[r][i];
                res += V[j] * PROD2;
            }

            W[k] += res;
        }
    }

    return W;
}
