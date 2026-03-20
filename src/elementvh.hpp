#ifndef ELEMENTVH_H
#define ELEMENTVH_H

#include <vector>

using namespace std;

class ElementVh {

private:
    vector<double> valeurs_noeuds_interieurs;
    vector<double> valeurs_tous_noeuds;

    double normeL2, normeL2_grad;

public:
    ElementVh(vector<double> valeurs_noeuds_interieurs, vector<double> valeurs_tous_noeuds,
        double normeL2, double normeL2_grad);
    ElementVh();
    vector<double> get_noeuds_interieurs();
    vector<double> get_tous_noeuds();
    double get_norme();
    double get_norme_grad();
};

#endif
