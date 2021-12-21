#ifndef MAILLAGE_SIM202
#define MAILLAGE_SIM202

#include<vector>
#include<list>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<iterator>


#include "Vecteur.hpp"
#include "Matrice.hpp"

using namespace std;




class Maillage
{
    public:

        int Nbpt,Nbarete,Nbtri; // Nombre de sommets
        Matrice_pleine Coorneu; // matrice de taille Nbpt x 2 (du type [[x1,y1],...]) 
        Vecteur Refneu; // vecteur de taille 1 x Nbpt
        Matrice_pleine Numarete; // matrice de taille Nbarete x 2 (avec les refneu adéquats)
        Vecteur Refarete; // vecteur de taille 1 x Nbarete
        Matrice_pleine Numtri; // matrice de taille Nbtri x 3 (avec les refneu adéquats)
        Vecteur Reftri; // vecteur de taille 1 x Nbtri
        

    public:
        
        Maillage(string fichier); //constructeur par lecture d'un fichier gmsh
        Vecteur pt_bord();

        

};



vector<float> split_str (string chaine); // découpage d'une chaîne de caractères


#endif 