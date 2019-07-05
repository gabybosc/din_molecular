import numpy as np
import matplotlib.pyplot as plt
plt.ion()

datos = np.loadtxt("energias.txt", skiprows= 2)

ecin = datos[:, 0]
epot = datos[:, 1]
etot = datos[:, 2]

plt.figure()
plt.subplot(3,1,1)
plt.plot(ecin, '.',label="Ecin")
plt.legend()
plt.subplot(3,1,2)
plt.plot(epot, '.',label="Epot")
plt.legend()
plt.subplot(3,1,3)
plt.plot(etot, '.',label="E")
# plt.plot(epot*2+ecin, '.',label="E manual")
plt.legend()
