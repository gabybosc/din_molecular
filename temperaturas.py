import numpy as np
import matplotlib.pyplot as plt
plt.ion()

# lista = [40, 45, 50, 55, 60]
# for rho in lista:
rho = 40
temperaturas = np.arange(0.5, 2.1, 0.1)
temperaturas = temperaturas[::-1]
i = 0

cinetica = np.zeros(len(temperaturas))
energia = np.zeros(len(temperaturas))
entropia = np.zeros(len(temperaturas))
presion = np.zeros(len(temperaturas))

for j in range(len(temperaturas)):
    datos = np.loadtxt(f'datos/energiasTs_N125rho0.{rho}.txt', skiprows = 2)

    Ecin = datos[:,0]
    Epot = datos[:,1]
    Etot = Ecin+Epot
    H = datos[:,2]
    P = datos[:,3]
    Ecin_cut = Ecin[i:i+100]
    Epot_cut = Epot[i:i+100]
    Etot_cut = Epot_cut + Ecin_cut
    H_cut = H[i:i+100]
    P_cut = P[i:i+100]
    i += 100

    cinetica[j] = np.mean(Ecin_cut)
    energia[j] = np.mean(Etot_cut)
    entropia[j] = np.mean(H_cut)
    presion[j] = np.mean(P_cut)



plt.figure(1)
plt.plot(temperaturas, energia, label = rf'$\rho$ = 0.{rho}')
plt.legend()
plt.xlabel('Temperatura')
plt.ylabel('Energía total')
plt.title(r'Energía total en función de la temperatura para distintos valores de  $\rho$')

plt.figure(0)
plt.plot(temperaturas, cinetica, label = rf'$\rho$ = 0.{rho}')
plt.legend()
plt.xlabel('Temperatura')
plt.ylabel('Energía cinetca')
plt.title(r'Energía cinetica en función de la temperatura para distintos valores de  $\rho$')


plt.figure(2)
plt.plot(temperaturas, entropia,  label = rf'$\rho$ = 0.{rho}')
plt.legend()
plt.xlabel('Temperatura')
plt.ylabel('H')
plt.title(r'Entropía en función de la temperatura para distintos valores de  $\rho$')

plt.figure(3)
plt.plot( temperaturas, presion, label = rf'$\rho$ = 0.{rho}')
plt.legend()
plt.xlabel('Temperatura')
plt.ylabel('P')
plt.title(r'Presión en función de la temperatura para distintos valores de $\rho$')
