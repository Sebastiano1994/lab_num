###############################################################################
# The copyright of this code, including all portions, content, design, text,  #
# output and the selection and arrangement of the subroutines is owned by     #
# the Authors and by CNR, unless otherwise indicated, and is protected by the #
# provisions of the Italian Copyright law.                                    #
#                                                                             #
# All rights reserved. This software may not be reproduced or distributed, in #
# whole or in part, without the prior written permission of the Authors.      #
# However, reproduction and distribution, in whole or in part, by non-profit, #
# research or educational institutions for their own use is permitted if      #
# proper credit is given, with full citation, and copyright is acknowledged.  #
# Any other reproduction or distribution, in whatever form and by whatever    #
# media, is expressly prohibited without the prior written consent of the     #
# Authors. For further information, please contact CNR.                       #
# Contact person:           enrico.prati@cnr.it                               #
#                                                                             #
# Concept and development:  Sebastiano Corli, Enrico Prati                    #
# Year:                     2019                                              #
# Istituto di Fotonica e Nanotecnologie - Consiglio Nazionale delle Ricerche  #
###############################################################################


import random as rdm
import numpy as np
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import *
from tensorflow.keras.optimizers import *
from tensorflow.keras.models import load_model
from tensorflow.keras.utils import plot_model
import collections
import sys, os
sys.path.append(os.path.dirname(__file__) + "../..")
from operators_ed import Operators
from cube_ed import Cube







class Brain:
    def __init__(self):
        self.model=self.rete() #model è il grafo creato da rete
    
    def rete(self):
        model = Sequential() #dico che voglio un feed-forward (rete sequenziale, non ricorrente)
        model.add(Dense(510, input_dim=60, activation='relu')) #80=12x4+8x4
        model.add(Dense(205, activation='relu'))
        model.add(Dense(8, activation='linear'))  #i miei possibili stati di outcome
        plot_model(model, to_file='model_rete.png', show_shapes=True, show_layer_names=True)
        opt = Adam(0.001)                                     #optimizer: strategia per trovare i migliori parametri per risolvere il mio problema; 0.01 è il learning rate
        model.compile(loss='mse', optimizer=opt)        #mse: minimizza il minime square error
       
        return model

    def train(self, x, y):
        self.model.fit(x,y, batch_size=32, verbose=0) #batch_size = numero di x,y che la gpu userà per il processo di ottimizzazione della rete

    def predict(self, S):
        return self.model.predict(S)

    def predictOne(self, S):
        #reshape prende un vettore e me lo trasforma, flatten mi schiaccia tutto come vettore (è un metodo di reshape)
        return np.argmax(self.predict(S.reshape(1, 60)).flatten())







class Memory:
    def __init__(self, max_capacity=50000): #quando passo un parametro di default definito (come max_capacity nel qui caso), sempre in fondo
        self.max_capacity=max_capacity
        self.samples=collections.deque(maxlen=self.max_capacity)

    def add(self, sample):
        self.samples.append(sample)

    def sample(self, n):
        n=min(n, len(self.samples))
        return rdm.sample(self.samples,n)


#Definisco l'agente:
class Agent:
    def __init__(self, prob,q=0):
	    self.prob=prob
	    self.brain=Brain()
	    self.brain_target=Brain()
	    self.Qval=q
	    self.memory=Memory()
	    
    def update(self):
        self.brain_target.model.set_weights(self.brain.model.get_weights())
	    
        
        
    def replay(self):


        batch = self.memory.sample(32)
        # Necessary because our memory could have less than batch.size elements
        batchLen = len(batch)

        states  = np.array([ i[0] for i in batch ]) #lista di tutti gli ultimi batchLen stati
        states_ = np.array([ o[3] for o in batch ])
	    # Contengono le predizioni (q-value) del target_brain per gli stati del batch
        predicted_states1  = self.brain.predict(states)
        predicted_states_1 = self.brain.predict(states_)
        
        #seconda rete
        predicted_states2  = self.brain_target.predict(states_)

        x = np.zeros((batchLen, 60)) # matrix batchLen x self.target_brain.input_dim
        y = np.zeros((batchLen, 8)) # matrix batchLen x len(self.base_gates)

	    #for i in range(len(batch))
	    #for o in batch

        for i, o in enumerate(batch):
            # o = (s,a,r,s_) di ogni elemento di batch
            s = o[0]; a = o[1]; r = o[2]; s_ = o[3]; d = o[4]

            #print('LA REWARD VALE', r)
            target = predicted_states1[i];
            

            if d is True:
                target[a] = r
            else:
                act    = np.argmax(predicted_states_1[i])
                target[a] = r +  0.99* predicted_states2[i][act]

            x[i] = s
            y[i] = target


        #vettore per prendere tutti i qvalue massimi dell'azione che lo massimizza per ogni batch:
        q = np.asarray([max(a) for a in y])
        #di questo vettore ne estrapolo la media:
        self.Qval=np.average(q)
        self.brain.train(x, y)




    def choose(self, state):
	    if self.prob<rdm.random():
		    action=self.brain.predictOne(state)
	    else:
		    action=rdm.randint(0, 6 +1)
	    
	    return action
