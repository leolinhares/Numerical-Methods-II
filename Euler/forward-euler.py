import numpy as np

# Exemplo do trabalho final da disciplina
m1 = 20.0 
m2 = 15.0
f1 = 200.0
f2 = 120.0
k1 = 8.5
k2 = 10.2
c1 = 23.0
c2 = 14.0

m = np.array([[m1,0],[0,m2]])
f = np.array([[f1],[f2]])
k = np.array([[-k1-k2,k2],[k2,-k2]])
c = np.array([[-c1-c2,c2],[c2,-c2]])

u0 = np.zeros((2, 1))
v0 = np.zeros((2, 1))

s0 = np.array([u0,v0])

mInv = np.linalg.inv(m)


def state(u,v):
	eq = mInv.dot(f-c.dot(v)-k.dot(u))
	state = np.concatenate([v[None,:],eq[None,:]])
	return state

def forwardEuler(tempo,timeInterval):
	anteriorState = s0
	for i in xrange(0,int(tempo/timeInterval)):
		s = anteriorState + np.multiply(timeInterval,state(anteriorState[0],anteriorState[1]))
		anteriorState = s
	return s



print forwardEuler(1,1/30.0)

# quero saber o valor do estado no t=1segundo e o intervalo de tempo do calculo eh 1/30 segundos
