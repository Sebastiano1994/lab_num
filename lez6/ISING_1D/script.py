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

M=10**4               # Total number of throws
N=20                 # Number of blocks
L=int(M/N)            # Number of throws in each block, please use for M a multiple of N


data  = np.loadtxt('Info.csv', delimiter=",")

T, U, C, X = np.hsplit(data, 4)

T = T.ravel()
U = U.ravel()
C = C.ravel()
X = X.ravel()


unc = np.loadtxt('output_ene.csv', delimiter=",")
s_e = unc[:,2]
s_e = np.reshape(s_e, (20,30) )
s_e2 = s_e**2
s_e2 = s_e2.sum(axis=0)/L
s_e = (s_e.sum(axis=0)/L)**2
s_e = np.sqrt((s_e2 - s_e)/N)
#print(s_e)
#print(U)
#print(T)
plt.errorbar(T,U,s_e)
plt.xlabel('T')
plt.ylabel('U')
plt.grid(True)
plt.savefig('Internal Energy')
plt.close()


unc = np.loadtxt('output_heat.csv', delimiter=",")
s_c = unc[:,2]
s_c = np.reshape(s_c, (20,30) )
s_c2 = s_c**2
s_c2 = s_c2.sum(axis=0)/L
s_c = (s_c.sum(axis=0)/L)**2
#print(s_c)
#print(s_c2)
s_c = np.sqrt((s_c2 - s_c)/20)
#print(s_c)
plt.errorbar(T,C,s_c)
plt.xlabel('T')
plt.ylabel('C')
plt.grid(True)
plt.savefig('Specific Heat')
plt.close()



unc = np.loadtxt('output_chi.csv', delimiter=",")
s_x = unc[:,2]
s_x = np.reshape(s_x, (20,30) )
s_x2 = s_x**2
s_x2 = s_x2.sum(axis=0)/L
s_x = (s_x.sum(axis=0)/L)**2
s_x = np.sqrt((s_x2 - s_x)/N)
plt.errorbar(T,X,s_x)
plt.xlabel('T')
plt.ylabel('X')
plt.grid(True)
plt.savefig('Magnetic Susceptibility')
plt.close()


data_m = np.loadtxt('Info_m.csv', delimiter=",")
unc = np.loadtxt('output_mag.csv', delimiter=",")
s_m = unc[:,2]
T, M = np.hsplit(data_m, 2)
s_m = np.reshape(s_m, (20,30) )
#print(s_m)
s_m2 = s_m**2
s_m2 = s_m2.sum(axis=0)/L
s_m = (s_m.sum(axis=0)/L)**2
s_m = np.sqrt((s_m2 - s_m)/N)
plt.errorbar(T,M,s_m)
plt.xlabel('T')
plt.ylabel('M')
plt.grid(True)
plt.savefig('Magnetization')
plt.close()


#print(len(r_m))














