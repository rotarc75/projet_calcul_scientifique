#include "triangle.hpp"


Triangle::Triangle(int n1, int n2, int n3){
    this->n1 = n1;
    this->n2 = n2;
    this->n3 = n3;
}


Triangle::Triangle(){
    this->n1 = 0;
    this->n2 = 0;
    this->n3 = 0;
}


int Triangle::get(int k){
    switch (k){
        case 0 : return this->n1;
        case 1 : return this->n2;
        case 2 : return this-> n3;
        default : return -1;
    }
}

// Fonction qui renvoie le min de 3 entiers
int min3(int a, int b, int c) {
    int m = (a < b) ? a : b;
    return (m < c) ? m : c;
}


// Fonction qui renvoie le max de 3 entiers
int max3(int a, int b, int c) {
    int m = (a > b) ? a : b;
    return (m > c) ? m : c;
}


// Surcharge de l'opérateur == pour définir l'égalité de triangles
bool Triangle::operator==(const Triangle &t) const {
    int min1 = min3(n1,n2,n3);
    int max1 = max3(n1,n2,n3);
    int mid1 = n1 + n2 + n3 - min1 - max1;

    int min2 = min3(t.n1,t.n2,t.n3);
    int max2 = max3(t.n1,t.n2,t.n3);
    int mid2 = t.n1 + t.n2 + t.n3 - min2 - max2;

    return min1==min2 && mid1==mid2 && max1==max2;
}