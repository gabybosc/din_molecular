import numpy as np
import matplotlib.pyplot as plt
plt.ion()

datos = np.loadtxt("res/energiasL8.46T0.73.txt", skiprows= 2)

paso = 1

ecin = datos[:, 0]
epot = datos[:, 1]
etot = ecin+epot
h = datos[:, 2]
pres = datos[:, 2]
t = np.arange(0,paso*len(h),paso)
Ts = np.arange(2.0,0.35,-0.1)

fig1,ax1 = plt.subplots()
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
plt.xlabel("t*")
plt.text(1.1, -0.1, r"$\times10^{-3}$",horizontalalignment='right',verticalalignment='bottom', transform=ax1.transAxes)
plt.grid()
plt.legend()

fig2,ax2 = plt.subplots()
plt.plot(t,h,'.')
plt.xlabel("t*")
plt.ylabel("H")
plt.text(1.1, -0.1, r"$\times10^{-3}$",horizontalalignment='right',verticalalignment='bottom', transform=ax2.transAxes)
plt.grid()
