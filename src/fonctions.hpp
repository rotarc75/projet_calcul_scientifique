#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <tuple>
#include <vector>

#include "fonctions.hpp"
#include "triangle.hpp"

using namespace std;


vector<double> Subdiv(double a, int N);

int numgb(int N, int M, int i, int j);

tuple<int,int> invnumgb(int N, int M,int s);

vector<Triangle> maillageTR(int N, int M);

tuple<vector<double>,vector<double>> CoordsTrig(double a, double b, int N,int M, Triangle T);

vector<vector<double>> CalcMatBT(vector<double> xs, vector<double> ys);

vector<double> integ_eta_triang(double (* eta)(double,double),vector<Triangle> maillage,int N, int M,double a,double b);

vector<vector<double>> DiffTerm(tuple<vector<double>,vector<double>> xs_ys, double val);

vector<vector<double>> ReacTerm(tuple<vector<double>,vector<double>> xs_ys, double val);

#endif


