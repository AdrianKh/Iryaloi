#include "FenetreSFML.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

void createWin();


int main()
{
    srand(time(NULL));
    createWin();
    return 0;
}

void createWin()
{
    FenetreSFML fen;
    fen.init("Hello",600,400);
    /*Terrain t(Vec2(50,50),1000,800);
    Joueur j;
    Mur m(Vec2(200,200),400,200);
    m = m.genereMurAlea(t.getPos(),t.getWidth(),t.getHeight());*/
    while(fen.isOpen())
    {
        fen.gererEvenement();
        fen.clear();
        /*j.deplacerJoueur(fen.getMousePos());
        j.collision(m);
        j.collision(t);
        j.actionCercle();
        fen.draw(t);
        fen.draw(m);
        fen.draw(j);*/
        fen.display();
    }
}