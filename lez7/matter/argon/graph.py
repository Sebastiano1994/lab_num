import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import math


data = np.loadtxt('output.epot.csv', delimiter=",")

a, sumav, av, d = np.hsplit(data, 4)

av = av.ravel()
print(av)



data = np.loadtxt('dati.csv', delimiter=",")


a, b = np.hsplit(data, 2)

a = np.reshape(a, (10, int(len(a)/10)))
a2 = a**2
print(len(a))

ave = a.sum(axis=0)/len(a)

print(ave)

avsq = a2.sum(axis=0)/len(a)

print(avsq)

dev = np.sqrt(avsq-av**2)




plt.errorbar(np.arange(len(av)),av,dev)
plt.xlabel('Steps')
plt.ylabel('<Epot>')
plt.grid(True)
plt.savefig('Potential')
plt.close()

