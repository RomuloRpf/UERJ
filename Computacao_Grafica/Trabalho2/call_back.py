# Exemplos de call-backs do Matplotlib para a interação com o usuário
# Para terminar o programa, pressione a tecla 'a'

import numpy as np
import matplotlib.pyplot as plt

# Função que gerencia eventos do mouse


def on_press(event):
    print('Você pressionou o botão do mouse:',
          event.button, event.xdata, event.ydata)

# Função que gerencia eventos do teclado


def on_key(event):
    global end_loop
    print('Você pressionou a tecla: "', event.key,
          '"', event.xdata, event.ydata)
    if event.key == 'q':
        end_loop = True


plt.close('all')            # Fecha todas as figuras abertas
fig, ax = plt.subplots()    # Instancia objetos: figura e eixos correspondentes
ax.cla()                    # Limpa figura/eixos

# Conecta call backs associados aos eventos (mouse e teclado)
cid = fig.canvas.mpl_connect('button_press_event', on_press)
cid = fig.canvas.mpl_connect('key_press_event', on_key)

# Pontos de um quadrado unitário
po = np.array([[-0.5, -0.5, 1], [0.5, -0.5, 1], [0.5, 0.5, 1], [-0.5, 0.5, 1]])
po = np.transpose(po)

# Propriedades dos eixos da figura
ax.set_xlim([-7, 7]), ax.set_ylim([-7, 7])
ax.set_aspect(1)
plt.axhline(linewidth=1), plt.axvline(linewidth=1)

# Desenha pontos
plt.plot(po[0, :], po[1, :], 'ro')
# plt.show()

# O loop acaba quando a tecla "q" é pressionada
#end_loop = False
# while not end_loop:
#    plt.pause(0.01)
