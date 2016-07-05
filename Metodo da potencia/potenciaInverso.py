import numpy as np

def reafFile():

	with open('data.txt', 'r') as f:
		content = f.read().splitlines()
		
		# Lendo n
		n = content[0]

		# Lendo a matriz
		matrix = []
		for x in xrange(1,6):
			line = content[x].split(",")
			line = [int(i) for i in line]
			matrix.append(line)
		matrix = np.asarray(matrix)

		# Lendo o v0
		v = np.asarray([int(i) for i in content[6].split(",")])
	
		# Lendo o erro
		error = float(content[7])
	return matrix, n, v, error

def calculate(matrix, epsilon, v):
	error = float("infinity")
	autoValor = float("infinity")	
	vAtual = v

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
	m,n,v,error = reafFile()
	autoValor, autoVetor = calculate(m, error, v)
	
	# Escrevendo no arquivo
	with open('outputInverso.txt',"w") as f:	
		f.write("Autovalor: \n")
		f.write(str(1/autoValor))
		f.write("\n\n")
		f.write("Autovetor: \n")
		f.write(" ".join(map(str, autoVetor)))
		f.close()

	print "Autovalor: ", 1/autoValor
	print "Autovetor: ", autoVetor/autoVetor[4]

if __name__ == "__main__": main()