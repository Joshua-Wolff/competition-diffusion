#### Lecture fichier texte et affichage 
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


fig = plt.figure()
ax =fig.gca(projection='3d')    

X,Y,U0,U1,U2,U3=np.loadtxt('affichage.txt')

Z1=10*np.sin(np.pi*X/10)*np.sin(np.pi*Y/10)

ax.plot_trisurf(X,Y,U3,cmap=plt.cm.CMRmap)
