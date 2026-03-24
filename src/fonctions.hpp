#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <tuple>
#include <vector>


#include "fonctions.hpp"
#include "triangle.hpp"

using namespace std;

typedef vector<vector<double>> matrix;
typedef tuple<vector<double>,vector<double>> duplix;
typedef vector<Triangle> maillage;

vector<double> Subdiv(double a, int N);

int numgb(int N, int M, int i, int j);

tuple<int,int> invnumgb(int N, int M,int s);

maillage maillageTR(int N, int M);

duplix CoordsTrig(double a, double b, int N,int M, Triangle T);

matrix CalcMatBT(vector<double> xs, vector<double> ys);

vector<double> integ_eta_triang(double (* eta)(double,double),
    maillage TRG,int N, int M,double a,double b);

matrix DiffTerm(duplix xs_ys, double val);

matrix ReacTerm(duplix xs_ys);

vector<double> matvec(vector<double> V, maillage TRG, int N, int M,
    double a, double b, double (* eta)(double,double));

#endif


