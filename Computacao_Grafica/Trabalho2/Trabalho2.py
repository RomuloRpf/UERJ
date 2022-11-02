import numpy as np
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors


def on_press(event):
    global centro_x, centro_y
    centro_x = round(event.xdata,2)
    centro_y = round(event.ydata,2)
    print('Novo centro da figura: x =', centro_x,", y =",centro_y)


def on_key(event):
    global end_loop, theta, escala
   
    if event.key == "q":
        end_loop = True
        print("Programa Encerrado")
    elif event.key == "up":
        escala = escala + 0.5
        print("Escala:", escala)
    elif event.key == "down":
        if escala > 0.5:
            escala = escala - 0.5
            print("Escala:", escala)
    elif event.key == "left":
        theta = theta + 2
        print("Theta:", theta)
    elif event.key == "right":
        theta = theta - 2
        print("Theta:", theta)
    elif event.key == "escape":
        theta = 0
        print("Rotação Interrompida")
    

def Trabalho2(po):
    
    plt.close('all')           
    fig, ax = plt.subplots()    
    ax.cla()                    


    cid = fig.canvas.mpl_connect('button_press_event', on_press)
    cid = fig.canvas.mpl_connect('key_press_event', on_key)


    po = np.transpose(po)
    
    global centro_x, centro_y, escala, theta, end_loop
    
    centro_x = 0
    centro_y = 0

    escala = 1
    theta = 0
    angulo = 0
    cor = 0

    end_loop = False
    while not end_loop:
     
        if theta != 0:
            cor = cor + 0.3
        
        cor_rad = (cor/180) * np.pi
    
        ax.cla()  
        ax.set_xlim([-7, 7]), ax.set_ylim([-7, 7])
        ax.set_aspect(1)
        plt.axhline(linewidth=1), plt.axvline(linewidth=1)
        
        E = np.array([[escala,0,0],
                     [0,escala,0],
                     [0,0,1]])
    
        angulo = angulo + theta
        theta_rad = (angulo/180) * np.pi
    
        R = np.array([[np.cos(theta_rad), -np.sin(theta_rad), 0],
                      [np.sin(theta_rad), np.cos(theta_rad), 0],
                      [0,0,1]])
    
        Tra = np.array([[1,0,centro_x],
                        [0,1,centro_y],
                        [0,0,1]])
    
        Re = np.matmul(R, E)
        Tre = np.matmul(Tra, Re)
        pt = np.matmul(Tre, po)
        mcolors.hsv_to_rgb([1,1,1])
        plt.fill(pt[0,:], pt[1,:], facecolor = mcolors.hsv_to_rgb([abs(np.cos(cor_rad)),1,1]))
        plt.pause(0.01)
 
#po = np.array([[-0.5, -0.5, 1], [0.5, -0.5, 1], [0.5, 0.5, 1], [-0.5, 0.5, 1]])
#Trabalho2(np.array([[-0.5, -0.5, 1], [0.5, -0.5, 1], [0.5, 0.5, 1], [-0.5, 0.5, 1]]))
