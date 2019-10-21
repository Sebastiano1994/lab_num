from pandas import read_csv, Series
import numpy as np
import sys, os
import matplotlib.pyplot as plt
import time
import csv



#permutation function (sigma is the permutating transformation i -> sigma(i) )
def reseq(v, sigma):
	new = np.array([v[sigma[i]] for i in range(len(v))])
	return new

def I(vett):
	v = np.array([int(vett[i]) for i in range(len(vett))])
	return v




data = np.loadtxt('positions.csv', delimiter=',')

x, y = np.hsplit(data, 2)


perm = np.loadtxt('conf_final.csv', delimiter=' ')
perm = I(perm)
print(perm)
print(len(x))


x = reseq(x, perm)
y = reseq(y, perm)
a = np.array([x[29], x[0]])
b = np.array([y[29], y[0]])


plt.scatter(x,y, s=5)
for i in range(0, len(x), 2):
	plt.plot(x[i:i+2], y[i:i+2], 'ro-')
	plt.plot(x[i+1:i+3], y[i+1: i+3], 'ro-')
	plt.plot(a, b, 'ro-')
plt.xlabel('x')
plt.ylabel('y')
#plt.grid(True)
plt.savefig('Cities')
plt.close()






