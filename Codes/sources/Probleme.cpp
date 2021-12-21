#include <iostream>
#include "Probleme.hpp"
#include "Maillage.hpp"
#include "Vecteur.hpp"
#include "Matrice.hpp"

Probleme::Probleme()
{
    //a=4; b=2 ; c=2 ; d=1 ; c_u=1 ; c_v=1 ; // bon coeff pour la vérification en temporel uniquement (euler)
    a=1; b=1/3 ; c=1/4 ; d=1 ; c_u=1 ; c_v=1 ;  // bon coeff pour le problème final 

    delta_T=1 ; 
    alpha=1/delta_T ;
}

Vecteur Probleme::assemblage_second_membre(Vecteur& V, Vecteur& U, int Nbpt, int test)
{
	Vecteur S(Nbpt, 0);
	if (test == 0) //on construit S_u
	{
		for (int i = 1; i < Nbpt+1; i++)
		{
			S(i) = U(i) * (1 - U(i) - c*V(i));
		};
	};

	if (test == 1) //on construit S_v
	{
		for (int i = 1; i < Nbpt+1; i++)
		{
			S(i) = V(i) * (a- V(i) - b*U(i));
		};

	};

	return S;
};