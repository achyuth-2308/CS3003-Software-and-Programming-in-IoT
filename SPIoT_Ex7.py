# This code contains the implementation of PID Controller for Temperature Regulation.
# Simulating a PID controller for temperature regulation in a thermal system using Python, analyzing system response and control performance over time.

import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import odeint

# System parameters
T_ambient = 25.0  # Ambient temperature in °C
K = 1.0           # System gain
tau = 50.0        # Time constant in seconds
T_set = 100.0     # Desired temperature (setpoint) in °C

# PID controller parameters
Kp = 2.0          # Proportional gain
Ki = 1.0          # Integral gain
Kd = 0.5          # Derivative gain

# PID controller implementation
def pid_control(e, e_prev, integral, dt):
    derivative = (e - e_prev) / dt
    integral += e * dt
    u = Kp * e + Ki * integral + Kd * derivative
    return u, integral

# System model
def thermal_system(T, t, u):
    dTdt = -(T - T_ambient) / tau + K * u / tau
    return dTdt

# Simulation parameters
dt = 0.1  # Time step in seconds
time = np.arange(0, 500, dt)  # Simulation time array
T = np.zeros_like(time)  # Array to hold temperature values
e_prev = 0.0  # Previous error
integral = 0.0  # Integral of error

# Initial temperature
T[0] = T_ambient  # Start at ambient temperature

# Simulation loop
for i in range(1, len(time)):
    e = T_set - T[i-1]  # Calculate error
    u, integral = pid_control(e, e_prev, integral, dt)  # PID control
    e_prev = e  # Update previous error
    T[i] = odeint(thermal_system, T[i-1], [0, dt], args=(u,))[-1]  # Update temperature

# Plotting results
plt.figure(figsize=(10, 5))
plt.plot(time, T, label='Temperature (°C)')
plt.axhline(T_set, color='r', linestyle='--', label='Setpoint (°C)')
plt.title('PID Controller for Thermal System')
plt.xlabel('Time (s)')
plt.ylabel('Temperature (°C)')
plt.legend()
plt.grid()
plt.show()
