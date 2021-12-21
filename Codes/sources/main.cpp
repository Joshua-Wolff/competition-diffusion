#include <iostream>
#include "Probleme.hpp"
#include "Vecteur.hpp"
#include "Matrice.hpp"
#include "Maillage.hpp"
#include<string>
using namespace std;

int main()
{

    //!\\ ne pas mettre plus qu'un seul "oui" //!//

    string validation_poisson = "non"; //pas de couplage, stationnaire (résolution de l'équation de poisson)
    string validation_sans_diffusion = "non"; //couplage, pas de diffusion, temporel
    string validation_diffusion_seule = "non"; // pas de couplage, diffusion 
    string resolution = "oui"; // couplage, diffusion 






    Maillage M("maillageSIM202.txt"); // constructeur maillage
    Probleme pb; // constructeur problème

    // récupération des éléments du maillage 

    int Nbpt = M.Nbpt; int Nbarete = M.Nbarete; int Nbtri = M.Nbtri;
    Matrice_pleine Coorneu(M.Coorneu);
    Vecteur Refneu(M.Refneu);
    Matrice_pleine Numarete(M.Numarete);
    Vecteur Refarete(M.Refarete);
    Matrice_pleine Numtri(M.Numtri);
    Vecteur Reftri(M.Reftri);
    // fin de récupération 

    Vecteur Points_du_bord(M.pt_bord()); // Vecteur qui contient la référence des points qui sont au bord du domaine

    double a = pb.a; double b = pb.b; double c = pb.c; double d = pb.d; // coeffs pour la construction du second membre
    double c_u = pb.c_u; double c_v = pb.c_v; // coeffs de diffusion
    double delta_T = pb.delta_T; double alpha = pb.alpha; double h = pb.h; // pas de discrétisation




    //Validation pb de poisson stationnaire
    if (validation_poisson == "oui")
    {    
        Vecteur U(Nbpt, 0);//on travaille sans couplage

        Vecteur F = pb.f(Nbpt, Coorneu);//second membre
        Matrice_pleine KK(pb.assemblage_matrice(Numtri, Coorneu, Nbpt, Nbtri, 0));
        Matrice_pleine AA = pb.elimine_M(KK, Points_du_bord, Nbpt);//pseudo élimination de KK
        Vecteur L= pb.elimine_V(F, Points_du_bord, Nbpt);
        //Matrice_pleine AA_tilde = inv(AA);
        //U = AA_tilde * L;
        U=GradCon(AA,L);

        string const nomFichier("affichage.txt");
        ofstream monFlux(nomFichier.c_str());
        

        
        // Affichage
        
        if(monFlux)    
        {
            for (int i=1;i<Nbpt;i++)
            {
                monFlux << Coorneu(i,1)<< " ";
            }
            monFlux << Coorneu(Nbpt,1) << endl;

            for (int i=1;i<Nbpt;i++)
            {
                monFlux << Coorneu(i,2)<< " ";
            }
            monFlux << Coorneu(Nbpt,2) << endl;

            for (int i=1;i<Nbpt;i++)
            {
                monFlux << U(i)<< " ";
            }
            monFlux << U(Nbpt) << endl;
        }
        
    }






    //validation du pb sans diffusion
    if (validation_sans_diffusion == "oui")
    {
        double u = 10;//populations initiales
        double v = 10;

        int T_max=500;

        string const nomFichier("affichage.txt");
        ofstream monFlux(nomFichier.c_str());
        
        if(monFlux)    
        {
            monFlux << T_max << " ";
            monFlux << delta_T<< " ";
            monFlux << u << " " ;
            monFlux << v << " ";
        }

        for (int k = 0; k < T_max; k++)
        {
            // calcul de Ukp1 et Vkp1
            u = delta_T * u * (alpha + c - d * v); // proies
            
            v = delta_T * v * (alpha - a + b * u); // prédateurs

            if(monFlux)    
            {
                if(k==T_max-1)
                {
                    monFlux << u << " " ;
                    monFlux << v;
                }
                else
                {
                    monFlux << u << " " ;
                    monFlux << v << " ";
                }
            }
            
        };
        

    };







    //validation du pb de diffusion seule
    if (validation_diffusion_seule == "oui")
    {
        Vecteur U(Nbpt, 1); //on initialise à 1        

        Vecteur L_u(Nbpt, 0); //second membre
        Vecteur F = pb.f(Nbpt, Coorneu); //fonction second membre
        

        Matrice_pleine MM(pb.assemblage_matrice(Numtri, Coorneu, Nbpt, Nbtri, 1));
        Matrice_pleine KK(pb.assemblage_matrice(Numtri, Coorneu, Nbpt, Nbtri, 0));
        //Matrice_pleine SS(pb.assemblage_matrice(Numtri, Coorneu, Nbpt, Nbtri, 2));        

        Matrice_pleine AA = alpha * MM + c_u * KK;
        Matrice_pleine A = pb.elimine_M(AA, Points_du_bord, Nbpt);
        //Matrice_pleine AA_tilde = inv(AA);

        string const nomFichier("affichage.txt");
        ofstream monFlux(nomFichier.c_str());

        if(monFlux)
        {
            for (int i=1;i<Nbpt;i++)
            {
                monFlux << Coorneu(i,1)<< " ";
            }
            monFlux << Coorneu(Nbpt,1) << endl;
            for (int i=1;i<Nbpt;i++)
            {
                monFlux << Coorneu(i,2)<< " ";
            }
            monFlux << Coorneu(Nbpt,2) << endl;
            for (int i=1;i<Nbpt;i++)
            {
                monFlux << U(i)<< " ";
            }
            monFlux << U(Nbpt) << endl;
        }

        int T_max = 3;

        for (int k = 0; k < T_max; k++)
        {
            // calcul du second membre
            L_u = pb.elimine_V(F + alpha * MM * U, Points_du_bord, Nbpt);

            // calcul de Ukp1 
            U = GradCon(A,L_u);

            if(monFlux)    
            {
                for (int i=1;i<Nbpt;i++)
                {
                    monFlux << U(i)<< " ";
                }
                monFlux << U(Nbpt) << endl;
            }
           
        }
    }











    //résolution du problème
    if (resolution=="oui")
    {
        //Vecteur U(Nbpt, 0.5);
        Vecteur U=pb.g(Nbpt, Coorneu);
        Vecteur V(Nbpt, 0.2); 
        
        Vecteur L_u(Nbpt, 0); //seconds membres
        Vecteur L_v(Nbpt, 0);

        Matrice_pleine MM(pb.assemblage_matrice(Numtri, Coorneu, Nbpt, Nbtri, 1));
        Matrice_pleine KK(pb.assemblage_matrice(Numtri, Coorneu, Nbpt, Nbtri, 0));
        //Matrice_pleine SS(pb.assemblage_matrice(Numarete, Coorneu, Nbpt, Nbarete, 2));

        Matrice_pleine AA_u = alpha * MM + c_u * KK;
        Matrice_pleine AA_v = alpha * MM + c_v * KK;

        //Matrice_pleine AA_tilde_u = inv(AA_u);
        //Matrice_pleine AA_tilde_v = inv(AA_v);

        string const nomFichier("affichage.txt");
        ofstream monFlux(nomFichier.c_str());

        if(monFlux)    
            {
                for (int i=1;i<Nbpt;i++)
                {
                    monFlux << Coorneu(i,1)<< " ";
                }
                monFlux << Coorneu(Nbpt,1) << endl;
                for (int i=1;i<Nbpt;i++)
                {
                    monFlux << Coorneu(i,2)<< " ";
                }
                monFlux << Coorneu(Nbpt,2) << endl;
                for (int i=1;i<Nbpt;i++)
                {
                    monFlux << U(i)<< " ";
                }
                monFlux << U(Nbpt) << endl;
                for (int i=1;i<Nbpt;i++)
                {
                    monFlux << V(i)<< " ";
                }
                monFlux << V(Nbpt) << endl;
            }

        int T_max = 5;

        for (int k = 0; k < T_max; k++)
        {
            // calcul des seconds membres
            Vecteur S_u(pb.assemblage_second_membre(V, U, Nbpt, 0));
            Vecteur S_v(pb.assemblage_second_membre(V, U, Nbpt, 1));

            L_u = S_u + alpha * MM * U;
            L_v = S_v + alpha * MM * V;

            // calcul de Ukp1 et Vkp1
            U = GradCon(AA_u,L_u);
            V = GradCon(AA_v,L_v);


            if(monFlux)    
            {
                for (int i=1;i<Nbpt;i++)
                {
                    monFlux << U(i)<< " ";
                }
                monFlux << U(Nbpt) << endl;
                for (int i=1;i<Nbpt;i++)
                {
                    monFlux << V(i)<< " ";
                }
                monFlux << V(Nbpt) << endl;
            }



        }
    }

    return 0;
};
