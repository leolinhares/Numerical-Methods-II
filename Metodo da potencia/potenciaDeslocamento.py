import numpy as np

def reafFile():

	with open('dataDeslocamento.txt', 'r') as f:
		content = f.read().splitlines()
		
		# Lendo n
		n = int(content[0])

		# Lendo a matriz
		matrix = []
		for x in xrange(1,4):
			line = content[x].split(",")
			line = [int(i) for i in line]
			matrix.append(line)
		matrix = np.asarray(matrix)

		# Lendo o v0
		v = np.asarray([int(i) for i in content[4].split(",")])
	
		# Lendo o erro
		error = float(content[5])

		# Lendo u
		u = float(content[6])
	return matrix, n, v, error, u

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

def main():
	m,n,v,error,u = reafFile()

	# Calculo da matriz modificada
	a = m - u*np.identity(n)


	autoValor, autoVetor = calculate(a, error, v)
	
	# Escrevendo no arquivo
	with open('outputDeslocamento.txt',"w") as f:	
		f.write("Autovalor: \n")
		f.write(str(autoValor+u))
		f.write("\n\n")
		f.write("Autovetor: \n")
		f.write(" ".join(map(str, autoVetor/autoVetor[2])))
		f.close()

	print "Autovalor: ", autoValor+u
	print "Autovetor: ", autoVetor/autoVetor[2]

if __name__ == "__main__": main()