//
//  main.cpp
//  Integracao
//
//  Created by Leonardo Linhares on 15/03/2016.
//  Copyright © 2016 Leonardo Linhares. All rights reserved.
//

#include <iostream>
#include <cmath>

#define N 100 // Number of partitions

using namespace std;

/*
 * Function:  f
 * --------------------
 * computes the value of f(x) where f is:
 *    f(x) = x^4 * cos(x + e^x)
 *
 *  x: variable
 *
 *  returns: the value of f(x)
 */
double f(double x){
    return (pow(x, 4)*cos(x+exp(x)));
}


/*
 * Function:  integralCalculatorTrapeziumBase
 * --------------------
 * Calculating defined integral of a function by dividing
 * into "n" trapezoidal partitions
 *
 *  a: inferior limit of integration
 *  b: superior limit of integration
 *  n: number of partitions
 *
 *  returns: integral's value
 */
double integralCalculatorTrapeziumBase(double a, double b, int n){
    
    double i = 0; // Integral value
    double deltaX = (b-a)/n; // Size of each partition
    double xi; // Partition first point
    int p = 0; // Auxiliary variable (it represents each partition's index)
    
    for (p = 0; p < n; p++) {
        xi = a + p*deltaX;
        i = i + (0.5)*(f(xi)+f(xi+deltaX))*deltaX; // Cumulative sum of each trapezoidal area
    }
    return i;
}


/*
 * Function:  integralCalculatorBase
 * --------------------
 * Calculating defined integral of a function by dividing
 * into "n" retangular partitions
 *
 *  a: inferior limit of integration
 *  b: superior limit of integration
 *  n: number of partitions
 *
 *  returns: integral's value
 */
double integralCalculatorBase(double a, double b, int n){
    
    double i = 0; // Integral value
    double deltaX = (b-a)/n; // Size of each partition
    double xp; // Partition midpoint
    int p = 0; // Auxiliary variable (it represents each partition's index)
    
    for (p = 0; p < n; p++) {
        xp = deltaX/2 + deltaX*p + a;
        i = i + deltaX*f(xp); // Cumulative sum of each rectangular area
    }
    return i;
}

double method1(double a, double b){
    return integralCalculatorBase(a, b, N);
}

double method2(double a, double b){
    double e = 1000;
    double i = 0;
    double old = 0;
    int n = 1;
    while (abs(e) >= 0.001) {
        i = integralCalculatorBase(a, b, n);
        if (old != 0) {
            e = (i - old)/old;
        }
        old = i;
        n = n*2;
    }
    cout << "Number of iterations: " << n << endl;
    return i;
}

double method3(double a, double b){
    return integralCalculatorTrapeziumBase(a, b, N);
}

double method4(double a, double b){
    double e = 1000;
    double i = 0;
    double old = 0;
    int n = 1;
    while (abs(e) >= 0.001) {
        i = integralCalculatorTrapeziumBase(a, b, n);
        if (old != 0) {
            e = (i - old)/old;
        }
        old = i;
        n = n*2;
    }
    cout << "Number of iterations: " << n << endl;
    return i;
}

int main(int argc, const char * argv[]) {
    double a,b;
    cout << "Digite o intervalo:\n";
    cin >> a >> b;
    double result = method1(a, b);
    cout << "Resultado final: " << result << endl;
    double result2 = method2(a, b);
    cout << "Resultado final: " << result2 << endl;
    double result3 = method3(a, b);
    cout << "Resultado final: " << result3 << endl;
    double result4 = method4(a, b);
    cout << "Resultado final: " << result4 << endl;
    return 0;
}
