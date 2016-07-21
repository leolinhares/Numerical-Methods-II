import numpy as np
import math

# Exemplo do trabalho final da disciplina
m1 = 2.0
m2 = 3.0
k1 = 15.0
k2 = 20.0
c1 = 1.0
c2 = 2.0
f1 = 20.0
f2 = 12.0

def fst(x1,x2,v1,v2):
    dv1 = 1/m1*(k2*(x2-x1)+c2*(v2-v1)-k1*x1-c1*v1+f1)
    dv2 = 1/m2*(-k2*(x2-x1)-c2*(v2-v1)+f2)
    fst = np.array([v1,v2,dv1,dv2])
    return fst

def forwardEuler(tempo,timeInterval):
	anteriorState = np.array([[0],[0],[0],[0]])
	for i in range(0,int(tempo/timeInterval)):
		s = anteriorState + np.multiply(timeInterval,fst(anteriorState[0],anteriorState[1],anteriorState[2],anteriorState[3]))
		anteriorState = s
	return s

print forwardEuler(1,1/30.0)

# quero saber o valor do estado no t=1 segundo e o intervalo de tempo do calculo eh 1/30 segundos