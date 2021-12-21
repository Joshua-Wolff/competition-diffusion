#include<vector>
#include<list>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<iterator>

#include "Maillage.hpp"
#include "Vecteur.hpp"
#include "Matrice.hpp"

using namespace std;


// fonction pour découper une chaîne de caractères au niveau des espaces

vector<float> split_str (string chaine)
{
    string buff;
    vector<float> sortie;
    int inc=0;
    int n=chaine.length();


    while (inc!=n) 
    {
         if (chaine[inc]!=' ')
            {
                buff+=chaine[inc];
            }
         else
         {
            sortie.push_back(stof(buff));
            buff=' ';
         }   
         inc+=1;
    }
    sortie.push_back(stof(buff));

   
    return sortie;
}



// constructeur du maillage à partir d'un .gmsh



Maillage::Maillage(string fichier)
{
    
    string nom_fichier = "./";
    nom_fichier+=fichier; // On a maintenant le chemin d'accès au fichier texte

    ifstream file(nom_fichier);
    int Nbelem;

   if(file)
   {
        string ligne; //Une variable pour stocker les lignes lues
        int inc=1;
        int i=1;

        Nbtri=0; // On va les compter en parcourant une première fois le fichier
        Nbarete=0;
        

        while(getline(file, ligne)) //Tant qu'on n'est pas à la fin, on lit ligne par ligne
        {

            if (inc==5) // les 4 premières lignes ne contiennent pas d'infos utiles
            {
                Nbpt=stoi(ligne); //Nombre de sommets contenus dans le fichier
                Coorneu=Matrice_pleine(Nbpt,2,0); 
                Refneu=Vecteur(Nbpt,0);
            }
            
            if ((inc>5)&&(inc<=5+Nbpt)) // on récupère les coordonnées des sommets
            {
                vector<float> coord_sommet=split_str(ligne);
                Refneu(i)=i; // référence des sommets
                Coorneu(i,1)=coord_sommet[1];
                Coorneu(i,2)=coord_sommet[2];
                i=i+1;
            }
            
            if (inc==8+Nbpt)
            {
                Nbelem=stoi(ligne);
            }

            if ((inc>8+Nbpt)&&(inc<=8+Nbpt+Nbelem)) // On compte le nombre d'aretes et de triangles
            {
                vector<float> elements=split_str(ligne);

                if (elements[1]==1)
                {
                    Nbarete+=1;
                }

                if (elements[1]==2)
                {
                    Nbtri+=1;
                }
            }

            inc+=1;
        } 
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }

    
    // Deuxième lecture du fichier pour récupérer l'information sur les triangles et les aretes
    string nom_fichier2 = "./";
    nom_fichier2+=fichier; // On a maintenant le chemin d'accès au fichier texte

    ifstream file2(nom_fichier2);

    if(file2)
    {
        string ligne; //Une variable pour stocker les lignes lues
        int inc=1;
        int i=1;
        int j=1;

        Refarete=Vecteur(Nbarete,0);
        Numarete=Matrice_pleine(Nbarete,2,0);
        Reftri=Vecteur(Nbtri,0);
        Numtri=Matrice_pleine(Nbtri,3,0);
        

        while(getline(file2, ligne)) //Tant qu'on n'est pas à la fin, on lit ligne par ligne
        {

            if ((inc>8+Nbpt)&&(inc<=8+Nbpt+Nbelem))
            {
                vector<float> elements=split_str(ligne);

                if (elements[1]==1)
                {
                    int saut=elements[2];
                    Refarete(j)=j;
                    Numarete(j,1)=elements[3+saut];
                    Numarete(j,2)=elements[4+saut];
                    j+=1;
                }

                if (elements[1]==2)
                {
                    int saut=elements[2];
                    Reftri(i)=i;
                    Numtri(i,1)=elements[3+saut];
                    Numtri(i,2)=elements[4+saut];
                    Numtri(i,3)=elements[5+saut];
                    i+=1;
                }
            }

            inc+=1;

        } 
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }

}



// Fonction pour connaître les références des points du maillage se trouvant au bord du domaine



Vecteur Maillage::pt_bord()
{
    int size_arete=Nbarete;
    Vecteur compteur; compteur=Vecteur(size_arete,0);
    int size_tri=Nbtri;
    vector<int> liste_refarete_bord;

    Vecteur arete;
    Vecteur triangle; 

    for (int i=1;i<=size_arete;i++)
    {
        for (int j=1;j<=size_tri;j++)
        {
            arete=Vecteur(Numarete.ligne(i));
            triangle=Vecteur(Numtri.ligne(j));
            
            if ( ((arete(1)==triangle(1)) || (arete(1)==triangle(2)) || (arete(1)==triangle(3))) && ((arete(2)==triangle(1)) || (arete(2)==triangle(2)) || (arete(2)==triangle(3))) )
            {
                compteur(i)=compteur(i)+1;
            }
        }
    }


    for (int i=1;i<=size_arete;i++)
    {
        if (compteur(i)==1)
        {
            liste_refarete_bord.push_back(Refarete(i));
        }
    }

    

    vector<int> liste_pt_bord;
    for (int i=0;i<=liste_refarete_bord.size();i++)
    {
        liste_pt_bord.push_back(Numarete(liste_refarete_bord[i],1));
        liste_pt_bord.push_back(Numarete(liste_refarete_bord[i],2));
    }

    sort(liste_pt_bord.begin(), liste_pt_bord.end());
    liste_pt_bord.erase(unique(liste_pt_bord.begin(), liste_pt_bord.end()), liste_pt_bord.end());

    

    Vecteur res; res=Vecteur(liste_pt_bord.size(),0);


    for (int i = 0; i != liste_pt_bord.size(); i++)
    {
        res[i]=liste_pt_bord[i];
    }


    return res;
}

