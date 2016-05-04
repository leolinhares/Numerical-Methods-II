//
//  GaussHermite.cpp
//  Numerical Methods 2
//
//  Created by Leonardo Linhares on 16/04/2016.
//  Copyright © 2016 Leonardo Linhares. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <iomanip>


using namespace std;

class GaussHermite{

private:
    double f(double x);
    struct weights;
    struct points;
    double loop(const double p[], const double w[], int numberOfPoints);

public:
    double calculate(int numberOfPoints);

};

// Retorna o valor da funcao f(x) = x^2
double GaussHermite::f(double x){
    return pow(x,2);
}


// Estrutura com os pesos de Gauss-Hermite
struct GaussHermite::weights{
    // double n1[1] = {2};
    double n2[2] = {0.88622692,0.88622692};
    double n3[3] = {1.18163590, 0.29540897, 0.29540897};
    double n4[4] = {0.80491409,0.80491409, 0.08131283, 0.08131283};
    double n5[5] = {0.94530872, 0.39361932, 0.39361932, 0.01995324, 0.01995324};
    double n6[6] = {0.00453,0.157067,0.72463,0.72463,0.157067,0.00453};
};

// Estrutura com os pontos de Gauss-Hermite
struct GaussHermite::points{
    // double p1[1] = {0};
    double p2[2] = {0.70710678,-0.70710678};
    double p3[3] = {0, 1.22474487, -1.22474487};
    double p4[4] = {0.52464762, -0.52464762, 1.65068012, -1.65068012};
    double p5[5] = {0, 0.95857246, -0.95857246, 2.02018287, -2.02018287};
    double p6[6] = {-2.3506,-1.33585,-0.436077,0.436077,1.33585,2.3506};
};


double GaussHermite::loop(const double p[], const double w[], int numberOfPoints){
    double aux = 0;
    for (int j = 0; j < numberOfPoints; j++) {
        aux = aux + f(p[j])*w[j];
    }
    return aux;
}

// Funcao que aplica os pesos das formulas de Gauss-Hermite a partir do numero de pontos requisitado pelo usuario
double GaussHermite::calculate(int numberOfPoints){
    double i = 0;
    struct weights w;
    struct points p;
    switch (numberOfPoints) {
        // case 1:
        //     i = loop(a, b, p.p1, w.n1, numberOfPoints);
        //     break;
        case 2:
            i = loop(p.p2, w.n2, numberOfPoints);
            break;
        case 3:
            i = loop(p.p3, w.n3, numberOfPoints);
             break;
        case 4:
            i = loop(p.p4, w.n4, numberOfPoints);
            break;
        case 5:
            i = loop(p.p5, w.n5, numberOfPoints);
            break;
        case 6:
            i = loop(p.p6, w.n6, numberOfPoints);
            break;
        default:
            break;
    }
    return i;
}


int main(int argc, const char * argv[]) {
    double a,b;
    double error;
    int numberOfPoints;
    GaussHermite gh;
    cout << setprecision(10) << fixed;


    cout << "Digite o numero de pontos de Hermite (1-6):\n";
    while(!(cin >> numberOfPoints)) {
        cin.clear();
        cin.ignore(999,'\n');
        cout << "Valor invalido. Digite novamente o grau:\n";
    }
    
    double result = gh.calculate(numberOfPoints);
    cout << "Resultado final Gauss-Hermite com " << numberOfPoints << " pontos: " << result << endl;
    return 0;
}

// C++ 11
// clang++ -std=c++11 -stdlib=libc++ GaussHermite.cpp
