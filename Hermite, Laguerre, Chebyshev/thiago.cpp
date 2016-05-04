/* Implementar e testar a quadratura de Gauss-Hermite para integração adequada a esse tipo de quadratura.
O método que retorna o valor da função para um dado x deve ser programado e incorporado ao código.
A entrada de dados deve ser:
1) o número de pontos de Hermite a serem usados no somatório (1 a 6). */

#include <iostream>
#include <cmath>
#include <iomanip> //Biblioteca para manipulacao do cout

using namespace std;

double mainFunction(double x){
   return pow(x,2);
}

double calcIntegral(double roots[], double weights[], int grade){

   int j;
   double integral = 0;

   for(j=0;j<grade;j++){
      integral = integral + mainFunction(roots[j])*weights[j];
   }
   return integral;
}

double grade6(){

   double weights[6] = {0.00453,0.157067,0.72463,0.72463,0.157067,0.00453};
   double roots[6] = {-2.3506,-1.33585,-0.436077,0.436077,1.33585,2.3506};

   return calcIntegral(roots,weights,6);
}


double grade5(){

   double weights[5] = {0.0199532,0.393619,0.945309,0.393619,0.0199532};
   double roots[5] = {-2.02018,-0.958572,0,0.958572,2.02018};

   return calcIntegral(roots,weights,5);

}


double grade4(){

   double weights[4] = {0.0813128,0.80491,0.80491,0.0813128};
   double roots[4] = {-1.65068,-0.524648,0.524648,1.65068};

   return calcIntegral(roots,weights,4);

}

double grade3(){

   double weights[3] = {0.295409, 1.18164, 0.295409};
   double roots[3] = {-1.22474, 0, 1.22474};

   return calcIntegral(roots,weights,3);

}

double grade2(){

   double weights[2] = {0.886227,0.886227};
   double roots[2] = {0.707107,-0.707107};

   return calcIntegral(roots,weights,2);
}

/*double grade1(float a, float b, double error){
   double integral = 0; double aux = 0;
   double alfa,delta;
   int i; int n = 1;
   double weights[1] = {2};
   double roots[1] = {0};
   alfa = 1;
   while(alfa > error){
      aux = integral;
      integral = 0;
      delta = (b-a)/n;
      for(i=0;i<n;i++){
         integral = integral + calcIntegral(a + delta*i,a+delta*(i+1),roots,weights,1);
      }
      n = n*2;
      alfa = abs(integral-aux)/aux;
   }
   return integral;
}*/

int main(){

   int grade;
   cout << setprecision(4) << fixed;

   cout << "Digite os número de pontos de Hermite: ";
   cin >> grade;


   switch (grade) {

      case 1:
         //cout << grade1() << "\n";
         break;
      case 2:
         cout << grade2() << "\n";
         break;
      case 3:
         cout << grade3() << "\n";
         break;
      case 4:
         cout << grade4() << "\n";
         break;
      case 5:
         cout << grade5() << "\n";
         break;
      default:
         cout << "Metodo nao implementado\n";
   }
}