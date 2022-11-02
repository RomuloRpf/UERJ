import numpy as np
import matplotlib.pyplot as plt

#Criando um ponto
p = np.array([[1, 1]])
p = np.transpose(p)

#plt.figure(figsize=(5, 5))
#plt.xlim(-5, 5), plt.ylim(-5, 5)
#plt.axhline(), plt.axvline()
#plt.plot(p[0, 0], p[1, 0], 'bo')
#plt.show()

#Rotacionando em 90 graus o ponto
theta = 90
theta_rad = (theta/180) * np.pi

R = np.array([[np.cos(theta_rad), -np.sin(theta_rad)],
              [np.sin(theta_rad), np.cos(theta_rad)]])

pT = np.matmul(R,p)
#plt.figure(figsize=(5, 5))
#plt.xlim(-5, 5), plt.ylim(-5, 5)
#plt.axhline(), plt.axvline()
#plt.plot(pT[0, 0], pT[1, 0], 'ro')
#plt.show()

#Criando um quadrado
#p = np.array([[-0.5,-0.5],[0.5,-0.5],[0.5, 0.5],[-0.5,0.5]])
p = np.array([[0,0],[1,0],[1, 1],[0,1]])
p = np.transpose(p)

#plt.figure(figsize=(5, 5))
#plt.xlim(-5, 5), plt.ylim(-5, 5)
#plt.axhline(), plt.axvline()
#x_list = np.append(p[0,:], p[0,0])
#y_list = np.append(p[1,:], p[1,0])
#plt.plot(x_list, y_list , '-ro')
#plt.show()

#Rotacionando em 45 graus o Quadrado
theta = 45
theta_rad = (theta/180) * np.pi

R = np.array([[np.cos(theta_rad), -np.sin(theta_rad)],
              [np.sin(theta_rad), np.cos(theta_rad)]])

pT = np.matmul(R,p)
#plt.figure(figsize=(5, 5))
#plt.xlim(-5, 5), plt.ylim(-5, 5)
#plt.axhline(), plt.axvline()
#x_list = np.append(pT[0,:], pT[0,0])
#y_list = np.append(pT[1,:], pT[1,0])
#plt.plot(x_list, y_list , '-bo')
#plt.show()

#Animação de rotação do Quadrado
plt.figure(figsize=(5, 5))

for theta in range(0,721,6):
    theta_rad = (theta/180) * np.pi
    R = np.array([[np.cos(theta_rad), -np.sin(theta_rad)],
              [np.sin(theta_rad), np.cos(theta_rad)]])
    pT = np.matmul(R,p)
    plt.clf()
    plt.xlim(-5, 5), plt.ylim(-5, 5)
    plt.axhline(), plt.axvline()
    x_list = np.append(pT[0,:], pT[0,0])
    y_list = np.append(pT[1,:], pT[1,0])
    plt.plot(x_list, y_list , '-bo')
    plt.show()
    plt.pause(0.01)