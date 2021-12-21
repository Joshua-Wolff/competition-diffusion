#include "Vecteur.hpp"
#include <cmath>
#include <cstdlib>

using namespace std;
// fichier vecteur.cpp à compléter

//utilitaire de messages d'erreur
void stop(const char * msg)
{
  cout<<"ERREUR classe vecteur, "<<msg;
  exit(-1);
}

void test_dim(int d1, int d2, const char * org)
{
  if(d1==d2)  return;
  cout<<org<<" ("<<d1<<","<<d2<<") dimensions incompatibles";
  exit(-1);
}

// constructeurs-destructeurs
Vecteur::Vecteur(int d, double v0) //dim et val constante
{
  init(d);
  for(int i=0;i<dim_;i++) val_[i]=v0;
}

Vecteur::Vecteur(const Vecteur & v) //constructeur par copie
{
  init(v.dim_);
  for(int i=0;i<dim_;i++) val_[i]=v.val_[i];
}

Vecteur::~Vecteur() {clear();}

// outils de construction et de destruction
void Vecteur::init(int d) //initialisation avec allocation dynamique
{
  //if(d<=0) stop("init() : dimension <=0");
  dim_=d;
  val_ = new double[d];
}

void Vecteur::clear()    //désallocation
{
    if(val_!=0) delete [] val_;
    dim_=0;
}
Vecteur & Vecteur::operator=(const Vecteur &u)
{   
    //if(u.dim_!=dim_){stop("error dim");};
    init(u.dim_);
    for(int i=0;i<dim_;i++) val_[i]=u.val_[i];
    return *this;
};

Vecteur & Vecteur::operator=(double x)
{
    for (int i=0;i<dim_;i++)
        val_[i]=x;
    return *this;
};

Vecteur & Vecteur::operator()(const Vecteur &u,int i,int j)
{
    dim_=j-i;
    for (int k=i;k<j;k++)
        val_[i-k]=u.val_[k];
    return *this;
}

Vecteur & Vecteur::operator+=(const Vecteur &u)
{
    if(u.dim_!=dim_){stop("error dim");};
    for (int i=0;i<dim_;i++)
    {
        val_[i]=val_[i]+u.val_[i];

    }
    return *this;
}

Vecteur &Vecteur::operator+=(double x)
{
    for (int i=0;i<dim_;i++)
    {
        val_[i]=val_[i]+x;

    }
    return *this;

}

Vecteur & Vecteur::operator-=(const Vecteur &u)
{
    if(u.dim_!=dim_){stop("error dim");};
    for (int i=0;i<dim_;i++)
    {
        val_[i]=val_[i]-u.val_[i];

    }
    return *this;
}

Vecteur &Vecteur::operator-=(double x)
{
    for (int i=0;i<dim_;i++)
    {
        val_[i]=val_[i]-x;

    }
    return *this;

}

Vecteur operator+(const Vecteur &u)
{
    return u;
}

Vecteur operator+(const Vecteur &u,const Vecteur &v)
{
    Vecteur Q(u);
    Q+=v;
    return Q;
}

Vecteur operator+(const Vecteur &u,double x)
{
    Vecteur Q(u);
    Q+=x;
    return Q;
}
Vecteur operator+(double x,const Vecteur &u)
{
    Vecteur Q(u);
    Q+=x;
    return Q;
}

Vecteur operator-(const Vecteur &u)
{   Vecteur Q(u);
    Q-=u;
    Q-=u;
    return Q;
}

Vecteur operator-(const Vecteur &u,const Vecteur &v)
{
    Vecteur Q(u);
    Q-=v;
    return Q;
}

Vecteur operator-(const Vecteur &u,double x)
{
    Vecteur Q(u);
    Q-=x;
    return Q;
}
Vecteur operator-(double x,const Vecteur &u)
{
    Vecteur Q(u);
    Q-=x;
    return Q;
}


Vecteur Vecteur::operator*=(double x)
{
    for (int i=0;i<dim_;i++)
    {
        val_[i]=val_[i]*x;

    }
    return *this;
}

Vecteur Vecteur::operator/=(double x)
{
    for (int i=0;i<dim_;i++)
    {
        val_[i]=val_[i]/x;

    }
    return *this;
}

Vecteur operator*(const Vecteur &u,double x)
{
    Vecteur Q(u);
    Q*=x;
    return Q;
}

Vecteur operator*(double x,const Vecteur &u)
{
    Vecteur Q(u);
    Q*=x;
    return Q;
}

Vecteur operator/(const Vecteur &u,double x)
{
    Vecteur Q(u);
    Q/=x;
    return Q;
}


double Vecteur::operator|(const Vecteur & v)
{
    test_dim(dim_,v.dim_,"vecteur");
    double x(0);
    for(int i=0;i<dim_;i++)
    {
        x+=val_[i]*(v.val_[i]); 
    }
    return x;
}

ostream & operator<<(ostream &os ,const Vecteur &u)
{

os<<"(";
for(int i=0;i<u.dim_;i++)
os<<u.val_[i]<<",";

os<<")"<<endl;
return os;
}
