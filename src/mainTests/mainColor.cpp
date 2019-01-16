#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Couleur.h"

using namespace std;

void printCouleur(const Couleur c);

int main()
{
    srand(time(NULL));
    
    Couleur c[50];
    for(unsigned int i=0; i<50; i++) c[i].genCouleurAleatoire();
    for(unsigned int i=0; i<50; i++) printCouleur(c[i]);

    return 0;
}

void printCouleur(const Couleur c)
{
    cout<<(int)c.getR()<<" "<<(int)c.getG()<<" "<<(int)c.getB()<<" "<<(int)c.getA()<<endl;
}