import numpy as np
import matplotlib.pyplot as plt
plt.ion()

T0 = np.array([0.65, 0.728, 0.81, 0.9, 1.1, 1.2, 1.5])
Etot = np.array([-2389.82426844, -2380.12811121, -2378.87515017, -2369.04521616, -2356.16541424, -2363.324558656156, -2324.00677881])
Ecin = np.array([367.99652661, 390.64260725, 370.81563191, 385.01804825, 405.4196597, 407.0207115755756, 414.77922413])

Ts = 2*Ecin / (3*512)
E = Etot/512

recta = np.polyfit(Ts, E, 1)
plt.plot(Ts,E,'.')

x = np.linspace(min(Ts),max(Ts),10)
plt.plot(x,recta[0]*x+recta[1])

# la pendiente da 1.5109721744454856