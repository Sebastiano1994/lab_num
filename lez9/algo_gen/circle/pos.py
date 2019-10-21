from pandas import read_csv, Series
import numpy as np
import sys, os
import matplotlib.pyplot as plt
import time
import csv



data = np.loadtxt('positions.csv', delimiter=',')

x, y = np.hsplit(data, 2)

print(len(data))


plt.scatter(x,y, s=5)
plt.xlabel('x')
plt.ylabel('y')
#plt.grid(True)
plt.savefig('Cities')
plt.close()

