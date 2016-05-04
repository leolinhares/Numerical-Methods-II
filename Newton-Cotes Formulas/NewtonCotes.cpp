//
//  NewtonCotes.cpp
//  Integracao
//
//  Created by Leonardo Linhares on 24/03/2016.
//  Copyright © 2016 Leonardo Linhares. All rights reserved.
//

#include <iostream>
#include <cmath>

using namespace std;

class NewtonCotes{
    
    double f(double x);
    struct weights;
    double loop(int w[], int n, double h, double a);

public:
    double calculate(int numberOfPoints, double a, double b);
};


/*
 * Function:  f
 * --------------------
 * computes the value of f(x) where f is:
 *    f(x) = x^4 * cos(x + e^x)
 *
 *  returns: the value of f(x)
 */
double NewtonCotes::f(double x){
//    return (pow(x, 4)*cos(x+exp(x)));
    return pow(x, 3)+1;
}

struct NewtonCotes::weights{
    int first[2] = {1,1};
    int second[3] = {1, 4, 1};
    int third[4] = {1, 3, 3, 1};
    int forth[5] = {7, 32, 12, 32, 7};
    int fifth[6] = {19, 75, 50, 50, 75, 19};
    int sixth[7] = {41, 216, 27, 272, 27, 216, 41};
    int seventh[8] = {751, 3577, 1323, 2989, 2989, 1323, 3577, 751};
};

double NewtonCotes::loop(int w[], int n, double h, double a){
    double aux = 0;
    double xi = 0;
    for (int p = 0; p <= n; p++) {
        xi = a + p*h;
        aux = aux + f(xi)*w[p];
    }
    return aux;
}

double NewtonCotes::calculate(int n, double a, double b){
    double h = (b-a)/n;
    double i = 0;
    weights w;
    double aux = 0;
    switch (n) {
        case 1:
            aux = loop(w.first, n, h, a);
            i = h/2*aux;
            break;
        case 2:
            aux = loop(w.second, n, h, a);
            i = h/3*aux;
            break;
        case 3:
            aux = loop(w.third, n, h, a);
            i = 3*h/8*aux;
            break;
        case 4:
            aux = loop(w.forth, n, h, a);
            i = 2*h/45*aux;
            break;
        case 5:
            aux = loop(w.fifth, n, h, a);
            i = 5*h/288*aux;
            break;
        case 6:
            aux = loop(w.sixth, n, h, a);
            i = 1*h/140*aux;
            break;
        case 7:
            aux = loop(w.seventh, n, h, a);
            i = 7*h/17280*aux;
            break;
        default:
            break;
    }
    return i;
}



int main(int argc, const char * argv[]) {
    double a,b;
    int grau;
    NewtonCotes nc;
    
    cout << "Digite o intervalo de integração inferior:\n";
    cin >> a;
    cout << "Digite o intervalo de integração superior:\n";
    cin >> b;
    cout << "Digite o grau do polinomio de interpolação (1-5):\n";
    cin >> grau;
    
    double result = nc.calculate(grau, a, b);
    cout << "Resultado final Newton Cotes grau " << grau << ": " << result << endl;
    return 0;
}


