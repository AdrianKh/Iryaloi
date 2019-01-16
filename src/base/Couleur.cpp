#include "Couleur.h"
#include <cstdlib>

Couleur::Couleur(unsigned char r1,unsigned char g1,unsigned char b1, unsigned char a1)
{
    this->r = r1;
    this->g = g1;
    this->b = b1;
    this->a = a1;
}
Couleur::Couleur(const Couleur & c )
{
    this->r = c.r;
    this->g = c.g;
    this->b = c.b;
    this->a = c.a;
}
unsigned char Couleur::getR()const {return r;} 
unsigned char Couleur::getG()const {return g; }
unsigned char Couleur::getB()const{return b; }
unsigned char Couleur::getA()const{return a; }
    
void Couleur::setR(unsigned char r1){this->r =r1;}
void Couleur::setG(unsigned char g1){this->g =g1; }
void Couleur::setB(unsigned char b1){this->b =b1; }
void Couleur::setA(unsigned char a1){this->a =a1; }

void Couleur::genCouleurAleatoire(){
    r=rand()%205;
    g=rand()%205;
    b=rand()%205;
    a=255;//rand()%150 + 100;
}

Couleur::~Couleur(){};
