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
# [[1, t],[-(t/2), 1]] * [[v1],[u1]] = [[v0 - deltaT*u0 + deltaT/2*cos(t0)+ deltaT/2*cos(t1)],[u0+deltaT/2*v0]]

# s0 = [[v0],[u0]] = [[0],[0]]

def eulerModificado(tempo,timeInterval):
	s0 = np.zeros((2, 1))
	anteriorState = s0 

	t = timeInterval
	tAnterior = 0
	tAtual = timeInterval
	for i in xrange(0,int(tempo/timeInterval)):
		tAtual = timeInterval*(i+1)
		a = np.array([[1, t],[-(t/2), 1]])
		b = np.array([anteriorState[0] - t*anteriorState[1] + (t/2)*math.cos(tAnterior)+(t/2)*math.cos(tAtual),anteriorState[1]+(t/2)*anteriorState[0]])
		s = np.linalg.solve(a, b)
		anteriorState = s
		tAnterior = tAtual
	return s



print eulerModificado(1,1/10.0)

# quero saber o valor do estado no t=1segundo e o intervalo de tempo do calculo eh 1/10 segundos
