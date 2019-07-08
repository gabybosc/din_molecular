import numpy as np
import matplotlib.pyplot as plt
plt.ion()

datos = np.loadtxt("energias.txt", skiprows= 2)

ecin = datos[:, 0]
epot = datos[:, 1]

plt.figure()

plt.subplot(3,1,1)
plt.plot(ecin, '.')
plt.plot([ecin[0] for i in range(len(ecin))],'r--')
plt.ylabel("K")
plt.grid()

plt.subplot(3,1,2)
plt.plot(epot, '.')
plt.plot([epot[0] for i in range(len(epot))],'r--')
plt.ylabel("V")
plt.grid()

E0 = ecin[0]+epot[0]
plt.subplot(3,1,3)
plt.plot(ecin+epot, '.')
plt.plot([E0 for i in range(len(ecin))],'r--')
plt.ylim([int(E0)-1,int(E0)])
plt.ylabel("E")
plt.grid()

#plt.savefig("energias.png",dpi=150)