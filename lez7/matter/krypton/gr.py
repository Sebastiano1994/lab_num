from pandas import read_csv, Series
import numpy as np
import sys, os
import matplotlib.pyplot as plt
import time
import csv
from scipy import optimize


#data have already been "blocked"

data = np.fromfile('output.gofr.0', dtype=float, count=-1, sep=' ')
g = np.reshape(data, (10, 100))
n=len(g)
x = np.arange(100)
print(len(g))
g2 = g**2
av = np.sum(g, axis=0)/n #function average

dev = np.sqrt(np.sum(g2, axis=0)/n-(np.sum(g, axis=0)/n)**2)


#print(av)
#print(dev)

f= open("output.gave.0","w+")
for i in range(len(av)):
	f.write(str("%.10E" % av[i])+','+'\t'+str("%.10E" % dev[i])+'\n')
f.close()



plt.errorbar(x,av,yerr=dev)
plt.xlabel('r')
plt.ylabel('<g(r)>')
plt.grid(True)
plt.savefig('g(r)_2')
plt.close()
