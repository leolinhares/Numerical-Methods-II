//
//  NewtonCotes.cpp
//  Numerical Methods 2
//
//  Created by Leonardo Linhares on 24/03/2016.
//  Copyright © 2016 Leonardo Linhares. All rights reserved.
//

#include <iostream>
#include <cmath>

using namespace std;

class NewtonCotes{
    
private:
    double f(double x);
    struct weights;
    double loop(const int w[], int n, double h, double a);
    double calculate(int numberOfPoints, double a, double b);
    double calculateWithIntervals(int grau, double a, double b, int intervals);

public:
    double execute(double a, double b, int grau, double error);
};

// Retorna o valor da funcao f(x) = x^3 + 3*x^2 + 12
double NewtonCotes::f(double x){
    return pow(x, 3)+3*pow(x,2) + 12;
}

// Estrutura com os pesos das fórmulas de Newton-Cotes entre 1 e 5
struct NewtonCotes::weights{
    int first[2] = {1,1};
    int second[3] = {1, 4, 1};
    int third[4] = {1, 3, 3, 1};
    int forth[5] = {7, 32, 12, 32, 7};
    int fifth[6] = {19, 75, 50, 50, 75, 19};
};

// Calcula o somatório de f(xi)*w(i) para i entre a e b
double NewtonCotes::loop(const int w[], int n, double h, double a){
    double aux = 0;
    double xi = 0; // ponto a ser calculado o valor da funcao
    for (int p = 0; p <= n; p++) {
        xi = a + p*h; // h é o intervalo, tamanho de cada pedaco no qual a funçao foi subdividida
        aux = aux + f(xi)*w[p];
    }
    return aux;
}

// Funcao que aplica os pesos das formulas de Newton-Cotes a parti do grau requisitado pelo usuario.
double NewtonCotes::calculate(int grau, double a, double b){
    double h = (b-a)/grau;
    double i = 0;
    struct weights w;
    double aux = 0;
    switch (grau) {
        case 1:
            aux = loop(w.first, grau, h, a);
            i = h/2*aux;
            break;
        case 2:
            aux = loop(w.second, grau, h, a);
            i = h/3*aux;
            break;
        case 3:
            aux = loop(w.third, grau, h, a);
            i = 3*h/8*aux;
            break;
        case 4:
            aux = loop(w.forth, grau, h, a);
            i = 2*h/45*aux;
            break;
        case 5:
            aux = loop(w.fifth, grau, h, a);
            i = 5*h/288*aux;
            break;
        default:
            break;
    }
    return i;
}

// Calcula iterativamente a integral a partir do numero de intervalos dados
double NewtonCotes::calculateWithIntervals(int grau, double a, double b, int intervals){
    double i = 0;
    double h = (b-a)/intervals;
    for (int p = 0; p < intervals; p++) {
        i = i + calculate(grau, a + h*p, a + h*(p+1));
    }
    return i;
}

// subdivide o intervalo (a,b) original ate que a formula de newton cotes
// retorne um valor com o erro estipulado
double NewtonCotes::execute(double a, double b, int grau, double error){
    double e = 1000;
    double oldI = 0;
    double newI = 0;
    bool firstIteration = true;
    int intervals = 1;
    
    while (fabs(e) >= error){
        newI = calculateWithIntervals(grau, a, b, intervals);
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
    int grau;
    NewtonCotes nc;
    
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
    cout << "Digite o grau do polinomio de interpolação (1-5):\n";
    while(!(cin >> grau)) {
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
    double result = nc.execute(a, b, grau, error);
    cout << "Resultado final Newton Cotes grau " << grau << ": " << result << endl;
    return 0;
}

// C++ 11
// clang++ -std=c++11 -stdlib=libc++ NewtonCotes.cpp
