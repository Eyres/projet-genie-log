#include <iostream>
#include <fstream>
#include "matrice.h"
using namespace std;

Coo::Coo(int l,int c)
{
    _l=l;
    _c=c;
}

void Coo::aff(ostream &flux) const
{
    flux<<"(l:"<<_l<<", c:"<<_c<<")";
}

bool Coo::operator<(Coo const &a) const
{
    if(_l<a._l) return true;
    else if(_l>a._l) return false;
    else return(_c<a._c);
}

ostream& operator<<(ostream & flux, Coo & a)
{
    a.aff(flux);
    return flux;
}

int Coo::ret_l() const
{
    return _l;
}
int Coo::ret_c() const
{
    return _c;
}
matrice::matrice(int hh,int ll)     //Constructeur basique prenant les dimensions de la matrice
{
    h=hh;
    l=ll;
}
matrice::matrice(string s)          //Constructeur à partir d'un fichier
{
    ifstream fichier(s.c_str());    //ouverture du fichier

    if(fichier)                     //Si le fichier existe
    {
        fichier>>h>>l;              //Lecture des dimmensions
        int x;
        int y;

        while(!fichier.eof())       //Parcour tout le fichier
        {
            fichier>>x>>y;          //Prend les coordonees
            fichier>>mc[Coo(x,y)];  //Stock la valeur
        }
    }
    else cout<<"Erreur, fichier introuvable"<<endl;

}

void matrice::ecriture(string s)                //Ecriture optimiser
{
    ofstream fichier(s.c_str());                //Ouvre le fichier et le crée si il n'existe pas
    fichier<<h<<endl<<l<<endl;                  //Ecris les dimensions de la matrice
    map<Coo,int>::iterator it;                  //Création d'un itérateur
    for(it = mc.begin();it != mc.end(); ++it)   //Pour toute les valeurs contenu dans le map
    {
        fichier<<it->first.ret_l()<<"\t"<<it->first.ret_c()<<"\t"<<it->second<<endl;    //Sépare les coordonées(x,y) et les ecris suivi de la valeur associé
    }

}

void matrice::ecritureU(string s)               //Ecriture visuelle
{
    ofstream fichier(s.c_str());
    fichier<<h<<endl<<l<<endl;
    for(int i=0;i<h;i++)                        //Parcour de toute la matrice
    {
        for(int j=0;j<l;j++)
        {
            if(mc.find(Coo(i,j))==mc.end()) fichier<<"0\t"; //Si la clé n'existe pas on ecrit 0
            else fichier<<mc[Coo(i,j)]<<"\t";               //Sinon on ecrit la valeur associé

        }
        fichier<<endl;                                      //Changement de ligne
    }
}

void matrice::ajout_modif(Coo e,int val)
{
    if(val==0) mc.erase(e);     //Si val==0 alors on supprime la clé

    else mc[e]=val;             //Sinon on y affecte la  valeur
}

int matrice::ret_val(Coo e)
{
    if(mc.find(e)==mc.end()) return 0;  //Si la clé n'existe pas on retourne 0
    return mc[e];                       //Sinon on retourne la valeur
}

matrice matrice::addition(matrice& a)
{
    matrice tmp(h,l);
    if(h!=a.h||l!=a.l) return tmp;
    map<Coo,int>::iterator it;                  //Création d'un itérateur
    map<Coo,int>::iterator it1;
    it=mc.begin();
    it1=a.mc.begin();
    while(it!=mc.end()&&it1!=a.mc.end())
    {
        if(it!=mc.end())
        {
            tmp.mc[it->first]+=it->second;
            it++;
        }
        if(it1!=a.mc.end())
        {
            tmp.mc[it1->first]+=it1->second;
            it1++;
        }

    }
    return tmp;
}

matrice matrice::soustraction(matrice& a)
{
    matrice tmp(h,l);
    if(h!=a.h||l!=a.l) return tmp;
    map<Coo,int>::iterator it;                  //Création d'un itérateur
    map<Coo,int>::iterator it1;
    it=mc.begin();
    it1=a.mc.begin();
    while(it!=mc.end()&&it1!=a.mc.end())
    {
        if(it!=mc.end())
        {
            tmp.mc[it->first]+=it->second;
            it++;
        }
        if(it1!=a.mc.end())
        {
            tmp.mc[it1->first]-=it1->second;
            it1++;
        }

    }
    return tmp;
}

matrice matrice::transposer()
{
    matrice tmp(l,h);
    map<Coo,int>::iterator it;                         //Parcour de toute la matrice
    for(it=mc.begin();it!=mc.end();it++)
    {
        tmp.mc[Coo(it->first.ret_c(),it->first.ret_l())]=it->second;
    }
    cout<<"passer"<<endl;
    return tmp;
}

matrice matrice::multiplication_const(int nombre)
{
    matrice tmp(h,l);
    map<Coo,int>::iterator it;
    for(it=mc.begin();it!=mc.end();it++)
    {
        tmp.mc[it->first]=it->second*nombre;
    }
    return tmp;
}

matrice matrice::multiplication_matrice(matrice& a)
{
    matrice tmp(h,a.l);
    if(h!=a.l) return tmp;
    matrice aT=a.transposer();
    map<Coo,int>::iterator it;                  //Création d'un itérateur
    map<Coo,int>::iterator it1;
    map<Coo,int>::iterator itmp;
    it=itmp=mc.begin();
    it1=aT.mc.begin();
    int i=it->first.ret_l();
    int j=it1->first.ret_l();
    int c,l,c1,l1;
    while(it!=mc.end()&&it1!=aT.mc.end())   //Pour toute les valeurs contenu dans le map
    {
        c=it->first.ret_c();
        l=it->first.ret_l();
        c1=it1->first.ret_c();
        l1=it1->first.ret_l();
        if(l1>j)
        {
            it=itmp;
            j++;
        }
        else if(l>i)
        {
            it=itmp;
            it1++;
        }
        else if(c==c1)
        {
            tmp.mc[Coo(l,l1)]+=it->second*it1->second;
            it1++;
            it++;
        }
        else if(c<c1) it++;
        else it1++;
        if(it1==aT.mc.end())
        {


            i++;
            while(l<i)
            {
                if(it==mc.end())break;
                it++;
            }
            itmp=it;
            if(it!=mc.end())
            {
                it1=aT.mc.begin();
                j=it1->first.ret_l();
            }

        }
    }


    return tmp;
}
