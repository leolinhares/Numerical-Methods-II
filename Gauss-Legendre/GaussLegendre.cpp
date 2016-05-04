//
//  GaussLegendre.cpp
//  Numerical Methods 2
//
//  Created by Leonardo Linhares on 16/04/2016.
//  Copyright © 2016 Leonardo Linhares. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <iomanip>


using namespace std;

class GaussLegendre{

private:
    double f(double x);
    struct weights;
    struct points;
    double loop(double a, double b, const double p[], const double w[], int numberOfPoints);
    double calculate(double a, double b, int numberOfPoints);
    double calculateWithIntervals(double a, double b, int numberOfPoints, int intervals);

public:
    double execute(double a, double b, int numberOfPoints, double error);
};

// Retorna o valor da funcao f(x) = sen(x)
double GaussLegendre::f(double x){
    // return sin(x);
    return pow(x,11);
}

// Estrutura com os pesos de Gauss-Legendre
struct GaussLegendre::weights{
    double n1[1] = {2};
    double n2[2] = {1,1};
    double n3[3] = {0.888888889, 0.555555556, 0.555555556};
    double n4[4] = {0.652145155,0.652145155, 0.347854845, 0.347854845};
    double n5[5] = {0.568888889, 0.478628670, 0.478628670, 0.236926885, 0.236926885};
    double n6[6] = {0.467913935, 0.467913935, 0.360761573, 0.360761573, 0.171324492, 0.171324492};

};

// Estrutura com os pontos de Gauss-Legendre
struct GaussLegendre::points{
    double p1[1] = {0};
    double p2[2] = {0.577350269,-0.577350269};
    double p3[3] = {0, 0.774596669, -0.774596669};
    double p4[4] = {0.339981043, -0.339981043, 0.861136312, -0.861136312};
    double p5[5] = {0, 0.538469310, -0.538469310, 0.906179846, -0.906179846};
    double p6[6] = {0.238619186, -0.238619186, 0.661209387, -0.661209387, 0.952469514, -0.952469514};

};


double GaussLegendre::loop(double a, double b, const double p[], const double w[], int numberOfPoints){
    double aux = 0;
    double x = 0;
    for (int j = 0; j < numberOfPoints; j++) {
        x = (a+b)/2 + ((b-a)/2)*p[j]; //parametrizacao de s para x
        aux = aux + f(x)*w[j];
    }
    return 0.5*(b-a)*aux;
}

// Funcao que aplica os pesos das formulas de Gauss-Legendre a partir do numero de pontos requisitado pelo usuario
double GaussLegendre::calculate(double a, double b, int numberOfPoints){
    double i = 0;
    struct weights w;
    struct points p;
    switch (numberOfPoints) {
        case 1:
            i = loop(a, b, p.p1, w.n1, numberOfPoints);
            break;
        case 2:
            i = loop(a, b, p.p2, w.n2, numberOfPoints);
            break;
        case 3:
            i = loop(a, b, p.p3, w.n3, numberOfPoints);
             break;
        case 4:
            i = loop(a, b, p.p4, w.n4, numberOfPoints);
            break;
        case 5:
            i = loop(a, b, p.p5, w.n5, numberOfPoints);
            break;
        case 6:
            i = loop(a, b, p.p6, w.n6, numberOfPoints);
            break;
        default:
            break;
    }
    return i;
}

// Calcula iterativamente a integral a partir do numero de intervalos dados
double GaussLegendre::calculateWithIntervals(double a, double b, int numberOfPoints, int intervals){
    double i = 0;
    double h = (b-a)/intervals;
    for (int p = 0; p < intervals; p++) {
        i = i + calculate(a + h*p, a + h*(p+1), numberOfPoints);
    }
    return i;
}

// subdivide o intervalo (a,b) original ate que a formula de gauss-legendre
// retorne um valor com o erro estipulado
double GaussLegendre::execute(double a, double b, int numberOfPoints, double error){
    double e = 1000;
    double oldI = 0;
    double newI = 0;
    bool firstIteration = true;
    int intervals = 1;

    while (fabs(e) >= error){
        newI = calculateWithIntervals(a, b, numberOfPoints, intervals);
        if (!firstIteration) {
            e = (newI - oldI)/oldI;
        }
        oldI = newI;
        firstIteration = false;
        intervals = intervals*2;
    }

    return newI;
}



int main(int argc, const char * argv[]) {
    double a,b;
    double error;
    int numberOfPoints;
    GaussLegendre gl;
    cout << setprecision(10) << fixed;


    cout << "Digite o intervalo de integração inferior:\n";
    while(!(cin >> a)) {
        cin.clear();
        cin.ignore(999,'\n');
        cout << "Valor invalido. Digite novamente o intervalor de integracao inferior:\n";
    }
    cout << "Digite o intervalo de integração superior:\n";
    while(!(cin >> b)) {
        cin.clear();
        cin.ignore(999,'\n');
        cout << "Valor invalido. Digite novamente o intervalor de integracao superior:\n";
    }
    cout << "Digite o numero de pontos de Legendre (1-6):\n";
    while(!(cin >> numberOfPoints)) {
        cin.clear();
        cin.ignore(999,'\n');
        cout << "Valor invalido. Digite novamente o grau:\n";
    }
    cout << "Digite a tolerancia (potencia negativa de 10):\n";
    while(!(cin >> error)) {
        cin.clear();
        cin.ignore(999,'\n');
        cout << "Valor invalido. Digite novamente a tolerancia:\n";
    }
    double result = gl.execute(a, b, numberOfPoints, error);
    cout << "Resultado final Gauss-Legendre com " << numberOfPoints << " pontos: " << result << endl;
    return 0;
}

// C++ 11
// clang++ -std=c++11 -stdlib=libc++ GaussLegendre.cpp
