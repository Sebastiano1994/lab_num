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


plt.scatter(x,y, s=5)
for i in range(0, len(x), 2):
	plt.plot(x[i:i+2], y[i:i+2], 'ro-')
	plt.plot(x[i+1:i+3], y[i+1: i+3], 'ro-')
plt.xlabel('x')
plt.ylabel('y')
#plt.grid(True)
plt.savefig('Cities')
plt.close()






'''
seq = np.array([0,2,1,3])

def pbc(i):
	if i>3:
		i-=3
	return i

x = np.arange(4)
y = np.arange(4)
x[0] = 0
y[0] = 0
x[1] = 1
y[1] = 1
x[2] = 1
y[2] = 0
x[3] = 0
y[3] = 1





x = reseq(x, seq)
y = reseq(y, seq)




plt.scatter(x,y, s=5)
for i in range(0, len(x), 2):
	plt.plot(x[i:i+2], y[i:i+2], 'ro-')
	plt.plot(x[i+1:i+3], y[i+1: i+3], 'ro-')
plt.xlabel('x')
plt.ylabel('y')
#plt.grid(True)
plt.savefig('Cities')
plt.close()



for i in range(len(x)):
	print(seq[i])



plt.scatter(x,y, s=5)
for i in range(0, len(x)-2, 2):
	plt.plot(x[seq[i]:seq[i+2]], y[seq[i]:seq[i+2]], 'ro-')
	plt.plot(x[seq[i+1]:seq[i+3]], y[seq[i+1]:seq[i+3]], 'ro-')
plt.xlabel('x')
plt.ylabel('y')
#plt.grid(True)
plt.savefig('Cities2')
plt.close()
'''

