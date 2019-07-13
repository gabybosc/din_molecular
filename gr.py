import numpy as np
import matplotlib.pyplot as plt
plt.ion()

data = np.loadtxt("gr_rho0.6.dat")
r1 = data[:,0]
gr1 = data[:,1]

data = np.loadtxt("gr_rho0.8.dat")
r2 = data[:,0]
gr2 = data[:,1]

data = np.loadtxt("gr_rho1.dat")
r3 = data[:,0]
gr3 = data[:,1]

plt.plot(r1,gr1,label=0.6)
plt.plot(r2,gr2,label=0.8)
plt.plot(r3,gr3,label=1.0)
plt.legend()