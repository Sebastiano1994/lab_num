import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import math


M = 10**6
N = 10**4
L = int(M/N)
print(L)
np.random.seed(0)     # Random seed
r = np.random.rand(M) # r in U[0,1)



r = np.reshape(r, (L, N))

print(len(r))

vec = np.zeros(L)

for j in range(L):
	bins = np.zeros(100)
	for i in range(N):
		#print(r[j][i])
		a = int(r[j][i]*100)
		#print(a)
		bins[a]+=1
	#print(bins)
	s = np.sum((bins -100)**2)
	#print(s)
	vec[j] = s/100

#print(vec)
print(np.sum(vec)/L)



plt.errorbar(np.arange(L),vec,yerr=0)
plt.xlabel('j')
plt.ylabel('Xj')
plt.grid(True)
plt.savefig('Chi_squared')
plt.close()






