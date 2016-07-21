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

def state(x1,x2,v1,v2):
    eq1 = 1/m1*(k2*(x2-x1)+c2*(v2-v1)-k1*x1-c1*v1+f1)
    eq2 = 1/m2*(-k2*(x2-x1)-c2*(v2-v1)+f2)
    state = np.array([v1,v2,eq1,eq2])
    return state

def forwardEuler(tempo,timeInterval,s0):
	anteriorState = s0
	s = anteriorState + np.multiply(timeInterval,state(anteriorState[0],anteriorState[1],anteriorState[2],anteriorState[3]))
	return s

def modifiedEuler(tempo,timeInterval, error):
	s0 = np.array([[0],[0],[0],[0]])
	s1 = forwardEuler(tempo,timeInterval,s0)
	for i in xrange(1,int(tempo/timeInterval)):	
		while True:
			s2 = s0 + np.multiply(timeInterval/2.0,(state(s1[0],s1[1],s1[2],s1[3])+state(s0[0],s0[1],s0[2],s0[3])))
			if (LA.norm((s2-s1)/s2) < error): 
				break
			s1 = s2
		s0 = s2
		s1 = forwardEuler(tempo,timeInterval,s0)
	return s2

print modifiedEuler(1,1/30.0,0.001)


