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


// bool test_CoordsTrig(double a, double b, int N, int M, Triangle T,
//     tuple<vector<double>,vector<double>> sol_attendue){

//     return CoordsTrig(a,b,N,M,T) == sol_attendue;
// }


// bool test_CalcMatBT(vector<double> xs, vector<double> ys,
//     vector<vector<double>> sol_attendue){

//     return CalcMatBT(xs,ys) == sol_attendue;
// }

// bool test_integ_eta_triang(double (* eta)(double,double),
//     vector<Triangle> maillage,int N, int M,double a,double b,
//     vector<double> sol_attendue){

//     return integ_eta_triang(eta,maillage,N,M,a,b) == sol_attendue;
// }



int main(){
    cout << "--------------Tests numgb--------------\n";

    int num_tests = 1;

    test_numgb(num_tests,2, 2, 1, 1,4);
    test_numgb(num_tests,18, 50, 11, 31,600);


    cout << "\n\n\n";
    cout << "--------------Tests invnumgb--------------\n";


    test_invnumgb(num_tests,2, 2,4,{1,1});
    test_invnumgb(num_tests,21, 3,45,{1,2});
    test_invnumgb(num_tests,101, 101,3923,{47,38});



    cout << "\n\n\n";
    cout << "--------------Tests maillageTR--------------\n";



    // Test pour N = 1, M = 1
    vector<Triangle> maillage(2);

    maillage[0] = Triangle(0, 2, 3);
    maillage[1] = Triangle(0, 1, 3);

    test_maillageTR(num_tests, 1, 1, maillage);



    // Test pour N = 2, M = 1
    vector<Triangle> maillage1 = vector<Triangle>(4);

    maillage1[0] = Triangle(0,3,4);
    maillage1[1] = Triangle(0,1,4);
    maillage1[2] = Triangle(1,2,4);
    maillage1[3] = Triangle(2,4,5);

    test_maillageTR(num_tests,2,1,maillage1);



    // Test pour N = 3, M = 2
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







    // Test pour N = 4, M = 2
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



    // Test pour N = 4, M = 4
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


    // Test pour N = 3, M = 3
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
    cout << "--------------Tests CoordsTrig--------------\n";

    cout << "Aucun test n'a été écrit pour cette section pour le moment...\n";





    cout << "\n\n\n";
    cout << "--------------Tests CalcMatBT--------------\n";



    cout << "Aucun test n'a été écrit pour cette section pour le moment...\n";






    cout << "\n\n\n";
    cout << "--------------Tests integ_eta_triang--------------\n";

    cout << "Aucun test n'a été écrit pour cette section pour le moment...\n";


}


