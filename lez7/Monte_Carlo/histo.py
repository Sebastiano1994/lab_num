import matplotlib.pyplot as plt
from pandas import read_csv, Series
import numpy as np

n=100


data = np.fromfile('output.gofr.0', dtype=float, count=-1, sep=' ')
print(data)
plt.hist(data, range=(0,1));
plt.savefig('g(r)')
plt.close()


