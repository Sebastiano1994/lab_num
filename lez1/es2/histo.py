import matplotlib.pyplot as plt
from pandas import read_csv, Series
import numpy as np
import argparse


parser=argparse.ArgumentParser()
parser.add_argument('n', help='Numero di tiri', type=int)
args= parser.parse_args()

n=args.n


data = np.fromfile('linear_'+str(n)+ '.csv', dtype=float, count=-1, sep=' ')
print(data)
plt.hist(data);
plt.savefig('dice'+str(n))
plt.close()

#data2 = read_csv('exp_1.csv')
data2 = np.fromfile('exp_'+str(n)+'.csv', dtype=float, count=-1, sep=' ')
print(data2)
plt.hist(data2, bins=40, range=(1.55, 1.9))
plt.ylabel('No of times')
plt.savefig('exp'+str(n))
plt.close()

data3 = np.fromfile('lorentz_' + str(n)+'.csv', dtype=float, count=-1, sep=' ')
plt.hist(data3, bins=40, range=(-10**(1), 10**(1)))
plt.ylabel('No of times')
plt.savefig('lorentz'+str(n))
plt.close()
