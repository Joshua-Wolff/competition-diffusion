#include "Vecteur.hpp"
#include "Matrice.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>
using namespace std;
void Matrice::compatible(const Matrice & M)
{
    if(taille()!=M.taille())
    {
        cout<<"probleme de dimension";
        exit(1);
    }
}

void Matrice::copie_val(double x)
{
    double *p=val_;
    for(int k=0;k<size_;k++,++p) *p=x;
}

void Matrice::copie_val(const Matrice &M)
{
    double *p=val_;
    double *q=M.val_;
    for(int k=0;k<size_;k++,++p,++q) *p=*q;
}

Matrice & Matrice::operator+=(const Matrice &M)
{
    double *p=val_;
    double *q=M.val_;
    for(int k=0;k<size_;k++,++p,++q) *p+=*q;
    return *this;
}

Matrice & Matrice::operator-=(const Matrice &M)
{
    double *p=val_;
    double *q=M.val_;
    for(int k=0;k<size_;k++,++p,++q) *p-=*q;
    return *this;
}
Matrice & Matrice::operator*=(double x)
{
    double *p=val_;
    for(int k=0;k<size_;k++,++p) (*p)*=x;
    return *this;
}
Matrice & Matrice::operator/=(double x)
{if(x==0){cout<<"division par 0";
exit(1);}
    double *p=val_;
    for(int k=0;k<size_;k++,++p) *p/=x;
    return *this;
}


//MATRICE PLEINE
Matrice_pleine::Matrice_pleine(int i,int j,double x)
{m=i;n=j;size_=m*n;
alloc();
double*p=val_;
for(int i=0;i<m;i++)
{
  for(int j=0;j<n;j++,p++)
  {
      (*p)=x;
  }
}

}

Matrice_pleine::Matrice_pleine(const Matrice_pleine &M)
{
    m=M.m;n=M.n;size_=M.size_;
    alloc();
    copie_val(M);

}

Matrice_pleine & Matrice_pleine::operator=(const Matrice_pleine &M)
{
    if(size_!=M.size_)
    {
        dealloc();
        size_=M.size_;
        alloc();
    }
    m=M.m;n=M.n;size_=M.size_;
    copie_val(M);
    return *this;
}

Matrice_pleine operator+(const Matrice_pleine &M)
{
    return M;
}

Matrice_pleine operator-(const Matrice_pleine &M)
{   Matrice_pleine R(M.nb_ligne(),M.nb_colonne(),0);
    R-=M;
    return R;
}

Matrice_pleine operator+(const Matrice_pleine &M,const Matrice_pleine &N)
{
    Matrice_pleine R(M);
    R+=N;
    return R;
}

Matrice_pleine operator-(const Matrice_pleine &M,const Matrice_pleine &N)
{
    Matrice_pleine R(M);
    R-=N;
    return R;
}



Matrice_pleine operator*(const Matrice_pleine &M,double x)
{
    Matrice_pleine R(M);
    R*=x;
    return R;
}

Matrice_pleine operator*(double x,const Matrice_pleine &N)
{
    Matrice_pleine R(N);
    R*=x;
    return R;
}

Matrice_pleine operator/(const Matrice_pleine &M,double x)
{
    Matrice_pleine R(M);
    R/=x;
    return R;
}

void Matrice_pleine::affiche() const
{
    double *p=val_;
    for(int i=0;i<m;i++)
    {
        cout<<" \n nb ligne "<<i+1<<" : ";
        for(int j=0;j<n;j++,p++) cout<<*p<<" ";
    };
}



Vecteur operator*(const Matrice_pleine &M,const Vecteur &v)
{
    Vecteur w(M.nb_colonne(),0);
    double *p=w.val_;
    for(int i=0; i<M.nb_ligne();i++, p++)
    {
        for(int j=0;j<v.dim();j++)
        {
            (*p)+=v(j+1)*M(i+1,j+1);
        };

    };
    return w;
}

Vecteur Matrice_pleine::colonne(int j)
{
    Vecteur w(nb_ligne(),0);
    double *p=w.val_;
    for (int i=0;i<nb_ligne();i++,p++)
    {
        (*p)=val_[(i-1)*n+j-1];
    };
    return w;
};

Vecteur Matrice_pleine::ligne(int i)
{
    Vecteur w(nb_colonne(),0);
    double *p=w.val_;
    for (int j=1;j<=nb_colonne();j++,p++)
    {
        (*p)=val_[(i-1)*n+j-1];
    };
    return w;
};
Vecteur Matrice_pleine::colonne(int j,int f)const
{
    Vecteur w(nb_ligne()-f+1,0);
    double *p=w.val_;
    for (int i=f;i<=nb_ligne();i++,p++)
    {
        (*p)=val_[(i-1)*n+j-1];
    };
    return w;
};

Matrice_pleine eye(int n)
{
    Matrice_pleine M(n,n,0);
    for (int i=0;i<n;i++)
    {
        M(i+1,i+1)=1;
    }
    return M;
}
int Maxind(const Vecteur v)//on cherche l'indice max d'un vecteur
{
    int i=1;
    int Max=v(1);
    for(int k=2;k<v.dim();k++)
    {
        if (Max<v(k))
            {i=k;
            Max=v(k);}
    }
    return i;
}

Matrice_pleine perm(Matrice_pleine M,int i,int j)
{
    Vecteur V=M.ligne(j);  //on sauvegarde la ligne j
    int n=M.nb_colonne();
    for (int k=1;k<=n;k++)
    {
        M(j,k)=M(i,k);
        M(i,k)=V(k);
    }
    return M;
}

Matrice_pleine ligneaff(Matrice_pleine M,int i,Vecteur V)
{
 if(V.dim()==M.nb_colonne())
 {
     for(int j=1;j<=M.nb_colonne();j++)
     {
         M(i,j)=V(j);
     }
 }
 return M;
}

Matrice_pleine tr(Matrice_pleine& M)
{
    Matrice_pleine transp(M.nb_colonne(),M.nb_ligne(),0);

    for (int i=1;i<=M.nb_ligne();i++)
    {
        for (int j=1;j<=M.nb_colonne();j++)
        {
            transp(i,j)=M(j,i);
        }
    }
    return transp;

}

Matrice_pleine inv( Matrice_pleine& M)//inversion matrice pleine par algo Gauss Jordan
{
    int n=M.nb_colonne();
    Matrice_pleine N=eye(n);
    //recherche du plus grand pivot
    // puis echanger les lignes
    for(int i=1;i<=M.nb_colonne();i++)
    {
        Vecteur V=M.colonne(i,i);// on prend les valeurs en dessous de la ligne pivot
        int ind=Maxind(V)+i-1;//indice du plus grand pivot +i parce que la taille du vecteur est de n-i
        double Pivot=M(ind,i);//recuperer le plus grand pivot
        M=perm(M,i,ind);//permutation de la ligne du pivot
        N=perm(N,i,ind);
        if(M(i,i)!=0)//le pivot est différent de 1
        {
            M=ligneaff(M,i,M.ligne(i)/Pivot);//met le pivot à 1
            N=ligneaff(N,i,N.ligne(i)/Pivot);

            for (int k=1;k<=M.nb_ligne();k++)// parcourt des lignes en dessous et au dessus de la ligne pivot du pivot
            {
                if(k!=i)
                    {
                        Vecteur MM=M.ligne(k);
                        Vecteur NN=N.ligne(k);
                        MM=MM-M.ligne(i)*M(k,i); //on fait les operations sur les lignes
                        NN=NN-N.ligne(i)*M(k,i);
                        M=ligneaff(M,k,MM);//on affecte les operations linéaires
                        N=ligneaff(N,k,NN);

                    }
            }

        }
    }
    return N;
}

Matrice_pleine CtoP(Matrice_creuse & M)// Matrice creuse en matrice pleine
{   Matrice_pleine MM(M.nb_ligne(),M.nb_colonne(),0);
    map<pair<int,int>,double> val=M.mp();
    for (map<pair<int,int>,double>::const_iterator it=val.begin(); it!=val.end(); ++it)
    {   int i=it->first.first;
        int j=it->first.second;
        double x=it->second;
        MM(i,j)=x;

    }
    return MM;
}

//matrice cruse
void Matrice_creuse::add(pair<int,int> p,double x)
 {   if (x==-val__[p]){val__.erase(p);exit(0);}
     if(val__.find(p)!=val__.end()){val__[p]=val__[p]+x;}//si l'élément existe déja
     else val__.insert(pair<pair<int,int>,double>(p,x));
     size_+=1;
 }
void Matrice_creuse::add(int i,int j,double x)
{   pair<int,int> p(i,j);
    if (x==-val__[p]){val__.erase(p);exit(0);};
    if(val__.find(p)!=val__.end()){val__[p]=val__[p]+x;}//
    else val__.insert(pair<pair<int,int>,double>(p,x));
    size_+=1;
}
void Matrice_creuse::affiche() const
{   cout<<"Matrice creuse = "<<endl;
    for (map<pair<int,int>,double>::const_iterator it=val__.begin(); it!=val__.end(); ++it)
    {
    cout <<"("<< it->first.first<<","<<it->first.second<<")" << " => " << it->second << '\n';
    }
    };

Matrice_creuse Matrice_creuse::tr()
{
    map<pair<int,int>,double> p;
    for (map<pair<int,int>,double>::const_iterator it=val__.begin(); it!=val__.end(); ++it)
    {   pair<int,int> g(it->first.second,it->first.first);
        p.insert(pair<pair<int,int>,double>(g,it->second));
    };
    val__=p;
    return *this;
    };


Matrice_creuse& Matrice_creuse::operator+=(const Matrice_creuse& M)
{   Matrice_creuse N(M);
    for (map<pair<int,int>,double>::const_iterator it=val__.begin(); it!=val__.end(); ++it)
    {
        N.add(it->first,it->second);

    }
    (*this)=N;
    return *this;
}

Matrice_creuse& Matrice_creuse::operator-=(const Matrice_creuse& M)
{   Matrice_creuse N(M);
    for (map<pair<int,int>,double>::const_iterator it=val__.begin(); it!=val__.end(); ++it)
    {
        N.add(it->first,-it->second);

    }
    *this=N;
    return *this;
};
Matrice_creuse operator+(const Matrice_creuse &M,const Matrice_creuse &N)
{
    Matrice_creuse R(M);
    R+=N;
    return R;
};

Matrice_creuse operator-(const Matrice_creuse &M,const Matrice_creuse &N)
{
    Matrice_creuse R(M);
    R-=N;
    return R;
};

Matrice_creuse& Matrice_creuse::operator*=(double x)
{
    for (map<pair<int,int>,double>::const_iterator it=val__.begin(); it!=val__.end(); ++it)
    {
        pair<int,int> key=it->first;
        val__[key]*=x;

    }
    return *this;}

Matrice_creuse operator*(const Matrice_creuse &M,double x)
{
    Matrice_creuse R(M);
    R*=x;
    return R;
}

Matrice_creuse operator*(double x,const Matrice_creuse &M)
{
    Matrice_creuse R(M);
    R*=x;
    return R;
}

Matrice_creuse& Matrice_creuse::operator/=(double x)
{   if(x==0){exit(EXIT_FAILURE);};
    for (map<pair<int,int>,double>::const_iterator it=val__.begin(); it!=val__.end(); ++it)
    {
        pair<int,int> key=it->first;
        val__[key]/=x;

    }
    return *this;}

Matrice_creuse operator/(const Matrice_creuse &M,double x)
{
    Matrice_creuse R(M);
    R/=x;
    return R;
}

Vecteur operator*(Matrice_creuse &M,const Vecteur &v)
{
    Vecteur w(v.dim(),0);
    map<pair<int,int>,double> m=M.mp();
    for (map<pair<int,int>,double>::const_iterator it=m.begin(); it!=m.end(); ++it)
    {
        pair<int,int> key=it->first;
        w(key.first)+=v(key.second)*it->second; //w(i)=v(j)*M(i,j) mais on ne calcule que sur les éléments qui existe dans la matrice creuse
    }
    return w;
}
;

Vecteur operator*( const Vecteur &v,Matrice_creuse &M)
{
    Vecteur w(v.dim(),0);
    map<pair<int,int>,double> m=M.mp();
    for (map<pair<int,int>,double>::const_iterator it=m.begin(); it!=m.end(); ++it)
    {
        pair<int,int> key=it->first;
        w(key.first)+=v(key.second)*it->second; //w(i)=v(j)*M(i,j) mais on ne calcule que sur les éléments qui existe dans la matrice creuse
    }
    return w;
}
;


Matrice_creuse PtoC(const Matrice_pleine & M)
{   Matrice_creuse MM(M.nb_ligne(),M.nb_colonne());
    for(int i=1;i<=M.nb_ligne();i++)//parcourt ligne
    {
     for (int j=1;j<=M.nb_colonne();j++)//parcourt ligne
     {
         if(M(i,j)!=0)
         {
             MM.add(i,j,M(i,j));
         }
     }

    }
    return MM;
}


//GradCon(A,b) donne le vecteur x de Ax=b;
Vecteur GradCon( Matrice_creuse &M, Vecteur &b)// methode de gradient conjugu� donne le vecteur x de Ax=b
{    Vecteur x(M.nb_colonne(),0);
     Vecteur r=b-M*x;//initialisation
     Vecteur p=r;
     int k=0;

     while((r|r)>pow(10,-6) && k<100)// on veut que la norme soit petite
     {   double Mp=(p|(M*p));
         double a=(r|r)/Mp;//a = alpha
         x=x+a*p;
         Vecteur rk=r;//on retient en m�moire rk car on en a besoin pour pk+1
         r=r-a*(M*p);
         double B=(r|r)/(rk|rk);//B=beta
         p=r+B*p;
         k+=1;
     }
     return x;
};

//GradCon(A,b) donne le vecteur x de Ax=b;
Vecteur GradCon( Matrice_pleine &M, Vecteur &b)// methode de gradient conjugu� donne le vecteur x de Ax=b
{    Vecteur x(M.nb_colonne(),0);
     Vecteur r=b-M*x;//initialisation
     Vecteur p=r;
     int k=0;

     while((r|r)>pow(10,-9) && k<100)// on veut que la norme soit petite
     {   double Mp=(p|(M*p));
         double a=(r|r)/Mp;//a = alpha
         x=x+a*p;
         Vecteur rk=r;//on retient en m�moire rk car on en a besoin pour pk+1
         r=r-a*(M*p);
         double B=(r|r)/(rk|rk);//B=beta
         p=r+B*p;
         k+=1;
     }
     return x;
};