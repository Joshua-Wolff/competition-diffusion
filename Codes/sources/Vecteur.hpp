#ifndef VECTEUR_H_INCLUDED
#define VECTEUR_H_INCLUDED

#include<iostream>
using namespace std;

// fichier d'entête vecteur.h à compléter

void stop(const char * msg);                     //message d'arrêt
void test_dim(int d1, int d2, const char * org); //test dimension

//classe vecteur de réels double précision
class Vecteur
{
public :
  int dim_;          //dimension du vecteur
  double * val_;     //tableaux de valeurs

public:
  Vecteur(int d=0, double v0=0); //dim et val constante
  Vecteur(const Vecteur & v);    //constructeur par copie
  ~Vecteur();

  //tools
  void init(int d);              //allocation
  void clear();                  //désallocation
  int dim() const {return dim_;} //accès dimension
  Vecteur &operator=(const Vecteur &u);
  Vecteur &operator=(double x);
  double &operator[](int i){if(i>dim_){stop("error dim");};
  return val_[i];};
  double operator[](int i) const{if(i>dim_){stop("error dim");};
  return val_[i];};
  double &operator()(int i){if(i>dim_){stop("error dim");};
  return val_[i-1];};
  double operator()(int i)const{if(i>dim_){stop("error dim");};
  return val_[i-1];};
  Vecteur &operator()(const Vecteur &u,int i,int j);
  Vecteur &operator+=(const Vecteur &u);
  Vecteur &operator+=(double x);
  Vecteur &operator-=(const Vecteur &u);
  Vecteur &operator-=(double x);
  Vecteur operator*=(double x);
  Vecteur operator/=(double x);
  double operator|(const Vecteur &v);


};

Vecteur operator+(const Vecteur &u);

Vecteur operator+(const Vecteur &u,const Vecteur &v);

Vecteur operator+(const Vecteur &u,double x);
Vecteur operator+(double x,const Vecteur &u);
Vecteur operator-(const Vecteur &u);

Vecteur operator-(const Vecteur &u,const Vecteur &v);
Vecteur operator-(const Vecteur &u,double x);
Vecteur operator-(double x,const Vecteur &u);

Vecteur operator*=(const Vecteur & u,double x);

Vecteur operator*(const Vecteur &u,double x);

Vecteur operator*(double x,const Vecteur &u);

Vecteur operator/(const Vecteur &u,double x);
ostream & operator<<(ostream &os ,const Vecteur &u);


#endif // VECTEUR_H_INCLUDED
