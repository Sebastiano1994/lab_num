import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import math

def error(AV,AV2,n):  # Function for statistical uncertainty estimation
    if n==0:
        return 0
    else:
        return math.sqrt((AV2[n] - AV[n]**2)/n)


r = np.fromfile('dati.csv', dtype=float, count=-1, sep=' ')
M=len(r)              # Total number of throws






plt.errorbar(x,sum_prog,yerr=err_prog)
plt.xlabel('#throws')
plt.ylabel('pi')
plt.grid(True)
plt.savefig('Mean')
plt.close()



ave = np.zeros(M)
av2 = np.zeros(M)
sum_prog = np.zeros(M)
su2_prog = np.zeros(M)
err_prog = np.zeros(M)


err




    
plt.errorbar(x,sum_prog,yerr=err_prog)
plt.xlabel('#throws')
plt.ylabel('<sigma>')
plt.grid(True)
plt.savefig('variance')
plt.close()







