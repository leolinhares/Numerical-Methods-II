# Escreva e teste um programa que usa o metodo de Jacobi para transformar uma matriz simetrica A, dada como entrada, em uma matriz DIAGONAL.
# O programa deve ler a matriz e uma tolerancia a partir de um arquivo e imprimir: 
# a matriz de entrada, a matriz diagonal e a matriz de Jacobi. 
# Teste se as colunas da matriz de Jacobi sao automotores da matriz de entrada.

import numpy as np
import math

# matrix = np.array([[4,2,2,1],[2,-3,1,1],[2,1,3,1],[1,1,1,2]])

# matrix = np.array([[4,1,-2,2],[1,2,0,1],[-2,0,3,-2],[2,1,-2,-1]])
#matrix = np.array([[1,2],[3,4]])

def reafFile():

	with open('dataT.txt', 'r') as f:
		content = f.read().splitlines()
		
		# Lendo n
		n = int(content[0])

		# Lendo a matriz
		matrix = []
		for x in xrange(1,n+1):
			line = content[x].split(",")
			line = [float(i) for i in line]
			matrix.append(line)
		matrix = np.asarray(matrix)
	
		# Lendo o erro
		error = float(content[n+1])
	return n, matrix, error

def jacobi(matrix, error, matrix_order):
	modified_matrix = matrix
	jacobi_matrix = np.identity(matrix_order)
	e = float("infinity")

	while e > error:
		# da coluna 0 ate a coluna n-1
		for j in xrange(0,matrix_order-1):
			# vai ate a coluna n
			for i in xrange(j+1,matrix_order):
				# utiliza os elementos ajj, aij, aii da matrix modificada a
				jj = modified_matrix[j,j]
				ij = modified_matrix[i,j]
				ii = modified_matrix[i,i]
				J_matrix = construct_J(jj, ij, ii, i, j, matrix_order)
				modified_matrix = (J_matrix.T).dot(modified_matrix).dot(J_matrix)
				jacobi_matrix = jacobi_matrix.dot(J_matrix)
		
		#criterio de parada
		# retorna os indices dos elementos abaixo da diagonal principal
		lower_matrix_indexes = np.tril_indices(matrix_order,-1)
		lower_triangular_matrix = modified_matrix[lower_matrix_indexes] # matriz triangular modificada
		e = math.sqrt(sum(np.square(lower_triangular_matrix))) # soma quadrada de todos os elementos

	return modified_matrix, jacobi_matrix


def construct_J(jj, ij, ii, i, j, matrix_order):
	J_matrix = np.identity(matrix_order)
	theta = 0
	if ii == jj:
		theta = math.pi/4
	else:
		theta = (math.atan(2*ij/(jj-ii)))/2

	J_matrix[j,j] =	math.cos(theta)
	J_matrix[j,i] = -math.sin(theta)
	J_matrix[i,j] = math.sin(theta)
	J_matrix[i,i] = math.cos(theta)

	return J_matrix


def main():
	n, matrix ,error = reafFile()

	np.set_printoptions(suppress=True, precision=4)
	
	diagonal, jac = jacobi(matrix, error, n)

	print "Matriz Original: \n"
	print matrix
	print "\nMatriz Diagonal: \n"
	print diagonal
	print "\nMatriz Jacobi: \n"
	print jac
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
