########## README.txt ###############

######### GUIDE D'UTILISATION DE L'ALGORITHME DE RESOLUTION DES EQUATION DE COMPETITION DIFFUSION DE LOTKA VOLTERRA ########




1/ MAILLAGE

Le maillage est déjà disponible en format .txt (maillageSIM202.txt), il n'est à priori pas nécessaire de le modifier. (son pas est h=0.05)

Cependant si l'utilisateur souhaite le modifier, il suffit d'en créer un nouveau à partir de maillageSIM202.geo et de l'enregistrer au nom maillageSIM202.txt




2/ CHOIX DU PROBLEME A RESOUDRE

Il suffit d'initialiser une des chaînes de caractères en début de main.cpp à "oui" (il faut un unique "oui")

Exemple : le cas suivant permet d'effectuer la résolution du problème final :

string validation_poisson = "non"; //pas de couplage, stationnaire (résolution de l'équation de poisson)
string validation_sans_diffusion = "non"; //couplage, pas de diffusion, temporel
string validation_diffusion_seule = "non"; // pas de couplage, diffusion 
string resolution = "oui"; // couplage, diffusion 




3/ CHOIX DES PARAMETRES D'UN PROBLEME DONNÉ

a- Dans main.cpp :

L'utilisateur peut modifier les vecteurs U et V initiaux pour un problème donné. Si le problème est temporel il peut aussi fixer T_max (nombre d'incrémentation du pas temporel delta_T).

b- Dans Probleme.cpp :

L'utilisateur peut choisir les coefficients associés au différents problèmes (deux jeux de coefficients sont déjà proposés, l'un pour la vérification temporelle, l'autre pour la résolution du problème final)
L'utilisateur peut aussi fixer le pas de temps delta_T : on conseil delta_T=0.05 pour la vérification temporelle et delta_T=1 pour les deux autres problèmes.




4/ COMPILATION ET EXÉCUTION

Les fichiers à compiler sont :

- Vecteur.cpp 
- Matrice.cpp 
- Maillage.cpp 
- assemblage_mat.cpp 
- mat_elem.cpp 
- Probleme.cpp 
- main.cpp




5/ AFFICHAGE

Une fois le code compilé et executé, on récupère les résultats dans le fichier texte affichage.txt

4 codes d'affichage en python sont disponibles :

- affichage_poisson.py : pour le premier test
- affichage_euler.py : pour le second test
- affichage_diffusion_seule.py : pour le troisième test
- affichage_probleme.py : pour le problème final


De manière générale, X et Y représente les coordonnées des noeuds du maillage et Z le résultat (pour le premier test)
Si le problème est temporel on introduit Ui (et Vi) avec i un entier qui indique l'instant i*delta_T auquel on observe la solution





############################ FIN #######################################