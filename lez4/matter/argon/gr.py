from pandas import read_csv, Series
import numpy as np
import sys, os
import matplotlib.pyplot as plt
import time
import csv
from scipy import optimize
import math


def error(AV,AV2,n):  # Function for statistical uncertainty estimation
    if n==0:
        return 0
    else:
        return math.sqrt((AV2[n] - AV[n]**2)/n)


#data have already been "blocked"

data = np.fromfile('output.gofr.csv', dtype=float, count=-1, sep=' ')
bins = 100 #number of bins
l    = len(data) #number of data elements
g = np.reshape(data, ( int(len(data)/bins), bins))
n=len(g)
x = np.arange(bins)
#print(len(g))
av = np.zeros(bins)
N = 100
#print(len(g))
L = int(len(g)/N)
#print(L)
sums = np.zeros(bins)
ave = np.zeros((N, bins))
av2 = np.zeros((N, bins))
sum_prog = np.zeros((N, bins))
su2_prog = np.zeros((N, bins))
err_prog = np.zeros((N, bins))


#for i in range(int(len(g)/N)):
#	av[i] = np.sum(


'''
g2 = g**2
av = np.sum(g, axis=0)/n #function average

dev = np.sqrt(np.sum(g2, axis=0)/n-(np.sum(g, axis=0)/n)**2)
'''

for l in range(bins):
	for i in range(N):
		sums = np.zeros(bins)
		for j in range(L):
			k = j+i*L
			sums[l] += g[k][l]
			ave[i][l] = sums[l]/L      # r_i 
			av2[i][l] = (ave[i][l])**2 # (r_i)^2
		#print(ave)
'''
	for i in range(N):
		for j in range(i+1):
			sum_prog[i][l] += ave[j][l] # SUM_{j=0,i} r_j
			su2_prog[i][l] += av2[j][l] # SUM_{j=0,i} (r_j)^2
			sum_prog[i][l]/=(i+1) # Cumulative average
			su2_prog[i][l]/=(i+1) # Cumulative square average
			err_prog[i][l] = error(sum_prog[l],su2_prog[l],i) # Statistical uncertainty
'''




av = np.sum(ave, axis=0)/len(ave)


#print(ave)

a2 = ave**2
print(len(a2))
dev = (np.sqrt(np.sum(a2, axis=0)/len(a2) - (np.sum(ave, axis=0)/len(a2))**2))

'''
print(np.sum(a2, axis=0)[58]/len(a2))
print(np.sum(ave/len(ave), axis=0)[58]**2)

print(dev)
print(av)
print(av2)
print(np.argmax(dev))
print(av[58])
'''




f= open("output.gave.0","w+")
for i in range(len(av)):
	f.write(str("%.10E" % av[i])+','+'\t'+str("%.10E" % dev[i])+'\n')
f.close()


#print(np.argmax(data))
#print(np.max(data))



plt.errorbar(x,av,yerr=dev)
plt.xlabel('r')
plt.ylabel('<g(r)>')
plt.grid(True)
plt.savefig('g(r)')
plt.close()
