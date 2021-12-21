#### Lecture fichier texte et affichage 
import numpy as np
import matplotlib.pyplot as plt


X=np.loadtxt('affichage.txt')
tmax=int(X[0])
dt=float(X[1])
X=list(X[2:])

prey=[]
pred=[]
n=len(X)

for i in range(0,n):
    if i%2==0:
        prey.append(X[i])
    else:
        pred.append(X[i])
        
time=[dt*i for i in range(0,tmax+1)]


plt.plot(time,prey,label="Proies")
plt.plot(time,pred,label="Prédateurs")
plt.xlabel("temps")
plt.ylabel("taille des populations")
plt.title("a=4; b=2 ; c=2 ; d=1 ; dt = 0.05 (500 périodes)")
plt.legend()
plt.show()





