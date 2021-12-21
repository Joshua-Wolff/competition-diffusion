#include <iostream>
#include "Probleme.hpp"
#include "Vecteur.hpp"
#include "Matrice.hpp"
#include "Maillage.hpp"
using namespace std;

Matrice_pleine Probleme::assemblage_matrice(Matrice_pleine &Numtri, Matrice_pleine &Coorneu, int Nbpt, int Nbtri, int test)
{
        // si test=0 : matrice de raideur, si test = 1 : matrice de masse
        if (test == 0)
        {
            Matrice_pleine KK(Nbpt,Nbpt,0);
            for (int l = 1; l<Nbtri+1; l++)
            {
                Matrice_pleine Kel = matK_elem(Coorneu.ligne(Numtri(l,1)), Coorneu.ligne(Numtri(l,2)), Coorneu.ligne(Numtri(l,3)));

                for(int i = 1; i<4; i++)
                {
                    int I = Numtri(l,i);//à modifier
                    for(int j = 1; j<4; j++)
                    {
                        int J = Numtri(l,j);//àmodifier
                        KK(I,J) = KK(I,J)+Kel(i,j);  
                    }
                }
            }
            return KK;
        };

        if(test == 1)
        {
            Matrice_pleine MM(Nbpt,Nbpt,0);
            for (int l = 1; l<Nbtri+1; l++)
            {
                Matrice_pleine Mel = matM_elem(Coorneu.ligne(Numtri(l,1)),Coorneu.ligne(Numtri(l,2)),Coorneu.ligne(Numtri(l,3)));//à recoder, avec "vecteur colonne"

                for(int i = 1; i<4; i++)
                {
                    int I = Numtri(l,i);//àmodifier
                    for(int j = 1; j<4; j++)
                    {
                        int J = Numtri(l,j); //àmodifier// jème composante de la lème composante de Numtri (jeme sommet du lème triangle)
                        MM(I,J) = MM(I,J)+Mel(i,j);
                        
                    }
                }
            }
            return MM;
        };
        Matrice_pleine vide;
        return vide;
};
