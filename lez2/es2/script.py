import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import math
from mpl_toolkits.mplot3d import Axes3D
from scipy import optimize




M=10**2               # Total number of steps
T=10**4               # Number of trajectories
r  = np.fromfile('dati_discr.csv', dtype=float, count=-1, sep=' ')
r2 = np.fromfile('dati_cont.csv', dtype=float, count=-1, sep=' ')
x = np.arange(M)


data = np.loadtxt('err_discr.csv', delimiter=',')


#print(data)


mean  = np.reshape(data, (M, T))

#print(len(mean))
#print(mean)


mean2 = mean
mean = np.sqrt(mean)


mean  = np.sum(mean, axis=1)/T
mean2 = np.sum(mean2, axis=1)/T


#print(mean2)
#print(mean)
#print(mean2-mean*mean)



final = np.sqrt(np.absolute(mean2-mean**2))



#print(final)

r_err = r
r_err[0]=1
r_err[1]=1

dev2 = np.divide(final,r_err)/2

#print(dev)


data = np.loadtxt('err_cont.csv', delimiter=',')


#print(data)


mean  = np.reshape(data, (M, T))

#print(len(mean))
#print(mean)


mean2 = mean
mean = np.sqrt(mean)


mean  = np.sum(mean, axis=1)/T
mean2 = np.sum(mean2, axis=1)/T


#print(mean2)
#print(mean)
#print(mean2-mean*mean)



final = np.sqrt(np.absolute(mean2-mean**2))



#print(final)

r_err = r2
r_err[0]=1
r_err[1]=1

dev = np.divide(final,r_err)/2

#print(dev)
 



plt.errorbar(x,r2,dev2)
plt.xlabel('#steps')
plt.ylabel('(<r^2>)^1/2')
plt.grid(True)
plt.savefig('r_c')
plt.close()

plt.errorbar(x,r,dev)
plt.xlabel('#steps')
plt.ylabel('(<r^2>)^1/2')
plt.grid(True)
plt.savefig('r_d')
plt.close()




#print discrete parameter k (which multiplies our square root):
def test_func(x, a, b):
    return a * (x**b)

params = optimize.curve_fit(test_func, x, r)

print(params)


#print continuous parameter k (which multiplies our square root):

params = optimize.curve_fit(test_func, x, r2)

print(params)













