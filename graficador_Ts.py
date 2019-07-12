import numpy as np
import matplotlib.pyplot as plt
plt.ion()

datos = np.loadtxt("energiasTs_N125L6.79.txt", skiprows= 2)

N_verlet = 500
paso = 5 #cada cuantos guardo las energias

ecin = datos[:, 0]
epot = datos[:, 1]
etot = ecin+epot
h = datos[:, 2]
pres = datos[:, 2]
t = np.arange(0,paso*len(h),paso)
Ts = np.arange(2.0,0.39,-0.1)

fig1,ax1 = plt.subplots()

for j,temp in enumerate(Ts):
	i_min = j*int(N_verlet/paso)
	i_max = (j+1)*int(N_verlet/paso)
	plt.plot(t[i_min:i_max],ecin[i_min:i_max], '.', label=temp)

plt.ylabel("K*")
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
