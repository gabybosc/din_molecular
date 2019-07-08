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
plt.plot([ecin[0] for i in range(len(ecin))],'k')
#plt.xlim([0,50])
#plt.ylim([-10000,100000])
plt.ylabel("K")
plt.grid()

plt.subplot(3,1,2)
plt.plot(epot, '.')
plt.plot([epot[0] for i in range(len(epot))],'r')
#plt.xlim([0,50])
#plt.ylim([100000,300000])
plt.ylabel("V")
plt.grid()

plt.subplot(3,1,3)
plt.plot(etot, '.')
plt.plot([etot[0] for i in range(len(ecin))],'r')
#plt.xlim([0,50])
#plt.ylim([100000,300000])
plt.ylabel("E")
plt.grid()

#plt.savefig("energias.png",dpi=150)