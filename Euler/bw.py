import numpy as np
import math
from numpy import linalg as LA

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

def forwardEuler(timeInterval,s0):
	anteriorState = s0
	s = anteriorState + np.multiply(timeInterval,fst(anteriorState[0],anteriorState[1],anteriorState[2],anteriorState[3]))
	return s

def backwardEuler(tempo,timeInterval, error):
	previous = np.array([[0],[0],[0],[0]])
	unknown = forwardEuler(timeInterval,previous)
	for i in xrange(1,int(tempo/timeInterval)):	
		while True:
			current = previous + np.multiply(timeInterval,fst(unknown[0],unknown[1],unknown[2],unknown[3]))
			if (LA.norm((current-unknown)/current) < error): 
				break
			unknown = current
		previous = current
		unknown = forwardEuler(timeInterval,previous)
	return current

print backwardEuler(1,1/30.0,0.001)
