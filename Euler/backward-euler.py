import numpy as np
import math


# Exemplo usado
# v' = -2u + cos(t)
# u' = v
# u(0) = 0
# v(0) = 0
# Ou seja, estado S = [[v],[u]]
# e F(s,t) = [[-2u + cos(t)],[v]]


# Sistema linear a ser resolvido
# [[1, 2t],[-t, 1]] * [[v1],[u1]] = [[v0 + cos(t)],[u0]]

# s0 = [[v0],[u0]] = [[0],[0]]
s0 = np.zeros((2, 1))

def backwardEuler(tempo,timeInterval):
	anteriorState = s0
	t = timeInterval
	tAtual = t
	for i in xrange(0,int(tempo/timeInterval)):
		tAtual = timeInterval*(i+1)
		a = np.array([[1,2*t],[-t,1]])
		b = np.array([anteriorState[0]+t*math.cos(tAtual),anteriorState[1]])
		s = np.linalg.solve(a, b)
		anteriorState = s
	return s



print backwardEuler(1,1/10.0)

# quero saber o valor do estado no t=1segundo e o intervalo de tempo do calculo eh 1/10 segundos
