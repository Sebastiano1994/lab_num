import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import math
from mpl_toolkits.mplot3d import Axes3D





'''
data = np.loadtxt('Inf_2.csv', delimiter=",")

sigma, mu, E = np.hsplit(data, 3)



plt.errorbar(mu,E,0)
plt.xlabel('mu')
plt.ylabel('E')
plt.grid(True)
plt.savefig('E_mu')
plt.close()


data2 = np.loadtxt('Inf.csv', delimiter=",")

sigma, mu, E = np.hsplit(data2, 3)

r=np.argmin(E)
'''

data3 = np.loadtxt('Info_u2.csv', delimiter=',')

sigma, mu, E = np.hsplit(data3, 3)
r=np.argmin(E)

print(min(E))
print(np.argmin(E))
print(sigma[r], mu[r])












