#include <iostream>
#include "matrice.h"
#include <map>
#include <cstdlib>
#include <time.h>
using namespace std;

matrice generateur(int h,int l,int taille)
{
    matrice tmp(h,l);
    int c;
    int d;
//    for(int i=0;i<h;i++)
//    {
//        for(int j=0;j<l;j++)
//        {
//            c=rand()%(h-0)+0;
//            if(c>h)tmp.ajout_modif(Coo(i,j),rand()%(taille-1) +1);
//        }
//    }

    for(int i=0;i<5000000;i++)
    {
        c=rand()%(h-0)+0;
        d=rand()%(h-0)+0;
        tmp.ajout_modif(Coo(c,d),rand()%(taille-1) +1);
    }

    return tmp;
}
