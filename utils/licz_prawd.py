

import numpy as np
import sys

filename = sys.argv[1]

plik = open(filename, 'r')
data = plik.readlines()
size =  len(data)

matrix = np.zeros((size, size))
for idx_1, linia in enumerate(data):
    print idx_1," -------------"
    transitions =  linia.split(':')[-1].lstrip().rstrip()
    tmp = transitions.split(' ')
    for i in tmp:
        a,b = i.split('-')
        idx = int(a)
        prob = float(b)
        matrix[idx_1, idx] = prob

#kolumny suma do 1

for i in xrange(0, size):
    suma = matrix[:, i].sum()
    matrix[:,i] = matrix[:,i]/float(suma)
    
I = np.identity(size)
B,b = np.ones((size, size)), np.ones((size,1))

k = np.linalg.solve( matrix - I + B, b)       
print k
print k.sum()
