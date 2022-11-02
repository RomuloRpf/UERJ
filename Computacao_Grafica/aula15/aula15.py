import numpy as np
import matplotlib.pyplot as plt

p = np.array([[1,1,1],[1,2,1],[2, 2,1],[2,1,1]])
p = np.transpose(p)

#plt.figure(figsize=(5, 5))
#plt.title("Original")
#plt.xlim(-5, 5), plt.ylim(-5, 5)
#plt.axhline(linewidth=1), plt.axvline(linewidth=1)
#x_list = np.append(p[0,:], p[0,0])
#y_list = np.append(p[1,:], p[1,0])
#plt.plot(x_list, y_list , '-ro')
#plt.show()

Tt1 = np.array([[1,0,-1.5],
                [0,1,-1.5],
                [0,0,1]])

theta = 45
theta_rad = (theta/180) * np.pi
R = np.array([[np.cos(theta_rad), -np.sin(theta_rad), 0],
              [np.sin(theta_rad), np.cos(theta_rad), 0],
              [0,0,1]])

Tt2 = np.array([[1,0,1.5],
                [0,1,1.5],
                [0,0,1]])

Ttr = np.matmul(R,Tt1)
Ttrt = np.matmul(Tt2,Ttr)

pt = np.matmul(Ttrt, p)

plt.figure(figsize=(5, 5))
#plt.title("Transformado")
#plt.xlim(-5, 5), plt.ylim(-5, 5)
#plt.axhline(linewidth=1), plt.axvline(linewidth=1)
#x_list = np.append(pt[0,:], pt[0,0])
#y_list = np.append(pt[1,:], pt[1,0])
#plt.plot(x_list, y_list , '-ro')
#plt.show()

for theta in range(0,721,4):
    theta_rad = (theta/180) * np.pi
    R = np.array([[np.cos(theta_rad), -np.sin(theta_rad), 0],
                  [np.sin(theta_rad), np.cos(theta_rad), 0],
                  [0,0,1]])
    Ttr = np.matmul(R,Tt1)
    Ttrt = np.matmul(Tt2,Ttr)

    pt = np.matmul(Ttrt, p)
    
    plt.clf()
    plt.xlim(-5, 5), plt.ylim(-5, 5)
    plt.axhline(linewidth=1), plt.axvline(linewidth=1)
    x_list = np.append(pt[0,:], pt[0,0])
    y_list = np.append(pt[1,:], pt[1,0])
    plt.plot(x_list, y_list , '-ro')
    plt.show()
    plt.pause(0.001)