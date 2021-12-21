#### Lecture fichier texte et affichage 
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


fig = plt.figure()
ax =fig.gca(projection='3d')    

X,Y,U0,V0,U1,V1,U2,V2,U3,V3,U4,V4,U5,V5=np.loadtxt('affichage.txt')
Z=0*X

ax.plot_trisurf(X,Y,Z,cmap=plt.cm.CMRmap)

ax.plot_trisurf(X,Y,V2,cmap=plt.cm.Spectral)
ax.plot_trisurf(X,Y,U2,cmap=plt.cm.CMRmap)



