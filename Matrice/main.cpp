#include <iostream>
#include "matrice.h"
#include <map>
#include <cstdlib>
#include <time.h>
using namespace std;

int main()
{
    srand(time(NULL));
    matrice a=generateur(10000,10000,5);
    //matrice a("a.txt");
   //a.ecriture("a.txt");
    matrice b=generateur(10000,10000,5);
   //matrice b("b.txt");
   // b.ecriture("b.txt");
    cout<<"++"<<endl;
    matrice c=a.multiplication_matrice(b);
   // c.ecriture("c.txt");







    return 0;
}
