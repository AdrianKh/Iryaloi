#include "console.h"
#include "Cercle.h"
#include "Joueur.h"
#include <vector>

using namespace std;

void collisions(Joueur &j,console & a){
    a.getTerrain().collision(j.getTabCercle()[0]);
    a.getTerrain().collision(j.getTabCercle()[1]);
}


void initRec(vector <Rectangle> & Rec){
    Rec.push_back(Rectangle(Vec2(25,25),3,3));
    Rec.push_back(Rectangle(Vec2(20,20),3,7));
    Rec.push_back(Rectangle(Vec2(30,15),3,10));
    Rec.push_back(Rectangle(Vec2(4,50),3,10));
}

int main(void)
{   
    // utlise la classe Mur
    // tu peux aussi afficher les petit cercle
    // utilise la classe Jeu
    vector <Rectangle> Rec;
    console a(30,20);
    Joueur j(Vec2(3,3),6);
    initRec(Rec);
    char input = '0';
    while(input != 'f')
    {
        a.effaceConsole();
        a.dessineTabcer(j.getTabCercle());
        //a.dessineTabrec(Rec);
        a.afficheConsole();
        cin>>input;
        j.deplacerJoueur(input);
        // adrian regarde mainJeu.cpp
        
        a.viderConsole();
    }
    a.effaceConsole();

    return 0;
}