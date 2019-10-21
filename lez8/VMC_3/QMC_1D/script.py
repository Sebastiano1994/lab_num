import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import math
from mpl_toolkits.mplot3d import Axes3D



data  = np.loadtxt('probability.dat', delimiter=" ")

x, y, spl = np.hsplit(data,3)

plt.errorbar(x,y,0)
plt.xlabel('x')
plt.ylabel('Prob')
plt.grid(True)
plt.savefig('Psi2')
plt.close()
