#include "triangle.hpp"

Triangle::Triangle(int n1, int n2, int n3){
    this->n1 = n1;
    this->n2 = n2;
    this->n3 = n3;
}


int Triangle::get(int k){
    switch (k){
        case 0 : return this->n1;
        case 1 : return this->n2;
        case 2 : return this-> n3;
        default : return -1;
    }
}