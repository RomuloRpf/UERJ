import numpy as np
import matplotlib.pyplot as plt

#Criando um quadrado
#p = np.array([[-0.5,-0.5],[0.5,-0.5],[0.5, 0.5],[-0.5,0.5]])
p = np.array([[0,0],[1,0],[1, 1],[0,1]])
p = np.transpose(p)

plt.figure(figsize=(5, 5))
plt.xlim(-5, 5), plt.ylim(-5, 5)
plt.axhline(), plt.axvline()
x_list = np.append(p[0,:], p[0,0])
y_list = np.append(p[1,:], p[1,0])
plt.plot(x_list, y_list , '-bo')
plt.show()

#Cisalhamento vertical
sv = 1.2
Cv = np.array([[1,0],
              [sv,1]])

pT = np.matmul(Cv,p)

plt.figure(figsize=(5, 5))
plt.xlim(-5, 5), plt.ylim(-5, 5)
plt.axhline(), plt.axvline()
x_list = np.append(pT[0,:], pT[0,0])
y_list = np.append(pT[1,:], pT[1,0])
plt.plot(x_list, y_list , '-ro')
plt.show()

#Escala
E = np.array([[2,0],
              [0,1.5]])

pT = np.matmul(E,p)

plt.figure(figsize=(5, 5))
plt.xlim(-5, 5), plt.ylim(-5, 5)
plt.axhline(), plt.axvline()
x_list = np.append(pT[0,:], pT[0,0])
y_list = np.append(pT[1,:], pT[1,0])
plt.plot(x_list, y_list , '-ro')
plt.show()