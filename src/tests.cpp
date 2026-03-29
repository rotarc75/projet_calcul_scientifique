#include <cmath>
#include <iostream>

#include "fonctions.hpp"

using namespace std;


// Code ANSI des couleurs
const string VERT = "\033[32m";
const string ROUGE = "\033[31m";
const string BLANC = "\033[0m";


void test_numgb(int &k, int N,int M, int i, int j,int sol_attendue){
    int sol_obtenue = numgb(N,M,i,j);

    if (sol_obtenue == sol_attendue){
        cout << VERT << "Test "<<k<<" : réussi !\n"<< BLANC ;
    } else {
        cout << ROUGE << "Test "<<k<<" : échoué !\n" << BLANC ;
        cout << "   Résultat obtenu : " << sol_obtenue << endl;
        cout << "   Résultat attendu : " << sol_attendue << endl;
    }
    k++;
}


void test_invnumgb(int &k, int N, int M, int s, tuple<int,int> sol_attendue){
    tuple<int,int> sol_obtenue = invnumgb(N,M,s);

    if (sol_obtenue == sol_attendue){
        cout << VERT << "Test "<<k<<" : réussi !\n" << BLANC;
    } else {
        cout << ROUGE << "Test "<<k<<" : échoué !\n" << BLANC;
        cout << "Résultat obtenu : (" << get<0>(sol_obtenue)<<","<<get<1>(sol_obtenue) << ")\n";
        cout << "Résultat attendu : (" << get<0>(sol_attendue)<<","<<get<1>(sol_attendue) << ")\n";
    }
    k++;
}


void test_maillageTR(int &k, int N, int M, vector<Triangle> sol_attendue){
    vector<Triangle> sol_obtenue = maillageTR(N,M);

    int K = 2*N*M;
    bool reussi = true;

    for (int i = 0; i < K; i++){
        if (!(sol_obtenue[i] == sol_attendue[i])){
            reussi = false;
            break;
        }
    }

    if (reussi){
        cout << VERT << "Test "<<k<<" : réussi !\n" << BLANC;
    } else {
        cout << ROUGE << "Test "<<k<<" : échoué !\n" << BLANC;
        cout << "   Pas d'affichage de debug pour le moment.\n";
    }
    k++;

}


void test_CoordsTrig(int &num_test, double a, double b, int N, int M, Triangle T,
    tuple<vector<double>,vector<double>> sol_attendue){

    auto sol_obtenue = CoordsTrig(a,b,N,M,T);
    int L = get<0>(sol_attendue).size();
    auto xs_attendu = get<0>(sol_attendue);
    auto ys_attendu = get<1>(sol_attendue);
    auto xs_obtenu = get<0>(sol_obtenue);
    auto ys_obtenu = get<1>(sol_obtenue);
    bool correct_xs = true;
    bool correct_ys = true;

    for (int k = 0; k < L; k++){
        if (correct_xs && xs_attendu[k] != xs_obtenu[k]) correct_xs = false;
        if (correct_ys && ys_attendu[k] != ys_obtenu[k]) correct_ys = false;
    }

    if (correct_xs && correct_ys){
        cout << VERT << "Test "<< num_test<<" : réussi !\n" << BLANC;
    } else {
        cout << ROUGE << "Test "<<num_test<<" : échoué !\n" << BLANC;
        if (correct_ys){
            cout << "Il y a un soucis avec au moins une composante en x.\n";
        }
        if (correct_xs){
            cout << "Il y a un soucis avec au moins une composante en y.\n";
        }
    }

    num_test++;
}


void test_CalcMatBT(int &num_test, vector<double> xs, vector<double> ys,
    matrix sol_attendue){

    auto sol_obtenue = CalcMatBT(xs,ys);
    bool reussi = true;

    for (int l = 0; l < 2; l++){
        for (int c = 0; c < 2; c++){
            if (sol_obtenue[l][c] != sol_attendue[l][c]){
                reussi = false;
                break;
            }
        }
    }

    if (reussi){
        cout << VERT << "Test "<<num_test<<" : réussi !\n" << BLANC;
    } else {
        cout << ROUGE << "Test "<<num_test<<" : échoué !\n" << BLANC;
        cout << "   Pas d'affichage de debug pour le moment.\n";
    }

    num_test++;
}


void test_integ_eta_triang(int &num_test, double (* eta)(double,double),
    vector<Triangle> maillage,int N, int M,double a,double b,
    vector<double> sol_attendue){

    int K = 2*N*M;
    bool reussi = true;
    vector<double> sol_obtenue = integ_eta_triang(eta,maillage,N,M,a,b);
    double epsilon = 1e-9;

    for (int k = 0; k < K; k++){
        if (abs(sol_attendue[k] - sol_obtenue[k]) > epsilon){
            reussi = false;

            break;
        }
    }

    if (reussi){
        cout << VERT << "Test "<<num_test<<" : réussi !\n" << BLANC;
    } else {
        cout << ROUGE << "Test "<<num_test<<" : échoué !\n" << BLANC;
        cout << "   Pas d'affichage de debug pour le moment.\n";
    }

    num_test++;
}


void test_DiffTerm(int &num_test,duplix xs_ys, double val, matrix sol_attendue){

    matrix sol_obtenue = DiffTerm(xs_ys,val);
    bool reussi = true;
    double epsilon = 0.0000001;

    for (int l = 0; l < 3; l++){
        for (int c = 0; c < 3; c++){
            if (abs(sol_obtenue[l][c] - sol_attendue[l][c]) > epsilon){
                reussi = false;
                break;
            }
        }
    }

    if (reussi){
        cout << VERT << "Test "<<num_test<<" : réussi !\n" << BLANC;
    } else {
        cout << ROUGE << "Test "<<num_test<<" : échoué !\n" << BLANC;
        cout << "   Pas d'affichage de debug pour le moment.\n";
    }

    num_test++;
}


void test_ReacTerm(int &num_test,duplix xs_ys, matrix sol_attendue){

    matrix sol_obtenue = ReacTerm(xs_ys);
    bool reussi = true;
    double epsilon = 0.0000001;

    for (int l = 0; l < 3; l++){
        for (int c = 0; c < 3; c++){
            if (abs(sol_obtenue[l][c] - sol_attendue[l][c]) > epsilon){
                reussi = false;
                break;
            }
        }
    }

    if (reussi){
        cout << VERT << "Test "<<num_test<<" : réussi !\n" << BLANC;
    } else {
        cout << ROUGE << "Test "<<num_test<<" : échoué !\n" << BLANC;
        cout << "   Pas d'affichage de debug pour le moment.\n";
    }

    num_test++;
}


void test_matvec(int &num_test, vector<double> V, vector<Triangle> maillage,
    int N, int M, double a, double b, double (* eta)(double,double),
    vector<double> sol_attendue){


    vector<double> sol_obtenue = matvec(V,maillage,N,M,a,b,eta);
    bool reussi = true;
    double epsilon = 0.0000001;
    int G = (N+1)*(M+1);

    for (int k = 0; k < G; k++){
        if (abs(sol_attendue[k] - sol_obtenue[k]) > epsilon){
            reussi = false;
            break;
        }
    }

    if (reussi){
        cout << VERT << "Test "<<num_test<<" : réussi !\n" << BLANC;
    } else {
        cout << ROUGE << "Test "<<num_test<<" : échoué !\n" << BLANC;
        cout << "   Pas d'affichage de debug pour le moment.\n";
    }

    num_test++;
}


void test_pdt_sc(int &num_test, vector<double> u, vector<double> v,
        double sol_attendue){

    if (pdt_sc(u,v) == sol_attendue){
        cout << VERT << "Test "<<num_test<<" : réussi !\n" << BLANC;
    } else {
        cout << ROUGE << "Test "<<num_test<<" : échoué !\n" << BLANC;
        cout << "   Pas d'affichage de debug pour le moment.\n";
    }
    num_test++;
}


void test_cl_vec(int &num_test,double lbd, vector<double> u, double mu,
    vector<double> v, vector<double> sol_attendue){

    vector<double> sol_obtenue = cl_vec(lbd,u,mu,v);
    bool reussi = true;
    int K = sol_attendue.size();
    double epsilon = 1e-9;

    for (int k = 0; k < K; k++){
        if (abs(sol_attendue[k] - sol_obtenue[k]) > epsilon){
            reussi = false;
            break;
        }
    }

    if (reussi){
        cout << VERT << "Test "<<num_test<<" : réussi !\n" << BLANC;
    } else {
        cout << ROUGE << "Test "<<num_test<<" : échoué !\n" << BLANC;
        cout << "   Pas d'affichage de debug pour le moment.\n";
    }

    num_test++;
}


void test_max_abs(int &num_test, vector<double> V, double sol_attendue){

    if (max_abs(V) == sol_attendue){
        cout << VERT << "Test "<<num_test<<" : réussi !\n" << BLANC;
    } else {
        cout << ROUGE << "Test "<<num_test<<" : échoué !\n" << BLANC;
        cout << "   Pas d'affichage de debug pour le moment.\n";
    }

    num_test++;
}


void test_scdmembre(int &num_test, double rhsf(double,double,int), int N, int M, maillage TRG, double a, double b, int m, vector<double> sol_attendue){


    vector<double> sol_obtenue = scdmembre(rhsf,N,M,TRG,a,b,m);
    bool reussi = true;
    int K = sol_attendue.size();
    double epsilon = 1e-9;

    for (int k = 0; k < K; k++){
        if (abs(sol_attendue[k] - sol_obtenue[k]) > epsilon){
            reussi = false;
            break;
        }
    }

    if (reussi){
        cout << VERT << "Test "<<num_test<<" : réussi !\n" << BLANC;
    } else {
        cout << ROUGE << "Test "<<num_test<<" : échoué !\n" << BLANC;
        cout << "   Pas d'affichage de debug pour le moment.\n";
    }

    num_test++;
}


void test_normL2(int &num_test,vector<double> V,maillage TRG, int N, int M, double a,
    double b, double sol_attendue){

    if (abs(normL2(V,TRG,N,M,a,b) - sol_attendue) < 1e-9){
        cout << VERT << "Test "<<num_test<<" : réussi !\n" << BLANC;
    } else {
        cout << ROUGE << "Test "<<num_test<<" : échoué !\n" << BLANC;
        cout << "   Pas d'affichage de debug pour le moment.\n";
    }

    num_test++;
}


void test_normL2Grad(int &num_test, vector<double> V, maillage TRG, int N, int M,
    double a, double b, double sol_attendue){

    if (abs(normL2Grad(V,TRG,N,M,a,b) - sol_attendue) < 1e-9){
        cout << VERT << "Test "<<num_test<<" : réussi !\n" << BLANC;
    } else {
        cout << ROUGE << "Test "<<num_test<<" : échoué !\n" << BLANC;
        cout << "   Pas d'affichage de debug pour le moment.\n";
    }

    num_test++;
}



void test_bicg_stab(int &num_test, vector<double> B,maillage TRG, int N, int M,
    double a, double b, double tol,int max_it, double (* eta) (double,double),
    vector<double> sol_attendue){

    vector<double> sol_obtenue = bicg_stab(B,TRG,N,M,a,b,tol,max_it,eta);
    bool reussi = true;
    int K = sol_attendue.size();
    double epsilon = 1e-9;

    for (int k = 0; k < K; k++){
        if (abs(sol_attendue[k] - sol_obtenue[k]) > epsilon){
            reussi = false;
            break;
        }
    }

    if (reussi){
        cout << VERT << "Test "<<num_test<<" : réussi !\n" << BLANC;
    } else {
        cout << ROUGE << "Test "<<num_test<<" : échoué !\n" << BLANC;
        cout << "   Pas d'affichage de debug pour le moment.\n";
    }

    num_test++;
}


double eta1(double x, double y) {
    return 1.0;
}

double eta2(double x, double y) {
    return x + 2.0 * y + 5.0;
}

double eta3(double x, double y) {
    return x * x + y * y + 1.0;
}

//fonction qui affiche un vector de double
void print_vector(vector<double> tab){
    cout << "[" ;
    int size = tab.size();
    for (int k = 0; k < size -1; k++) cout << tab[k] << ", ";
    cout << tab[size-1] << "]\n";
}



int main(){
    cout << "--------------Tests numgb--------------\n";

    int num_tests = 1;

    // Test 1,2
    test_numgb(num_tests,2, 2, 1, 1,4);
    test_numgb(num_tests,18, 50, 11, 31,600);


    cout << "\n\n\n";
    cout << "--------------Tests invnumgb--------------\n";

    // Test 3,4,5
    test_invnumgb(num_tests,2, 2,4,{1,1});
    test_invnumgb(num_tests,21, 3,45,{1,2});
    test_invnumgb(num_tests,101, 101,3923,{47,38});



    cout << "\n\n\n";
    cout << "--------------Tests maillageTR--------------\n";



    // Test 6 : N = 1, M = 1
    maillage maillage0(2);

    maillage0[0] = Triangle(0, 2, 3);
    maillage0[1] = Triangle(0, 1, 3);

    test_maillageTR(num_tests, 1, 1, maillage0);



    // Test 7 : N = 2, M = 1
    maillage maillage1(4);

    maillage1[0] = Triangle(0,3,4);
    maillage1[1] = Triangle(0,1,4);
    maillage1[2] = Triangle(1,2,4);
    maillage1[3] = Triangle(2,4,5);

    test_maillageTR(num_tests,2,1,maillage1);



    // Test 8: N = 3, M = 2
    vector<Triangle> maillage2(12);

    maillage2[0] = Triangle(0, 4, 5);
    maillage2[1] = Triangle(0, 1, 5);
    maillage2[2] = Triangle(1, 2, 5);
    maillage2[3] = Triangle(2, 5, 6);
    maillage2[4] = Triangle(2, 6, 7);
    maillage2[5] = Triangle(2, 3, 7);

    maillage2[6] = Triangle(4, 5, 8);
    maillage2[7] = Triangle(5, 8, 9);
    maillage2[8] = Triangle(5, 9, 10);
    maillage2[9] = Triangle(5, 6, 10);
    maillage2[10] = Triangle(6, 7, 10);
    maillage2[11] = Triangle(7, 10, 11);

    test_maillageTR(num_tests, 3, 2, maillage2);







    // Test 9 : N = 4, M = 2
    vector<Triangle> maillage3 = vector<Triangle>(16);

    maillage3[0] = Triangle(0, 5, 6);
    maillage3[1] = Triangle(0, 1, 6);
    maillage3[2] = Triangle(1, 6, 2);
    maillage3[3] = Triangle(2, 6, 7);
    maillage3[4] = Triangle(2, 7, 8);
    maillage3[5] = Triangle(2, 3, 8);
    maillage3[6] = Triangle(3, 4, 8);
    maillage3[7] = Triangle(4, 8, 9);

    maillage3[8] = Triangle(5, 6, 10);
    maillage3[9] = Triangle(6, 10, 11);
    maillage3[10] = Triangle(6, 11, 12);
    maillage3[11] = Triangle(6, 7, 12);
    maillage3[12] = Triangle(7, 8, 12);
    maillage3[13] = Triangle(8, 12, 13);
    maillage3[14] = Triangle(8, 13, 14);
    maillage3[15] = Triangle(8, 9, 14);

    test_maillageTR(num_tests,4,2,maillage3);



    // Test 10 : N = 4, M = 4
    vector<Triangle> maillage4(32);

    maillage4[0]  = Triangle(0, 5, 6);
    maillage4[1]  = Triangle(0, 1, 6);
    maillage4[2]  = Triangle(1, 2, 6);
    maillage4[3]  = Triangle(2, 6, 7);
    maillage4[4]  = Triangle(2, 7, 8);
    maillage4[5]  = Triangle(2, 3, 8);
    maillage4[6]  = Triangle(3, 4, 8);
    maillage4[7]  = Triangle(4, 8, 9);

    maillage4[8]  = Triangle(5, 6, 10);
    maillage4[9]  = Triangle(6, 10, 11);
    maillage4[10] = Triangle(6, 11, 12);
    maillage4[11] = Triangle(6, 7, 12);
    maillage4[12] = Triangle(7, 8, 12);
    maillage4[13] = Triangle(8, 12, 13);
    maillage4[14] = Triangle(8, 13, 14);
    maillage4[15] = Triangle(8, 9, 14);

    maillage4[16] = Triangle(10, 15, 16);
    maillage4[17] = Triangle(10, 11, 16);
    maillage4[18] = Triangle(11, 12, 16);
    maillage4[19] = Triangle(12, 16, 17);
    maillage4[20] = Triangle(12, 17, 18);
    maillage4[21] = Triangle(12, 13, 18);
    maillage4[22] = Triangle(13, 14, 18);
    maillage4[23] = Triangle(14, 18, 19);

    maillage4[24] = Triangle(15, 16, 20);
    maillage4[25] = Triangle(16, 20, 21);
    maillage4[26] = Triangle(16, 21, 22);
    maillage4[27] = Triangle(16, 17, 22);
    maillage4[28] = Triangle(17, 18, 22);
    maillage4[29] = Triangle(18, 22, 23);
    maillage4[30] = Triangle(18, 23, 24);
    maillage4[31] = Triangle(18, 19, 24);

    test_maillageTR(num_tests, 4, 4, maillage4);


    // Test 11 : N = 3, M = 3
    vector<Triangle> maillage5(18);

    maillage5[0] = Triangle(0, 4, 5);
    maillage5[1] = Triangle(0, 1, 5);
    maillage5[2] = Triangle(1, 2, 5);
    maillage5[3] = Triangle(2, 5, 6);
    maillage5[4] = Triangle(2, 6, 7);
    maillage5[5] = Triangle(2, 3, 7);

    maillage5[6] = Triangle(4, 5, 8);
    maillage5[7] = Triangle(5, 8, 9);
    maillage5[8] = Triangle(5, 9, 10);
    maillage5[9] = Triangle(5, 6, 10);
    maillage5[10] = Triangle(6, 7, 10);
    maillage5[11] = Triangle(7, 10, 11);

    maillage5[12] = Triangle(8, 12, 13);
    maillage5[13] = Triangle(8, 9, 13);
    maillage5[14] = Triangle(9, 10, 13);
    maillage5[15] = Triangle(10, 13, 14);
    maillage5[16] = Triangle(10, 14, 15);
    maillage5[17] = Triangle(10, 11, 15);

    test_maillageTR(num_tests, 3, 3, maillage5);


    cout << "\n\n\n";
    cout << "--------------Tests CalcMatBT--------------\n";


    // Test 12
    vector<double> xs1 = {0.0, 1.0, 0.0};
    vector<double> ys1 = {0.0, 0.0, 1.0};
    matrix BT1 = {{1.0, 0.0},{0.0, 1.0}};
    test_CalcMatBT(num_tests, xs1, ys1, BT1);


    // Test 13
    vector<double> xs2 = {1.0, 4.0, 2.0};
    vector<double> ys2 = {1.0, 2.0, 5.0};
    matrix BT2 = {{3.0, 1.0},{1.0, 4.0}};
    test_CalcMatBT(num_tests, xs2, ys2, BT2);


    // Test 14
    vector<double> xs3 = {1.0, 2.0, 3.0};
    vector<double> ys3 = {1.0, 2.0, 3.0};
    matrix BT3 = {{1.0, 2.0},{1.0, 2.0}};
    test_CalcMatBT(num_tests, xs3, ys3, BT3);



    cout << "\n\n\n";
    cout << "--------------Tests integ_eta_triang--------------\n";


    // Test 15 : eta (x,y) = 1
    int N1 = 2;
    int M1 = 2;

    maillage maillage2x2 =   maillageTR(N1,M1);
    vector<double> sol_attendue1(2*N1*M1, 0.5);

    test_integ_eta_triang(num_tests, eta1, maillage2x2, N1, M1, 1.0, 1.0, sol_attendue1);


    // Test 16 : eta(x,y) = x + 2y + 5
    maillage maillage1x1 =   maillageTR(1,1);
    vector<double> sol_attendue2 = {32./3., 28./3.};
    test_integ_eta_triang(num_tests, eta2, maillage1x1, 1, 1, 1.0, 1.0, sol_attendue2);


    // Test 17 : eta(x,y) = x² + y² + 1
    vector<double> sol_attendue3 = {10.0 / 3.0, 10.0 / 3.0};

    test_integ_eta_triang(num_tests, eta3, maillage1x1, 1, 1, 1.0, 1.0, sol_attendue3);


    cout << "\n\n\n";
    cout << "--------------Tests DiffTerm--------------\n";


    // Test 18
    vector<double> xs4 = {0.0, 1.0, 0.0};
    vector<double> ys4 = {0.0, 0.0, 1.0};
    duplix T1 = {xs4, ys4};
    double val1 = 0.5;

    matrix sol_attendue4 =  {
        { 1.0, -0.5, -0.5},
        {-0.5,  0.5,  0.0},
        {-0.5,  0.0,  0.5}
    };

    test_DiffTerm(num_tests, T1, val1, sol_attendue4);


    // Test 19
    vector<double> xs5 = {0.0, 2.0, 1.0};
    vector<double> ys5 = {0.0, 0.0, 1.0};
    duplix T2 = {xs5, ys5};
    double val2 = 1.0;

    matrix sol_attendue5 = {
        { 0.5,  0.0, -0.5},
        { 0.0,  0.5, -0.5},
        {-0.5, -0.5,  1.0}
    };

    test_DiffTerm(num_tests, T2, val2, sol_attendue5);


    // Test 20
    vector<double> xs6 = {1.0, 3.0, 1.0};
    vector<double> ys6 = {1.0, 1.0, 4.0};
    duplix T3 = {xs6, ys6};
    double val3 = 3.0;

    matrix sol_attendue6 = {
        { 13.0/12.0, -0.75, -1.0/3.0 },
        { -0.75,      0.75,  0.0 },
        { -1.0/3.0,   0.0,   1.0/3.0 }
    };

    test_DiffTerm(num_tests, T3, val3, sol_attendue6);



    cout << "\n\n\n";
    cout << "--------------Tests ReacTerm--------------\n";


    // Test 21 : triangle de référence
    vector<double> xs7 = {0.0, 1.0, 0.0};
    vector<double> ys7 = {0.0, 0.0, 1.0};
    duplix T4 = {xs7, ys7};

    matrix sol_attendue7 = {
        { 1.0/12.0, 1.0/24.0, 1.0/24.0 },
        { 1.0/24.0, 1.0/12.0, 1.0/24.0 },
        { 1.0/24.0, 1.0/24.0, 1.0/12.0 }
    };

    test_ReacTerm(num_tests, T4, sol_attendue7);


    // Test 22
    vector<double> xs8 = {1.0, 3.0, 1.0};
    vector<double> ys8 = {1.0, 1.0, 4.0};
    duplix T5 = {xs8, ys8};

    matrix sol_attendue8 = {
        { 0.50, 0.25, 0.25 },
        { 0.25, 0.50, 0.25 },
        { 0.25, 0.25, 0.50 }
    };

    test_ReacTerm(num_tests, T5, sol_attendue8);


    // Test 23
    vector<double> xs9 = {-100.0, 500.0, 0.0};
    vector<double> ys9 = {-50.0, -50.0, 1000.0};
    duplix T6 = {xs9, ys9};

    matrix sol_attendue9 = {
        { 52500.0, 26250.0, 26250.0 },
        { 26250.0, 52500.0, 26250.0 },
        { 26250.0, 26250.0, 52500.0 }
    };

    test_ReacTerm(num_tests, T6, sol_attendue9);


    cout << "\n\n\n";
    cout << "--------------Tests matvec--------------\n";

    // Test 24
    vector<double> V = {0.0, 0.0, 0.0, 0.0};
    vector<double> sol_attendue10 = {0.0, 0.0, 0.0, 0.0};
    test_matvec(num_tests, V, maillage1x1, 1,1,1.0,1.0,eta1,sol_attendue10);


    // Test 25
    vector<double> V1 = {1.0, 1.0, 1.0, 1.0};
    vector<double> sol_attendue11 = {4.0 / 3.0, 2.0 / 3.0, 2.0 / 3.0, 4.0 / 3.0};
    test_matvec(num_tests, V1, maillage1x1, 1, 1, 1.0, 1.0, eta1, sol_attendue11);

    // Test 26
    vector<double> V2 = {1.0, 0.0, 0.0, 0.0};
    vector<double> sol_attendue12 = {5.0 / 3.0, -1.0 / 3.0, -1.0 / 3.0, 1.0 / 3.0};
    test_matvec(num_tests, V2, maillage1x1, 1, 1, 1.0, 1.0, eta1, sol_attendue12);


    cout << "\n\n\n";
    cout << "--------------Tests pdt_sc--------------\n";

    // Test 27
    vector<double> U3 = {1.0, 2.0, 3.0};
    vector<double> V3 = {4.0, -5.0, 6.0};
    test_pdt_sc(num_tests, U3, V3, 12.0);


    // Test 28
    vector<double> U4 = {1.0, 0.0, -1.0};
    vector<double> V4 = {0.0, 1.0, 0.0};
    test_pdt_sc(num_tests, U4, V4, 0.0);

    // Test 29
    vector<double> U5 = {0.0, 0.0, 0.0};
    vector<double> V5 = {7.5, -3.14, 42.0};
    test_pdt_sc(num_tests, U5, V5, 0.0);

    // Test 30
    vector<double> U6 = {0.5, 0.25, 1.5};
    vector<double> V6 = {2.0, 4.0, -2.0};
    test_pdt_sc(num_tests, U6, V6, -1.0);


    cout << "\n\n\n";
    cout << "--------------Tests cl_vec--------------\n";

    // Test 31
    vector<double> U7 = {1.0, 2.0, 3.0};
    vector<double> V7 = {4.0, 5.0, 6.0};
    vector<double> sol_attendue13 = {14.0, 19.0, 24.0};
    test_cl_vec(num_tests, 2.0, U7, 3.0, V7, sol_attendue13);

    // Test 32
    vector<double> U8 {1.5, -2.5};
    vector<double> V8 = {1.5, -2.5};
    vector<double> sol_attendue14 = {0.0, 0.0};
    test_cl_vec(num_tests, 1.0, U8, -1.0, V8, sol_attendue14);

    // Test 33
    vector<double> U9 = {10.0, 20.0};
    vector<double> V9 = {30.0, 40.0};
    vector<double> sol_attendue15= {0.0, 0.0};
    test_cl_vec(num_tests, 0.0, U9, 0.0, V9, sol_attendue15);


    // Test 34
    vector<double> U10 = {1.0, 3.0};
    vector<double> V10 = {4.0, -8.0};
    vector<double> sol_attendue16 = {1.5, -0.5};
    test_cl_vec(num_tests, 0.5, U10, 0.25, V10, sol_attendue16);




    cout << "\n\n\n";
    cout << "--------------Tests max_abs--------------\n";

    // Test 35
    vector<double> V11 = {1.5, -2.0, 3.5, -1.0};
    test_max_abs(num_tests, V11, 3.5);

    // Test 36
    vector<double> V12 = {4.0, -7.2, 3.1, 5.0};
    test_max_abs(num_tests, V12, 7.2);

    // Test 37
    vector<double> V13 = {0.0, 0.0, 0.0};
    test_max_abs(num_tests, V13, 0.0);



    cout << "\n\n\n";
    cout << "--------------Tests scdmembre--------------\n";




    // Test 38
    vector<double> sol_attendue17(11*15, 0.0);
    auto f0 = [](double,double,int){return 0.;};
    maillage maillage10x14 = maillageTR(10,14);
    test_scdmembre(num_tests, f0 , 10, 14, maillage10x14, 1., 1., 1, sol_attendue17);



    // Test 39
    auto f1 = [](double,double,int){return 1.0;};
    double aire_T = (2.0 * 2.0) / 6.0;
    vector<double> sol_attendue18 = {2*aire_T,aire_T,aire_T,2*aire_T};
    test_scdmembre(num_tests, f1, 1, 1, maillage1x1, 1.0, 1.0, 1, sol_attendue18);



    cout << "\n\n\n";
    cout << "--------------Tests normL2--------------\n";

    int N2 = 2, M2 = 2;
    double a = 1.0, b = 1.0;
    int G = (N2 + 1) * (M2 + 1);


    // Test 40
    vector<double> V14(G, 0.0);
    test_normL2(num_tests, V14, maillage2x2, N2, M2, a, b, 0.0);

    // Test 41
    vector<double> V15(G, 1.0);
    test_normL2(num_tests, V15, maillage2x2, N2, M2, a, b, 2.0);

    // Test42
    vector<double> V16(G, 0.0);
    for (int s = 0; s < G; s++) {
        tuple<int,int> coord = invnumgb(N2, M2, s);
        V16[s] = -a + (2.0 * a) / N2 * get<0>(coord);
    }

    test_normL2(num_tests, V16, maillage2x2, N2, M2, a, b, sqrt(4.0 / 3.0));


    cout << "\n\n\n";
    cout << "--------------Tests normL2Grad--------------\n";


    // Test 43
    test_normL2Grad(num_tests, V15, maillage2x2, N2, M2, a, b, 0.0);

    // Test 44
    test_normL2Grad(num_tests, V16, maillage2x2, N2, M2, a, b, 2.0);

    vector<double> V17(G, 0.0);
    for (int s = 0; s < G; s++) {
        tuple<int,int> coord = invnumgb(N2, M2, s);
        double x_noeud = -a + (2.0 * a) / N2 * get<0>(coord);
        double y_noeud = -b + (2.0 * b) / M2 * get<1>(coord);
        V17[s] = x_noeud + y_noeud;
    }

    // Test 45
    test_normL2Grad(num_tests, V17, maillage2x2, N2, M2, a, b, sqrt(8.0));



    cout << "\n\n\n";
    cout << "--------------Test bicg_stab--------------\n";


    // Test 46
    int N3 = 2, M3 = 2;
    double a3 = 1.0, b3 = 1.0;
    int G3 = (N3 + 1) * (M3 + 1);

    vector<double> sol_exacte = {8.,-3.,6.,-9.81,3.14,2.72,7.1,4.2,-5.3};


    vector<double> B = matvec(sol_exacte, maillage2x2, N3, M3, a3, b3, eta1);

    double tol = 1e-10;
    int max_it = 2000;


    test_bicg_stab(num_tests, B, maillage2x2, N3, M3, a3, b3, tol, max_it, eta1, sol_exacte);

}


