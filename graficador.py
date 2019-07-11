import numpy as np
import matplotlib.pyplot as plt
plt.ion()

datos = np.loadtxt("energiasTs_N125L6.79.txt", skiprows= 2)

paso = 5

ecin = datos[:, 0]
epot = datos[:, 1]
etot = ecin+epot
h = datos[:, 2]
t = np.arange(0,paso*len(h),paso)

plt.figure(1)

plt.subplot(3,1,1)
plt.plot(t,ecin, '.')
#plt.plot([ecin[0] for i in range(len(ecin))],'r--')
plt.ylabel("K*")
plt.grid()

plt.subplot(3,1,2)
plt.plot(t,epot, '.')
#plt.plot([epot[0] for i in range(len(epot))],'r--')
plt.ylabel("V*")
plt.grid()

E0 = ecin[0]+epot[0]
plt.subplot(3,1,3)
plt.plot(t,etot, '.')
plt.plot(t,[etot[0] for i in range(len(etot))],'r--', label="$E_0$")
plt.ylim([int(etot[0])-1.5,int(etot[0])+0.5])
plt.ylabel("E*")
plt.xlabel(r"t* $\times10^{-3}$")
plt.grid()
plt.legend()

#plt.savefig("res/energiasL8.46T0.65.png",dpi=150)

plt.figure(2)
plt.plot(t,h,'.')
plt.xlabel(r"t* $\times10^{-3}$")
plt.ylabel("H")
plt.grid()
#plt.savefig("res/entropiaL8.46T0.65.png",dpi=150)
