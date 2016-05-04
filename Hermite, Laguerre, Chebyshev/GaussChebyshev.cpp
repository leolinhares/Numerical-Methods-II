//
//  GaussChebyshev.cpp
//  Numerical Methods 2
//
//  Created by Leonardo Linhares on 16/04/2016.
//  Copyright © 2016 Leonardo Linhares. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <iomanip>


using namespace std;

class GaussChebyshev{

private:
    double f(double x);    
   
public:
    double loop(int numberOfPoints);

};

// Retorna o valor da funcao f(x) = e^-(x)*x^2
double GaussChebyshev::f(double x){
    return exp(x);
}


double GaussChebyshev::loop(int numberOfPoints){
    double aux = 0;
    double w = M_PI/numberOfPoints;

    for (int j = 1; j <= numberOfPoints; j++) {
        aux = aux + f(cos((j-0.5)*M_PI/numberOfPoints))*w;
    }
    return aux;
}



int main(int argc, const char * argv[]) {
    double a,b;
    double error;
    int numberOfPoints;
    GaussChebyshev gc;
    cout << setprecision(10) << fixed;


    cout << "Digite o numero de pontos de Chebyshev [1-N]:\n";
    while(!(cin >> numberOfPoints)) {
        cin.clear();
        cin.ignore(999,'\n');
        cout << "Valor invalido. Digite novamente o numero de pontos:\n";
    }
    
    double result = gc.loop(numberOfPoints);
    cout << "Resultado final GaussChebyshev com " << numberOfPoints << " pontos: " << result << endl;
    return 0;
}

// C++ 11
// clang++ -std=c++11 -stdlib=libc++ GaussChebyshev.cpp
