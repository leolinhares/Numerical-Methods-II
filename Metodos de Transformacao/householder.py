# Escreva e teste um programa que usa o metodo de Householder
# para transformar uma matriz simetrica A, dada como entrada,
# em uma matriz TRIDIAGONAL. O programa deve ler a matriz a partir
# de um arquivo e imprimir: a matriz de entrada, a matriz tridiagonal e a matriz de Householder.
import numpy as np
# matrix = np.array([[3,4,7,9],[4,2,1,8],[7,1,5,2],[9,8,2,1]])
# matrix = np.array([[4,1,-2,2],[1,2,0,1],[-2,0,3,-2],[2,1,-2,-1]])
# matrix = np.array([[4,2,2,1],[2,-3,1,1],[2,1,3,1],[1,1,1,2]])
# matrix = np.array([[3,1,4],[1,7,2],[4,2,0]])


def reafFile():

	with open('data2.txt', 'r') as f:
		content = f.read().splitlines()
		
		# Lendo n
		n = int(content[0])

		# Lendo a matriz
		matrix = []
		for x in xrange(1,n+1):
			line = content[x].split(",")
			line = [int(i) for i in line]
			matrix.append(line)
		matrix = np.asarray(matrix)
	
		# Lendo o erro
		error = float(content[n+1])
	return n, matrix, error

def householder(matrix, size):
	hh = np.identity(size)
	modified_matrix = matrix

	# para h de 0 ate n-3 (incluindo n-2)
	for h in xrange(0,size-2): # so vai ate o 1. coluna 0, coluna 

		column = modified_matrix[:,h].copy()
		q = calculate_householder(column, h, size) #coluna h da matriz modificada
		hh = hh.dot(q) # nao pode mudar a ordem dessa operacao
		modified_matrix = q.dot(modified_matrix).dot(q)

	return modified_matrix, hh

def calculate_householder(column, column_index, size):
	v = column[column_index+1:] # pega os h+1 elementos do vetor. se vetor = 1 2 3 4 5 e h=1 pega 3 4 5
	norma = np.linalg.norm(v)

	N = v
	if(v[0]>0):
		N[0] = N[0] + norma
	else:
		N[0] = N[0] - norma

	cn = np.linalg.norm(N)

	modified_N = np.divide(N,cn)

	# n tem que ter n elementos, dos quais os h+1 primeiros devem ser zero e depois coloca-se o vetor modificado
	n = np.zeros(column_index+1)
	n = np.append(n,modified_N)


	n_transpose = n[:,None] # transformando o array n em um array vetor (array coluna), que nao existe no numpy

	q = np.identity(size) - 2*n*n_transpose

	return q


def main():
	size, matrix ,error = reafFile()

	np.set_printoptions(suppress=True, precision=4)
	
	t_matrix, hh_matrix = householder(matrix, size)

	print "Matriz Original: \n"
	print matrix
	print "\nMatriz Triangular: \n"
	print t_matrix
	print "\nMatriz Householder: \n"
	print hh_matrix


	# with open('outputHH.txt',"w") as f:	
	# 	f.write("Matrix Original: \n")
	# 	f.write(" \n".join(map(str, matrix)))
	# 	f.write("\n\n")
	# 	f.write("Matrix Triangular: \n")
	# 	f.write(" \n".join(map(str, t_matrix)))
	# 	f.write("\n\n")
	# 	f.write("Matrix de Householder: \n")
	# 	f.write(" \n".join(map(str, hh_matrix)))
	# 	f.close()

if __name__ == "__main__": main()