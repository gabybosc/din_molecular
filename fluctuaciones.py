import numpy as np
import matplotlib.pyplot as plt
plt.ion()

def func_corr(x, k): 
    # x es la cadena de markov
	N = len(x)
	X = x[:N-k]
	Y = x[k:]
	mux = np.mean(X)
	muy = np.mean(Y)
	numerador = np.mean((X-mux)*(Y-muy))
	denominador = np.std(X)*np.std(Y)

	return(numerador/denominador)

datos = np.loadtxt("res/energiasL8.46T0.73.txt", skiprows= 2)

paso = 1

ecin = datos[:, 0]
epot = datos[:, 1]
etot = ecin+epot
h = datos[:, 2]
t = np.arange(0,paso*len(h),paso)

# a partir de 500 esta termalizado
K = ecin[500:]
V = epot[500:]
E = etot[500:]

k_max = 40
corr_K = np.zeros(k_max)
corr_V = np.zeros(k_max)
corr_E = np.zeros(k_max)
corr = np.zeros(k_max)

for i in range(k_max):
	corr_K[i] = func_corr(K,i)
	corr_V[i] = func_corr(V,i)
	corr_E[i] = func_corr(E,i)

for i in range(k_max):
	for j in range(int(len(E)/100)):
		corr[i] += func_corr(E[int(j*100):int((j+1)*100)],i)
corr = corr*100/len(E)

plt.plot(corr_K, '-.',label="K")
plt.plot(corr_V,'--',label="V")
plt.plot(corr_E,'--',label="E")
plt.plot(corr, '--', label="E promedio")
plt.legend()
plt.grid()
plt.xlabel("k")
plt.ylabel("C(k)")

# sin correlacion
sigma_K_0 = np.std(K)
sigma_V_0 = np.std(V)
sigma_E_0 = np.std(E)

#con correlacion, ver graficos para elegir el k de correlacion 0.1
k_corr = 20
sigma_K = np.std(np.array([K[k_corr*i] for i in range(int(len(K)/k_corr))]))
sigma_V = np.std(np.array([V[k_corr*i] for i in range(int(len(V)/k_corr))]))
sigma_E = np.std(np.array([E[k_corr*i] for i in range(int(len(E)/k_corr))]))