#include <iostream>



// #include <vector>
#include <tuple>

#include "main.cpp"

using namespace std;

// Test numgb



bool test_numgb(int N,int M, int i, int j,int sol_attendue){
    return numgb(N,M,i,j) == sol_attendue;
}

bool test_invnumgb(int N, int M, int s, tuple<int,int> sol_attendue){
    return invnumgb(N,M,s) == sol_attendue;
}


// bool test_maillageTR(int N,int M, vector<Triangle> sol_attendue){
//     return maillageTR(N,M) == sol_attendue;
// }



bool test_CoordsTrig(double a, double b, int N, int M, Triangle T,
    tuple<vector<double>,vector<double>> sol_attendue){

    return CoordsTrig(a,b,N,M,T) == sol_attendue;
}


bool test_CalcMatBT(vector<double> xs, vector<double> ys,
    vector<vector<double>> sol_attendue){

    return CalcMatBT(xs,ys) == sol_attendue;
}

bool test_integ_eta_triang(double (* eta)(double,double),
    vector<Triangle> maillage,int N, int M,double a,double b,
    vector<double> sol_attendue){

    return integ_eta_triang(eta,maillage,N,M,a,b) == sol_attendue;
}



int main(){
    cout << "--------------Tests numgb--------------\n";

    if (test_numgb(2, 2, 1, 1,4)){
        cout << "Test 1 : réussi !" ;
    } else {
        cout << "Test 1 : échoué !" ;
    }

    cout << "\n\n\n";
    cout << "--------------Tests invnumgb--------------\n";


    if (test_invnumgb(2, 2,3,{1,1})){
        cout << "Test 1 : réussi !" ;
    } else {
        cout << "Test 1 : échoué !" ;
    }



    cout << "\n\n\n";
    cout << "--------------Tests maillageTR--------------\n";

    cout << "Aucun test n'a été écrit pour cette section pour le moment...\n";





    cout << "\n\n\n";
    cout << "--------------Tests CoordsTrig--------------\n";

    cout << "Aucun test n'a été écrit pour cette section pour le moment...\n";





    cout << "\n\n\n";
    cout << "--------------Tests CalcMatBT--------------\n";

    vector<double> xs = {0.0, 2.0, 0.0};
    vector<double> ys = {0.0, 0.0, 2.0};

    vector<vector<double>> sol_attendue = {{2.,0.},{0.,2.}};

    if (test_CalcMatBT(xs,ys,sol_attendue)){
        cout << "Test 1 : réussi !" ;
    } else {
        cout << "Test 1 : échoué !" ;
    }







    cout << "\n\n\n";
    cout << "--------------Tests integ_eta_triang--------------\n";

    cout << "Aucun test n'a été écrit pour cette section pour le moment...\n";

}