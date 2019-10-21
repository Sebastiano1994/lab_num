import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import math
from mpl_toolkits.mplot3d import Axes3D


def error(AV,AV2,n):  # Function for statistical uncertainty estimation
    if n==0:
        return 0
    else:
        return math.sqrt((AV2[n] - AV[n]**2)/n)



data = np.loadtxt('dati.dat')
data = np.delete(data, 0)
x = np.arange(len(data))



plt.errorbar(x,data,0)
plt.xlabel('Steps')
plt.ylabel('Lenght')
plt.grid(True)
plt.savefig('Stochastic optimization')
plt.close()


















