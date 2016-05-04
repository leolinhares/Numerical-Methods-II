//
//  exponential.cpp
//  Integracao
//
//  Created by Leonardo Linhares on 02/05/2016.
//  Copyright © 2016 Leonardo Linhares. All rights reserved.
//

#include <iostream>
#include <cmath>

using namespace std;

double f(double x){
   return 1/sqrt(x);
}

double trapezio(double a, double b, double error){
   double integral = 0;
   double aux = 0;
   double h, e, x,s;
   int i;
   int n = 1;
   e = 1000;
   double N = 15.0;

   while(e > error){
      aux = integral;
      integral = 0;
      h = (N+N)/n;
      for(i=0;i<n;i++){
         s = h/2 + h*i + -N;
         x = 0.5*(b+a)+ 0.5*(b-a)*tanh(s);
         integral = integral + h*f(x)/(pow(cosh(s),2));
      }
      n = n*2;
      e = abs(integral-aux);
   }
   return 0.5*(b-a)*integral;
}


int main(int argc, const char * argv[]) {
    double a,b,e;
    cout << "Digite o intervalo:\n";
    cin >> a >> b;
    cout << "Digite o erro:\n";
    cin >> e;
    double result = trapezio(a, b, e);
    cout << "Resultado final: " << result << endl;
    return 0;
}
