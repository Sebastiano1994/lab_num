import numpy as np
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt
from pandas import read_csv, Series
import numpy as np
import sys, os
import matplotlib.pyplot as plt
import time
import csv


datas = read_csv('histo.csv', header=0)
    
x = datas['h']

n, bins, patches = plt.hist(x, 100, facecolor='blue', alpha=0.5)
plt.show()
