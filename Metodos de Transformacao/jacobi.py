# Escreva e teste um programa que usa o metodo de Jacobi para transformar uma matriz simetrica A, dada como entrada, em uma matriz DIAGONAL.
# O programa deve ler a matriz e uma tolerancia a partir de um arquivo e imprimir: 
# a matriz de entrada, a matriz diagonal e a matriz de Jacobi. 
# Teste se as colunas da matriz de Jacobi sao automotores da matriz de entrada.

import numpy as np
import math

matrix = np.array([[4,1,-2,2],[1,2,0,1],[-2,0,3,-2],[2,1,-2,-1]])
#matrix = np.array([[1,2],[3,4]])

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

diagonal, jac = jacobi(matrix, 0.001, 4)

print diagonal.T
print jac 