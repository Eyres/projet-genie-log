#ifndef MATRICE_H_INCLUDED
#define MATRICE_H_INCLUDED
#include <iostream>
#include <map>
using namespace std;
class Coo
{
private:
    int _l;
    int _c;

public:
    Coo(int l,int c);
    void aff(ostream &flux) const;
    bool operator<(Coo const& a) const;
    int ret_l() const;
    int ret_c() const;
};

class matrice
{
private:
    int h;
    int l;
    map<Coo,int> mc;
public:
    matrice(int hh,int ll);
    matrice(string s);
    void ecriture(string s);
    void ecritureU(string s);
    void ajout_modif(Coo e,int val);
    int ret_val(Coo e);
    matrice addition(matrice& a);
    matrice soustraction(matrice& a);
    matrice transposer();
    matrice multiplication_const(int nombre);
    matrice multiplication_matrice(matrice& a);
};


ostream& operator<<(ostream & flux, Coo & a);
matrice generateur(int h,int l,int taille);

#endif // MATRICE_H_INCLUDED
