from pandas import read_csv, Series
import numpy as np
import sys, os
import matplotlib.pyplot as plt
import time
import csv
from scipy import optimize



tot = 100

data = np.loadtxt('dati.csv', delimiter=",")


a, b = np.hsplit(data, 2) #divido le due misure (energia e pressione)

a = a.ravel()
b = b.ravel()


#Potential autocorrelation:

lenght = len(a)
M = int(lenght/tot)
a = np.reshape(a, (M, tot))

print(a)

#a = np.delete(a, np.s_[il:10000], axis=1)
av_a = a.sum(axis=0)/M


print(av_a)


mix_a = np.array([[a[i][j]*a[i][0] for j in range(tot)] for i in range(M)])




mix_a = mix_a.sum(axis=0)/M



final_a = mix_a - av_a*av_a[0]
#print("termine 20: ", mix_a[10])
#print("termine 20: ",av_a[10]*av_a[0])
final_a = final_a/final_a[0]

#print(final_a)



stringa='autocorr_potential'
fig = plt.figure(dpi=400)
plt.xlabel('time')
plt.ylabel('autocorrelation')
plt.ticklabel_format(style='sci', axis='x', scilimits=(0,0))
plt.rc('grid', linestyle='-', color='gray')
plt.plot(final_a, alpha=0.3, color='C0')
plt.savefig(stringa)
plt.close('all')




#Pression autocorrelation:


b = np.reshape(b, (M, tot))

print(b)

#a = np.delete(a, np.s_[il:10000], axis=1)
av_b = b.sum(axis=0)/M


print(av_b)


mix_b = np.array([[b[i][j]*b[i][0] for j in range(tot)] for i in range(M)])




mix_b = mix_b.sum(axis=0)/M



final_b = mix_b - av_b*av_b[0]
#print("termine 20: ", mix_a[10])
#print("termine 20: ",av_a[10]*av_a[0])
final_b = final_b/final_b[0]





#Fitting dei dati:

x_data = np.arange(tot)


def test_func(x, b):
    return np.exp(- x/b)

#params, params_covariance = optimize.curve_fit(test_func, x_data, y_data, p0=[1, 1])

#print(params)


params = optimize.curve_fit(test_func, x_data, final_a)

print(params)

params = optimize.curve_fit(test_func, x_data, final_b)

print(params)







stringa='autocorr_pressure'
fig = plt.figure(dpi=400)
plt.xlabel('time')
plt.ylabel('autocorrelation')
plt.ticklabel_format(style='sci', axis='x', scilimits=(0,0))
plt.rc('grid', linestyle='-', color='gray')
plt.plot(final_b, alpha=0.3, color='C0')
plt.savefig(stringa)
plt.close('all')





























    
  
