from scipy.integrate import odeint
import scipy.integrate as integrate
import matplotlib.pyplot as plt
import numpy as np
import math

def f(x, t):
    return math.sin(t)**2/x**2

x0 = 2
t = np.linspace(0, 2, num=100)
sol = odeint(f, x0, t)
plt.plot(t, sol)
plt.show()