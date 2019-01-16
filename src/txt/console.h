#pragma once 
#include "Vec2.h"
#include "Terrain.h"
#include "Mur.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>

class console{
 protected:
    unsigned int dimx, dimy;
    char *grille;
    Terrain ter;
    void initGrille();
 public:
    console(unsigned int , unsigned int );
    ~console();
    Terrain & getTerrain();
    void setVal(unsigned int , unsigned int , char );
    char getValeur(unsigned int , unsigned int ) const;
    void effaceConsole();
    void afficheConsole()const;
    void viderConsole();
    void initTerrain();
    void dessineCercle(unsigned int ,unsigned int , unsigned int );
    void dessineCercle(const Cercle & ) ;
    void dessineRectangle(int, int , int ,int ) ;
    void dessineRectangle(const Rectangle &);
    void dessineTabrec(const std::vector<Rectangle>& v) ; 
    void initTabcer( std::vector <Cercle> & ,const Cercle &, int );
    void dessineTabcer(const std::vector<Cercle> &  );
};