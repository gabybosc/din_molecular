import numpy as np
import matplotlib.pyplot as plt
plt.ion()

datos = np.loadtxt("energiasL8.46T1.5.txt", skiprows= 2)

ecin = datos[:, 0]
epot = datos[:, 1]
etot = ecin+epot

sigma = np.zeros(len(epot)-20)

for i in range(len(epot)-20):
    sigma[i] = np.std(epot[i:i+20])


buffer = np.zeros(len(sigma))

for i in range(len(buffer)-1):
    if sigma[i+1]<0.1*np.where(sigma == max(sigma))[0][0]:
        buffer[i] = 1
    else:
        buffer[i] = 0

booleano = buffer*sigma
plt.figure()
plt.plot(sigma)
plt.plot(booleano, '.r')
