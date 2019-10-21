import matplotlib.pyplot as plt
from pandas import read_csv, Series
import numpy as np

n=2


data = np.loadtxt('Histo.dat')
print(data)


plt.hist(data, bins=200);
plt.savefig('Psi2_ravv')
plt.close()




print(data[5270])
print(data[101])
print(len(data))
