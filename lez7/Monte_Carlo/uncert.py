from pandas import read_csv, Series
import numpy as np
import sys, os
import matplotlib.pyplot as plt
import time
import csv
from scipy import optimize




#a, b = np.loadtxt('dati.csv', delimiter=",")



data = read_csv('dati.csv', nrows=10000)


a, b = np.hsplit(data, 2) #divido le due misure (energia e pressione)

a = np.array(a)
a = a.ravel()
b = np.array(b)
b = b.ravel()

#parameters
#number of measures:
M = 10000

#number of blocks:
N = 10
#parameter:
parm = 50

#Energy uncertainties
def sigma(par):
	av  = np.split(a, par)
	for i in range(par):
		av[i]  = np.mean(av[i])

	av = np.array(av)
	#print(av)
	av2 = av**2
	#print(av2)
	#print(np.mean(av2))
	#print(np.mean(av)**2)
	#print("Uncertainties with", parm,":")
	#print(sigmall)

	return np.sqrt((np.mean(av2) - np.mean(av)**2)/M)



num = np.array([10, 25, 50])
sig = sigma(num)
print(sig)


'''
stringa='sigma_potential'
fig = plt.figure(dpi=400)
plt.xlabel('time')
plt.ylabel('uncertainties')
plt.ticklabel_format(style='sci', axis='x', scilimits=(0,0))
plt.rc('grid', linestyle='-', color='gray')
plt.plot(final_a, alpha=0.3, color='C0')
plt.savefig(stringa)
plt.close('all')
'''























