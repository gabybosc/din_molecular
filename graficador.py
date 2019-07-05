import numpy as np
import matplotlib.pyplot as plt
plt.ion()

datos = np.loadtxt("energias.txt", skiprows= 2)

ecin = datos[:, 0]
epot = datos[:, 1]
etot = datos[:, 2]

plt.figure()
plt.subplot(3,1,1)
plt.plot(ecin, '.')
plt.ylabel("K")
plt.subplot(3,1,2)
plt.plot(epot, '.')
plt.ylabel("V")
plt.subplot(3,1,3)
plt.plot(etot, '.')
plt.ylabel("E")
