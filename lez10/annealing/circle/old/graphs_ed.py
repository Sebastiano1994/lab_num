from pandas import read_csv, Series
import numpy as np
import sys, os
import matplotlib.pyplot as plt
import time
import csv


def graph():
    
    datas = read_csv('Info.csv', header=0)
    
    returns = datas['return']
    victories = datas['vittorie']
    qval = datas['Qval']
    
    ts_ret=Series(returns)
    ts_vic=Series(victories)
    ts_q  =Series(qval)
    if(len(returns)<=0 and len(victories)<=0):
        pass
    


    #print(ts_ret)

    #vettore medie/varianze mediate su 100 blocks di return:
    var_ret  = np.asarray(ts_ret.rolling(N).var())[N-1:]
    mean_ret = np.asarray(ts_ret.rolling(N).mean())[N-1:]
    
    #vettore medie/varianze mediate su 100 blocks di vittorie:
    var_vic  = np.asarray(ts_vic.rolling(N).var())[N-1:]
    mean_vic = np.asarray(ts_vic.rolling(N).mean())[N-1:]
    
    #vettore medie varianze mediate su 100 blocks di Qvalues:
    var_q  = np.asarray(ts_q.rolling(N).var())[N-1:]
    mean_q = np.asarray(ts_q.rolling(N).mean())[N-1:]
    
    
    stringa=nome+'/'+str(scramblate)+'scramble('+str(rang)+'_memory:'+str(memory_max_capacity)+')VITTORIE_0.001adam.png'
    fig = plt.figure(dpi=400)
    #plt.errorbar(len(mean_vic), mean_vic, yerr=var_vic)
    plt.xlabel('Number of Episodes')
    plt.ylabel('Success Percentage')
    plt.ticklabel_format(style='sci', axis='x', scilimits=(0,0))
    plt.rc('grid', linestyle='-', color='gray')
    plt.plot(mean_vic, alpha=0.3, color='C0')
    plt.savefig(stringa)
    plt.close('all')
    
    
    



def save_csv(infos, path):
    
    with open(path, mode='a') as f:
        csv_writer = csv.writer(f, delimiter=',')
        
        if os.stat(path).st_size==0:
            csv_writer.writerow(['vittorie,' + 'return,' + 'steps,' + 'Qval,' + 'eps'])
        
        for row in infos:
            csv_writer.writerow(row)


def scattering(nome, path, iniziale=0):
    #stringa1=nome+'/'+str(scramblate)+'scramble('+str(rang)+'_)VITTORIE_0.001adam.png'
    #stringa2=nome+'/'+str(scramblate)+'scramble('+str(rang)+'_)SCONFITTE_0.001adam.png'

    
    datas = read_csv(path + 'parametri.csv', header=0)
    
    returns   = datas['return']
    victories = datas['vittorie']
    lenght    = datas['steps']
    
    
    #il .values mi permette di salvare una serie di Pandas come vettore numpy
    ts_ret=Series(returns).values
    ts_vic=Series(victories).values
    ts_len=Series(lenght).values
    
    #print(ts_ret)
    
    l=len(ts_ret)
    il=iniziale
    #print(il-lo)
    
    ret_useful=ts_ret[il:l]
    vic_useful=ts_vic[il:l]
    len_useful=ts_len[il:l]
    
    #print(ret_useful)
    
    dati = np.column_stack([vic_useful, ret_useful, len_useful])
    
    #print(dati)
    
    #Vittorie
    wins=[]
    
    for i in range(l-il):
        if dati[i][0]==1:
            wins.append(dati[i])
    wins = np.array(wins)
    #print(wins[777])
    
    #Sconfitte
    loose=[]
    
    for i in range(l-il):
        if dati[i][0]==0:
            loose.append(dati[i])
    loose = np.array(loose)
    #print(loose[777])
    
    wins=np.transpose(wins)
    #print(wins)
    
    loose=np.transpose(loose)
    #print(loose)

    
    
    fig = plt.figure(dpi=400)
    plt.xlabel('Number of Episodes')
    plt.ylabel('Return Gained')
    plt.scatter(np.arange(len(wins[1])), wins[1], c=wins[2], s=1)
    plt.savefig('Vittorie.png')
    plt.close('all')
    
    fig = plt.figure(dpi=400)
    plt.xlabel('Number of Episodes')
    plt.ylabel('Return Gained')
    plt.scatter(np.arange(len(loose[1])), loose[1], c=loose[2], s=1)
    plt.savefig('Sconfitte.png')
    plt.close('all')
    
    
    m = min(len(wins[1]), len(loose[1]))
    vec1=wins[1]
    vec1=vec1[:m]
    vec2=loose[1]
    vec2=vec2[:m]
    vec3=wins[2]
    vec3=vec3[:m]
    vec4=loose[2]
    vec4=vec4[:m]
    
    fig = plt.figure(dpi=400)
    plt.xlabel('Number of Episodes')
    plt.ylabel('Return Gained')
    plt.scatter(np.arange(m), vec1, c=vec3, s=1)
    plt.scatter(np.arange(m), vec2, c=vec4, s=1)
    plt.savefig('Dispersion.png')
    plt.close('all')



def count(nome, path, iniziale=0):

    datas = read_csv(path + 'parametri.csv', header=0)
    victories = datas['vittorie']
    ts_vic=Series(victories).values
    l=len(ts_vic)
    m=np.average(ts_vic[iniziale:])
    print('Average percentage:', m*100)



    
        

    

    
#scattering('8scrambles_300.0dilataz_boost', '8scrambles_300.0dilataz_boost/', 2000,42500)

#graph('10scrambles_200000trials', '10scrambles_200000trials/', 10, 200000, 20000, 500)
    
    

    
    

    
    
    
    

    
    
    
            
          
