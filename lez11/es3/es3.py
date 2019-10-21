import numpy as np
import matplotlib.pyplot as plt
import tensorflow as tf

import keras

from keras.models import Sequential
from keras.layers import Dense, Activation, Input
from keras import backend as K
from keras.utils import get_custom_objects
from math import sin
from mpl_toolkits.mplot3d import Axes3D





training = 10000
ep = 20


# generate training inputs
np.random.seed(0)
x_train = np.random.uniform(-np.pi/2, np.pi/2, training)

y_train = np.random.uniform(-np.pi/2, np.pi/2, training)

x_valid = np.random.uniform(-np.pi/2, np.pi/2, 1000)
y_valid = np.random.uniform(-np.pi/2, np.pi/2, 1000)
x_valid.sort()
y_valid.sort()
z_target = np.sin(x_valid**2+y_valid**2) # ideal (target) sinusoidal function

sigma = 0.0 # noise standard deviation, for the moment it is absent
z_train = np.random.normal(np.sin(x_train**2+y_train**2), sigma) # actual measures from which we want to guess regression parameters
z_valid = np.random.normal(np.sin(x_valid**2+y_valid**2), sigma)

All = np.array([y_train, x_train]).transpose()
All_valid = np.array([y_valid, x_valid]).transpose()


X,Y=np.meshgrid(x_valid,y_valid)
Z = np.sin(X**2+Y**2)

fig=plt.figure()
ax=fig.gca(projection='3d')
ax.plot_wireframe(X,Y,Z)
plt.grid(True)
plt.savefig('True')
plt.close('all')



model = keras.Sequential()
model.add(Dense(1000, input_shape=(2,), activation='relu'))
model.add(Dense(500,  activation='relu'))
model.add(Dense(250,  activation='linear'))
model.add(Dense(1, activation='linear'))

# compile the model choosing optimizer, loss and metrics object
model.compile(optimizer='sgd', loss='mse', metrics=['mse', 'acc'])


model.summary()


history = model.fit(All, y=z_train,
          batch_size=64, epochs=ep,
          shuffle=True, # a good idea is to shuffle input before at each epoch
          validation_data=(All_valid,z_valid))




model.get_weights()



score = model.evaluate(All_valid, z_valid, batch_size=32, verbose=1)


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
plt.show()



x_predicted = np.random.uniform(-np.pi/2, np.pi/2, 1000)
y_predicted = np.random.uniform(-np.pi/2, np.pi/2, 1000)
x_predicted.sort()
y_predicted.sort()
All_pred = np.array([y_predicted, x_predicted]).transpose()
X, Y = np.meshgrid(x_predicted,y_predicted)
#All_pred = np.array(X, Y).transpose
z_predicted = model.predict(All_pred)

fig=plt.figure()
ax=fig.gca(projection='3d')
ax.plot_wireframe(X,Y,z_predicted)
plt.savefig('Predicted vs True_3D')
plt.close('all')
#plt.show()





plt.scatter(x_predicted, z_predicted,color='r')
plt.plot(x_valid, z_target)
plt.grid(True)
#plt.show()
plt.savefig('Predicted vs True_x')
plt.close('all')


plt.scatter(y_predicted, z_predicted,color='r')
plt.plot(y_valid, z_target)
plt.grid(True)
#plt.show()
plt.savefig('Predicted vs True_y')
plt.close('all')
















