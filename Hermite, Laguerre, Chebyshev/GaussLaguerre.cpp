//
//  GaussLaguerre.cpp
//  Numerical Methods 2
//
//  Created by Leonardo Linhares on 16/04/2016.
//  Copyright © 2016 Leonardo Linhares. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <iomanip>


using namespace std;

class GaussLaguerre{

private:
    double f(double x);
    struct weights;
    struct points;
    double loop(const double p[], const double w[], int numberOfPoints);

public:
    double calculate(int numberOfPoints);

};

// Retorna o valor da funcao f(x) = x^2
double GaussLaguerre::f(double x){
    return pow(x,2);
}


// Estrutura com os pesos de Gauss-Laguerre
struct GaussLaguerre::weights{
    // double n1[1] = {2};
    double n2[2] = {0.853553,0.146447};
    double n3[3] = {0.711093, 0.278518, 0.0103893};
    double n4[4] = {0.603154,0.357419, 0.0388879, 0.000539295};
    double n5[5] = {0.521756, 0.398667, 0.0759424, 0.00361176, 0.00002337};
    double n6[6] = {0.45896467394996,0.4170008307721,0.113373382074,0.0103991974531,
      2.610172028149E-4,8.9854790643E-7};
};

// Estrutura com os pontos de Gauss-Laguerre
struct GaussLaguerre::points{
    // double p1[1] = {0};
    double p2[2] = {0.585786,3.41421};
    double p3[3] = {0.415775,2.29428,6.28995};
    double p4[4] = {0.322548, 1.74576, 4.53662, 9.39507 };
    double p5[5] = {0.26356, 1.4134, 3.59643, 7.08581, 12.6408};
    double p6[6] = {0.22284660417926,1.1889321016726,2.9927363260593,5.7751435691045,
      9.8374674183826,15.982873980602};
};



double GaussLaguerre::loop(const double p[], const double w[], int numberOfPoints){
    double aux = 0;
    for (int j = 0; j < numberOfPoints; j++) {
        aux = aux + f(p[j])*w[j];
    }
    return aux;
}

// Funcao que aplica os pesos das formulas de Gauss-Laguerre a partir do numero de pontos requisitado pelo usuario
double GaussLaguerre::calculate(int numberOfPoints){
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
    GaussLaguerre gl;
    cout << setprecision(10) << fixed;

    cout << "Digite o numero de pontos de Laguerre (2-6):\n";
    while(!(cin >> numberOfPoints)) {
        cin.clear();
        cin.ignore(999,'\n');
        cout << "Valor invalido. Digite novamente o grau:\n";
    }
    
    double result = gl.calculate(numberOfPoints);
    cout << "Resultado final Gauss-Laguerre com " << numberOfPoints << " pontos: " << result << endl;
    return 0;
}

// C++ 11
// clang++ -std=c++11 -stdlib=libc++ GaussLaguerre.cpp
