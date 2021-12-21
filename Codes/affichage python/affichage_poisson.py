#### Lecture fichier texte et affichage 
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


fig = plt.figure()
ax =fig.gca(projection='3d')    

X,Y,Z=np.loadtxt('affichage.txt')


Z1=10*np.sin(np.pi*X/10)*np.sin(np.pi*Y/10)
Z2=np.sin(np.pi*X)*np.sin(np.pi*Y)




ax.plot_trisurf(X,Y,Z,cmap=plt.cm.CMRmap)