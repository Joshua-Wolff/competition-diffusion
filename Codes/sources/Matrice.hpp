#ifndef MATRICE_H_INCLUDED
#define MATRICE_H_INCLUDED
#include<iostream>
#include"Vecteur.hpp"
//#include"Indice.h"
#include<map>
#include<utility>

using namespace std;

class Matrice
{
protected:
    int m,n;
    int size_;
    double * val_;
    void alloc()
    {
        val_=new double[size_];
    };
    void dealloc()
    {
        delete [] val_; val_=NULL;
    };
    void copie_val(const Matrice &M);
    void copie_val(double x);
public:
    int nb_ligne()const {return m;};
    int nb_colonne()const{return n;};
    int taille()const{return size_;};




    void compatible(const Matrice & M);
    Matrice & operator+=(const Matrice &M);
    Matrice & operator-=(const Matrice &M);
    Matrice & operator*=(double x);
    Matrice & operator/=(double x);

    friend ostream & operator<<(ostream &os, const Matrice &M);
};

class Matrice_pleine : public Matrice
{   public:
    Matrice_pleine(){m=0;n=0;size_=0;val_=NULL;}; // constructeur par défaut
    Matrice_pleine(int m,int n,double x);
    Matrice_pleine(const Matrice_pleine &M);
    ~Matrice_pleine(){dealloc();}
    Matrice_pleine& operator=(const Matrice_pleine &M);
    Vecteur colonne(int j);
    Vecteur ligne(int i);
    Vecteur colonne(int j,int f) const;// vecteur colonne commencant par la n ème indice
    double & operator()(int i,int j)const{return val_[(i-1)*n+j-1];}
    void affiche() const;
    Matrice_pleine tr()const;

    //tr transposé fait
    //inv inverse


};
Matrice_pleine tr(Matrice_pleine &M);
Matrice_pleine ligneaff(Matrice_pleine M,int i,Vecteur V);// i la ligne a affecter le vecteur V
Matrice_pleine inv( Matrice_pleine &M);
Matrice_pleine perm(Matrice_pleine M,int i,int j);//permuter les lignes pour pivot de gauss
int Maxind(const Vecteur v);//trouver l'indice maximum pour le pivot de gauss

Matrice_pleine operator+(const Matrice_pleine &M);
Matrice_pleine operator-(const Matrice_pleine &M);
Matrice_pleine operator+(const Matrice_pleine &M,const Matrice_pleine &N);
Matrice_pleine operator-(const Matrice_pleine &M,const Matrice_pleine &N);
Matrice_pleine operator*(const Matrice_pleine &M,double x);
Matrice_pleine operator*(double x,const Matrice_pleine &M);
Matrice_pleine operator/(const Matrice_pleine &M,double x);
Vecteur operator*(const Matrice_pleine &M,const Vecteur &v);
Vecteur operator*(const Vecteur &v,const Matrice_pleine &M);
Matrice_pleine eye(int n);





class Matrice_creuse : public Matrice
{
protected:
    map<pair<int,int>,double> val__;
public:
    Matrice_creuse();//construceur par défaut
    Matrice_creuse(int nn,int pp){n=nn;m=pp;size_=0;};//constructeur
    Matrice_creuse(const Matrice_creuse& M){n=M.n;m=M.m;val__=M.val__;}; //constructeur par copie
    void add(pair<int,int> p,double x);
    void add(int i,int j, double x);
    double operator()(int i,int j)//lecture
        {pair<int,int> p(i,j);
        if (val__.find(p)==val__.end()){return 0;}
        else{return val__[p];}
        };//accesseur
    Matrice_pleine& operator=(const Matrice_pleine &M);
    void affiche() const;
    Matrice_creuse tr();

    Matrice_creuse& operator+=(const Matrice_creuse &M);
    Matrice_creuse& operator-=(const Matrice_creuse &M);
    //inverse de matrice !( peut etre faire une condensation de masse)
    //addiction de matrice_creuse! fait
    Matrice_creuse& operator*=(double x);
    Matrice_creuse& operator/=(double x);
    map<pair<int,int>,double>  mp(){return val__;}
};

Matrice_creuse operator+(const Matrice_creuse &M,const Matrice_creuse &N);
Matrice_creuse operator-(const Matrice_creuse &M,const Matrice_creuse &N);
Matrice_creuse operator*(const Matrice_creuse& M,double x);
Matrice_creuse operator*(double x,const Matrice_creuse& M);
Matrice_creuse operator/(const Matrice_creuse& M,double x);
Matrice_creuse PtoC(const Matrice_pleine & M);//matrice_pleine en creuse



Vecteur operator*( Matrice_creuse &M,const Vecteur &v);
Vecteur operator*(const Vecteur &v,const Matrice_creuse &M);

Matrice_pleine CtoP( Matrice_creuse & M);// Matrice creuse en matrice pleine

//GradCon(A,b) donne le vecteur x de Ax=b;
Vecteur GradCon( Matrice_creuse &M, Vecteur &b);// methode iterative pour resoudre Ax=b avec A symetrique d�finie positive avec matrice creuse;
Vecteur GradCon( Matrice_pleine &M, Vecteur &b);//methode gradient conjugu� avec matrice pleine




#endif // MATRICE_H_INCLUDED
