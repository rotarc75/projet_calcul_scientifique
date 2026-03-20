#include "elementvh.hpp"

ElementVh::ElementVh(vector<double> valeurs_noeuds_interieurs, vector<double> valeurs_tous_noeuds,
        double normeL2, double normeL2_grad){
    this->valeurs_noeuds_interieurs = valeurs_noeuds_interieurs;
    this->valeurs_tous_noeuds = valeurs_tous_noeuds;
    this->normeL2 = normeL2;
    this->normeL2_grad = normeL2_grad;
}

ElementVh::ElementVh(){
    this->valeurs_noeuds_interieurs = vector<double>();
    this->valeurs_tous_noeuds = vector<double>();
    this->normeL2 = 0;
    this->normeL2_grad = 0;
}

vector<double> ElementVh::get_noeuds_interieurs(){
    return this->valeurs_noeuds_interieurs;
}

vector<double> ElementVh::get_tous_noeuds(){
    return this->valeurs_tous_noeuds;
}

double ElementVh::get_norme(){
    return this->normeL2;
}

double ElementVh::get_norme_grad(){
    return this->normeL2_grad;
}