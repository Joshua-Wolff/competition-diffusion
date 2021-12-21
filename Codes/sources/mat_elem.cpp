#include <iostream>
#include <cmath>
#include "Probleme.hpp"
#include "Vecteur.hpp"
#include "Matrice.hpp"
#include "Maillage.hpp"
#include <math.h>
using namespace std;

//matrice de raideur élémentaire
Matrice_pleine Probleme::matK_elem(Vecteur V1, Vecteur V2, Vecteur V3)

{
    double x1 = V1(1); double y1 = V1(2);
    double x2 = V2(1); double y2 = V2(2);
    double x3 = V3(1); double y3 = V3(2);

    double D = ((x2-x1)*(y3-y1) - (y2-y1)*(x3-x1)); //déterminant de Bl

    Vecteur emile(3,0); // vecteur des hauteurs issues des sommets du triangle
    emile(1)=sqrt(pow(x3-x2,2)+pow(y3-y2,2))/D;
    emile(2)=sqrt(pow(x3-x1,2)+pow(y3-y1,2))/D;
    emile(3)=sqrt(pow(x1-x2,2)+pow(y1-y2,2))/D;

    

    Matrice_pleine Bl(2,2,0);
    Bl(1,1) = x2-x1; Bl(1,2) = x3-x1;
    Bl(2,1) = y2-y1; Bl(2,2) = y3-y1;

    Matrice_pleine inv_Bl ;//inverse de la transposée de Bl
    Bl = tr(Bl);
    inv_Bl = inv(Bl);

    Matrice_pleine grad_w(3,2,0);

    grad_w(1,1) = -1*emile(1); grad_w(1,2) = -1*emile(1);
    grad_w(2,1) = 1*emile(1); grad_w(3,2) = 1*emile(1);

    Matrice_pleine Kel(3,3,0);
    for (int i = 1; i<4; i++)
    {
        for (int j =1; j<4; j++)
        {
            Vecteur A = inv_Bl*grad_w.ligne(i);
            Vecteur B = inv_Bl*grad_w.ligne(j);
            Kel(i,j) = (A|B)*abs(D)*0.5;
        }
    }
    return Kel;
}

//matrice de masse élémentaire
Matrice_pleine Probleme::matM_elem(Vecteur V1, Vecteur V2, Vecteur V3)
{
    double x1 = V1(1); double y1 = V1(2);
    double x2 = V2(1); double y2 = V2(2);
    double x3 = V3(1); double y3 = V3(2);

    double D = ((x2-x1)*(y3-y1) - (y2-y1)*(x3-x1)); //déterminant

    Vecteur emile(3,0); // vecteur des hauteurs issues des sommets du triangle
    emile(1)=sqrt(pow(x3-x2,2)+pow(y3-y2,2))/D;
    emile(2)=sqrt(pow(x3-x1,2)+pow(y3-y1,2))/D;
    emile(3)=sqrt(pow(x1-x2,2)+pow(y1-y2,2))/D;

    Matrice_pleine Mel(3,3,0);
    for(int i = 1; i<4; i++)
    {
        for(int j = 1; j<4; j++)
        {
            if(i==j){Mel(i,j) = emile(1)*emile(1)*abs(D)/12;}
            else {Mel(i,j) = emile(1)*emile(1)*abs(D)/24;}
        }
    }

    return Mel;

}
