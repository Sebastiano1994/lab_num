import numpy as np
import matplotlib.pyplot as plt
import tensorflow as tf

import keras

from keras.models import Sequential
from keras.layers import Dense, Activation
from keras import backend as K
from keras.utils import get_custom_objects


print(tf.VERSION)

# target parameters of f(x) = m*x + b
m = 2 # slope
b = 1 # intersect

training = 10000
ep = 50

# generate training inputs
np.random.seed(0)
x_train = np.random.uniform(-1, 1, training)
x_valid = np.random.uniform(-1, 1, 10)
x_valid.sort()
y_target = m * x_valid + b # ideal (target) linear function

sigma = 1.0 # noise standard deviation, for the moment it is absent
y_train = np.random.normal(m * x_train + b, sigma) # actual measures from which we want to guess regression parameters
y_valid = np.random.normal(m * x_valid + b, sigma)

#plotting valid targets:
plt.plot(x_valid, y_target)
plt.scatter(x_valid, y_valid, color='r')
plt.grid(True); plt.show()


#install model sequential and 1 layer (with 1 neuron)
model = keras.Sequential()
model.add(Dense(1, input_shape=(1,)))



# compile the model choosing optimizer, loss and metrics objects
model.compile(optimizer='sgd', loss='mse', metrics=['mse'])

history = model.fit(x=x_train, y=y_train, 
          batch_size=32, epochs=ep,
          shuffle=True, # a good idea is to shuffle input before at each epoch
          validation_data=(x_valid, y_valid))

model.get_weights()

# evaluate model
score = model.evaluate(x_valid, y_valid, batch_size=32, verbose=0)

# print performance
print()
print('Test loss:', score[0])
print('Test accuracy:', score[1])


# look into training history
# Plot training & validation loss values
plt.plot(history.history['loss'])
plt.plot(history.history['val_loss'])
plt.title('Model loss')
plt.ylabel('Loss')
plt.xlabel('Epoch')
plt.legend(['Train', 'Test'], loc='best')
#plt.show()
plt.savefig('Model loss')
plt.close('all')



x_predicted = np.random.uniform(-1, 1, 100)
y_predicted = model.predict(x_predicted)
plt.scatter(x_predicted, y_predicted,color='r')
plt.plot(x_valid, y_target)
plt.grid(True)
#plt.show()
plt.savefig('Predicted vs True')
plt.close('all')




with open('param.txt', 'w') as f:
    f.write('Training points: ' + str(training) + '\n')
    f.write('Epochs: ' + str(ep) + '\n')
    f.write('Noise: ' + str(sigma)  + '\n')
    f.write('Test loss: ' + str(score[0])  + '\n')
    f.write('Test accuracy:' + str(score[1])  + '\n')


 













