from pandas import read_csv, Series
import numpy as np
import sys, os
import time
import csv
from scipy import optimize
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import math



data_k = np.loadtxt('ave_Etot.csv', delimiter=",")

r, sigma = np.hsplit(data_k, 2)

'''
a = np.delete(r, 2)
a = np.delete(a,1)
a = np.delete(a,3)
'''

r = np.delete(r,0)

plt.errorbar(np.arange(len(r)), r,yerr=0)
plt.xlabel('steps')
plt.ylabel('<Ek>')
plt.grid(True)
plt.savefig('Kinetic_Energy')
plt.close()


