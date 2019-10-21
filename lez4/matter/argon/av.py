import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import math

def error(AV,AV2,n):  # Function for statistical uncertainty estimation
    if n==0:
        return 0
    else:
        return math.sqrt((AV2[n] - AV[n]**2)/n)



#KINETIC ENERGY



data_k = np.loadtxt('output_ekin.dat', delimiter=",")
M=len(data_k)         # Total number of throws
N=100                 # Number of blocks
L=int(M/N)            # Number of throws in each block, please use for M a multiple of N
np.random.seed(0)     # Fixing random seed for reproducibility
x = np.arange(N)      # [0,1,2,...,N-1]
ave = np.zeros(N)
av2 = np.zeros(N)
sum_prog = np.zeros(N)
su2_prog = np.zeros(N)
err_prog = np.zeros(N)

for i in range(N):
    sum = 0
    for j in range(L):
        k = j+i*L
        sum += data_k[k]
    ave[i] = sum/L       # r_i 
    av2[i] = (ave[i])**2 # (r_i)^2 

for i in range(N):
    for j in range(i+1):
        sum_prog[i] += ave[j] # SUM_{j=0,i} r_j
        su2_prog[i] += av2[j] # SUM_{j=0,i} (r_j)^2
    sum_prog[i]/=(i+1) # Cumulative average
    su2_prog[i]/=(i+1) # Cumulative square average
    err_prog[i] = error(sum_prog,su2_prog,i) # Statistical uncertainty
    
x*=L # Number of throws = block * (Number of throws in each block)
plt.errorbar(x,sum_prog,yerr=err_prog)
plt.xlabel('steps')
plt.ylabel('<Ek>')
plt.grid(True)
plt.savefig('Kinetic Energy')
plt.close()

f= open("ave_Ekin.csv","w+")
for i in range(len(sum_prog)):
	f.write(str("%.10E" % sum_prog[i])+','+'\t'+str("%.10E" % err_prog[i])+'\n')
f.close()




#POTENTIAL ENERGY



data_p = np.loadtxt('output_epot.dat', delimiter=",")
M=len(data_p)         # Total number of throws
N=100                 # Number of blocks
L=int(M/N)            # Number of throws in each block, please use for M a multiple of N
np.random.seed(0)     # Fixing random seed for reproducibility
x = np.arange(N)      # [0,1,2,...,N-1]
ave = np.zeros(N)
av2 = np.zeros(N)
sum_prog = np.zeros(N)
su2_prog = np.zeros(N)
err_prog = np.zeros(N)

for i in range(N):
    sum = 0
    for j in range(L):
        k = j+i*L
        sum += data_p[k]
    ave[i] = sum/L       # r_i 
    av2[i] = (ave[i])**2 # (r_i)^2 

for i in range(N):
    for j in range(i+1):
        sum_prog[i] += ave[j] # SUM_{j=0,i} r_j
        su2_prog[i] += av2[j] # SUM_{j=0,i} (r_j)^2
    sum_prog[i]/=(i+1) # Cumulative average
    su2_prog[i]/=(i+1) # Cumulative square average
    err_prog[i] = error(sum_prog,su2_prog,i) # Statistical uncertainty
    
x*=L # Number of throws = block * (Number of throws in each block)
plt.errorbar(x,sum_prog,yerr=err_prog)
plt.xlabel('steps')
plt.ylabel('<Epot>')
plt.grid(True)
plt.savefig('Potential energy')
plt.close()


f= open("ave_Epot.csv","w+")
for i in range(len(sum_prog)):
	f.write(str("%.10E" % sum_prog[i])+','+'\t'+str("%.10E" % err_prog[i])+'\n')
f.close()



#TOTAL ENERGY



data_t = np.loadtxt('output_etot.dat', delimiter=",")
M=len(data_t)         # Total number of throws
N=100                 # Number of blocks
L=int(M/N)            # Number of throws in each block, please use for M a multiple of N
np.random.seed(0)     # Fixing random seed for reproducibility
x = np.arange(N)      # [0,1,2,...,N-1]
ave = np.zeros(N)
av2 = np.zeros(N)
sum_prog = np.zeros(N)
su2_prog = np.zeros(N)
err_prog = np.zeros(N)

for i in range(N):
    sum = 0
    for j in range(L):
        k = j+i*L
        sum += data_t[k]
    ave[i] = sum/L       # r_i 
    av2[i] = (ave[i])**2 # (r_i)^2 

for i in range(N):
    for j in range(i+1):
        sum_prog[i] += ave[j] # SUM_{j=0,i} r_j
        su2_prog[i] += av2[j] # SUM_{j=0,i} (r_j)^2
    sum_prog[i]/=(i+1) # Cumulative average
    su2_prog[i]/=(i+1) # Cumulative square average
    err_prog[i] = error(sum_prog,su2_prog,i) # Statistical uncertainty
    
x*=L # Number of throws = block * (Number of throws in each block)
plt.errorbar(x,sum_prog,yerr=err_prog)
#plt.ylim([2.282e-21, 2.2838e-21])
plt.xlabel('steps')
plt.ylabel('<Etot>')
plt.grid(True)
plt.savefig('Total energy')
plt.close()


f= open("ave_Etot.csv","w+")
for i in range(len(sum_prog)):
	f.write(str("%.10E" % sum_prog[i])+','+'\t'+str("%.10E" % err_prog[i])+'\n')
f.close()



#TEMPERATURE





data_T = np.loadtxt('output_temp.dat', delimiter=",")
M=len(data_T)         # Total number of throws
N=100                 # Number of blocks
L=int(M/N)            # Number of throws in each block, please use for M a multiple of N
np.random.seed(0)     # Fixing random seed for reproducibility
x = np.arange(N)      # [0,1,2,...,N-1]
ave = np.zeros(N)
av2 = np.zeros(N)
sum_prog = np.zeros(N)
su2_prog = np.zeros(N)
err_prog = np.zeros(N)

for i in range(N):
    sum = 0
    for j in range(L):
        k = j+i*L
        sum += data_T[k]
    ave[i] = sum/L       # r_i 
    av2[i] = (ave[i])**2 # (r_i)^2 

for i in range(N):
    for j in range(i+1):
        sum_prog[i] += ave[j] # SUM_{j=0,i} r_j
        su2_prog[i] += av2[j] # SUM_{j=0,i} (r_j)^2
    sum_prog[i]/=(i+1) # Cumulative average
    su2_prog[i]/=(i+1) # Cumulative square average
    err_prog[i] = error(sum_prog,su2_prog,i) # Statistical uncertainty
    
x*=L # Number of throws = block * (Number of throws in each block)
plt.errorbar(x,sum_prog,yerr=err_prog)
plt.xlabel('steps')
plt.ylabel('<T>')
plt.grid(True)
plt.savefig('Temperature')
plt.close()


f= open("ave_temp.csv","w+")
for i in range(len(sum_prog)):
	f.write(str("%.10E" % sum_prog[i])+','+'\t'+str("%.10E" % err_prog[i])+'\n')
f.close()



#PRESSURE



data_P = np.loadtxt('output_pres.dat', delimiter=",")
M=len(data_P)         # Total number of throws
N=100                 # Number of blocks
L=int(M/N)            # Number of throws in each block, please use for M a multiple of N
np.random.seed(0)     # Fixing random seed for reproducibility
x = np.arange(N)      # [0,1,2,...,N-1]
ave = np.zeros(N)
av2 = np.zeros(N)
sum_prog = np.zeros(N)
su2_prog = np.zeros(N)
err_prog = np.zeros(N)

for i in range(N):
    sum = 0
    for j in range(L):
        k = j+i*L
        sum += data_P[k]
    ave[i] = sum/L       # r_i 
    av2[i] = (ave[i])**2 # (r_i)^2 

for i in range(N):
    for j in range(i+1):
        sum_prog[i] += ave[j] # SUM_{j=0,i} r_j
        su2_prog[i] += av2[j] # SUM_{j=0,i} (r_j)^2
    sum_prog[i]/=(i+1) # Cumulative average
    su2_prog[i]/=(i+1) # Cumulative square average
    err_prog[i] = error(sum_prog,su2_prog,i) # Statistical uncertainty
    
x*=L # Number of throws = block * (Number of throws in each block)
plt.errorbar(x,sum_prog,yerr=err_prog)
plt.xlabel('steps')
plt.ylabel('<P>')
plt.grid(True)
plt.savefig('Pressure')
plt.close()


f= open("ave_press.csv","w+")
for i in range(len(sum_prog)):
	f.write(str("%.10E" % sum_prog[i])+','+'\t'+str("%.10E" % err_prog[i])+'\n')
f.close()

















