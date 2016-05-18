import numpy as np

a = np.array([[-5, 5, -6],[-4,7,-12],[-2,-2,5]])
v0 = np.array([1,1,1])

def calculate(matrix, epsilon, v):
	error = float("infinity")
	autoValor = float("infinity")	
	vAtual = v
	autoVetor = np.array([1,1,1])

	while error > epsilon :
		ultimoAutoValor = autoValor
		vAnterior = vAtual

		# Normalizacao
		autoVetor = vAnterior/(np.linalg.norm(vAnterior))

		# Multiplicacao de matriz por vetor
		vAtual = np.dot(np.linalg.inv(matrix),autoVetor)

		# produto escalar
		autoVetorTransposta = autoVetor.T
		autoValor = np.inner(autoVetorTransposta, vAtual)

		error = abs((autoValor - ultimoAutoValor)/autoValor)


	print np.dot(np.linalg.inv(matrix), autoVetor)
	print np.dot(autoValor, autoVetor)

	return autoValor, autoVetor

autoValor, autoVetor = calculate(a, 0.001, v0)

print "Autovalor: ", 1/autoValor
print "Autovetor: ", autoVetor