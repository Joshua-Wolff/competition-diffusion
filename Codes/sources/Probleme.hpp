#ifndef PROBLEME_HPP
#define PROBLEME_HPP

#include <math.h>       /* sin */


#include <iostream>
#include "Vecteur.hpp"
#include "Matrice.hpp"
#include "Maillage.hpp"
using namespace std;

class Probleme
{
    public :

    double a, b, c, d; // coef utiles pour la construction du second membre
    double c_u;
    double c_v; 
    double delta_T; //pas de temps
    double alpha;
    double h ; //pas spatial 


    public :

    Probleme(); //contructeur par défaut (le fichier contient le nom du fichier texte du maillage)

    //assemblage de la matrice
    Matrice_pleine assemblage_matrice(Matrice_pleine &Numtri, Matrice_pleine &Coorneu, int Nbpt, int Nbtri, int test);//ajouteur Refneu
    //construction des seconds membres
    Vecteur assemblage_second_membre(Vecteur &V, Vecteur &U, int Nbpt, int test);

    Vecteur f(int Nbpt, Matrice_pleine Coorneu)
    {
        Vecteur A(Nbpt, 0);
        double pi=3.14159265358979323846;
        for (int i = 1; i <= Nbpt; i++)
        {   
            double x = Coorneu(i, 1);
            double y = Coorneu(i, 2);
            //A(i)=pi*pi*sin(pi*x/10)*sin(pi*y/10)/5;   
            A(i)=2*pi*pi*sin(pi*x)*sin(pi*y); 
        }

        return A;
    };

    Vecteur g(int Nbpt, Matrice_pleine Coorneu)
    {
        Vecteur A(Nbpt, 0);
        double pi=3.14159265358979323846;
        for (int i = 1; i <= Nbpt; i++)
        {   
            double x = Coorneu(i, 1);
            double y = Coorneu(i, 2);
            //A(i)=pi*pi*sin(pi*x/10)*sin(pi*y/10)/5;   
            A(i)=0.4*sin(pi*x)*sin(pi*y)+0.5; 
        }

        return A;
    };



    //PSEUDO ELIMINATION
    //pour une matrice
    Matrice_pleine elimine_M(Matrice_pleine M, Vecteur Points_du_bord, int Nbpt)
    {
        Matrice_pleine A(M);
        int n = Points_du_bord.dim();
        //Vecteur Z(Nbpt, 0);
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= Nbpt; j++)
            {
                if (Points_du_bord(i) == j)
                {
                    for(int k=1;k<=Nbpt;k++)
                    {
                        A(j,k)=0;
                        A(k,j)=0;
                    }
                    //A.ligne(j) = Z;
                    //A.colonne(j) = Z;
                }
            }

        }
        return A;
    }
    //pour un vecteur
    Vecteur elimine_V(Vecteur V, Vecteur Points_du_bord, int Nbpt)
    {
        Vecteur L(V);
        int n = Points_du_bord.dim();
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= Nbpt; j++)
            {
                if (Points_du_bord(i) == j)
                {
                    L(j) = 0;
                }
            }
        }

        return L;
    }

    Matrice_pleine matK_elem(Vecteur V1, Vecteur V2, Vecteur V3);
    Matrice_pleine matM_elem(Vecteur V1, Vecteur V2, Vecteur V3);

};





#endif
