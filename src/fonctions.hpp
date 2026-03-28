#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <tuple>
#include <vector>


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

vector<double> scdmembre(double rhsf(double,double, int), int N, int M, maillage TRG, double a, double b, int m);

double normL2(vector<double> V,maillage TRG, int N, int M, double a, double b);


double normL2Grad(vector<double> V, maillage TRG, int N, int M, double a, double b);

double pdt_sc(vector<double> u, vector<double> v);

vector<double> cl_vec(double lbd, vector<double> u, double mu, vector<double> v);

double max_abs(vector<double> V);

vector<double> bicg_stab(vector<double> B,maillage TRG, int N, int M, double a,
    double b, double tol,int max_it, double (* eta) (double,double));


vector<double> erreurs(double (* solExa) (double,double, int),vector<double> uh,maillage TRG, int N, int M, double a, double b, int m);