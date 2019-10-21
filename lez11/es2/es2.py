import numpy as np
import matplotlib.pyplot as plt
import tensorflow as tf

import keras

from keras.models import Sequential
from keras.layers import Dense, Activation
from keras import backend as K
from keras.utils import get_custom_objects
from keras.utils.vis_utils import plot_model

#print(tf.VERSION)

# target parameters of f(x) = a + b*x + c*x**2 + d*x**3
a = 4
b = -3
c = -2
d = 3




training = 10000
ep = 1000

# generate training inputs
np.random.seed(0)
x_train = np.random.uniform(-1, 1, training)
x_valid = np.random.uniform(-1, 1, int(training/10))
x_valid.sort()
y_target = a + b * x_valid + c * x_valid*x_valid + d * x_valid*x_valid*x_valid # ideal (target) cubic function

sigma = 0.5 # noise standard deviation, for the moment it is absent
y_train = np.random.normal(a + b * x_train + c * x_train*x_train + d * x_train**3) # actual measures from which we want to guess regression parameters
y_valid = np.random.normal(a + b * x_valid + c * x_valid**2 + d * x_valid**3, sigma)

#print(y_train)
#plotting valid targets:
plt.plot(x_valid, y_target)
plt.scatter(x_valid, y_valid, color='r')
plt.grid(True)#; plt.show()
plt.savefig('Ideal target')
plt.close('all')

#install model sequential and 1 layer (with 1 neuron)
model = keras.Sequential()
model.add(Dense(1000, input_shape=(1,), activation='relu'))
model.add(Dense(500, activation='linear'))
model.add(Dense(250, activation='linear'))
model.add(Dense(1, activation='linear'))
plot_model(model, to_file='model_plot.png', show_shapes=True, show_layer_names=True)

# compile the model choosing optimizer, loss and metrics objects
model.compile(optimizer='sgd', loss='mse', metrics=['mse'])

model.summary()

history = model.fit(x=x_train, y=y_train, 
          batch_size=64, epochs=ep,
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



x_predicted = np.random.uniform(-1, 1, 1000)
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


 













