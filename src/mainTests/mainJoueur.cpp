#include "Mur.h"
#include "Joueur.h"
#include "Terrain.h"
#include "Fenetre.h"

void testAffiche();

int main()
{
    testAffiche();
    return 0;
}

void testAffiche(){
    Terrain t(Vec2(50,50),1000,800);
    Fenetre Win("Terrain",600,400);
    Camera cam(Vec2(0,0),600,400);
    Joueur j;
    Mur m(Vec2(200,200),400,200);
    Win.color(Couleur(255,0,0,255));
    Uint32 tempsCalcule;
    while(!Win.estFerme())
    {
        tempsCalcule = SDL_GetTicks();
        Win.clear(Couleur(22,22,22,22));
        Win.gererEvenement();
        Win.draw(m);
        Win.draw(t);
        j.deplacerJoueur(Win.mousePos());
        j.collision(t);
        j.collision(m);
        Win.color(Couleur(0,255,0,255));
        Win.draw(j);
        Win.color(Couleur(255,0,0,255));
        Win.afficheRectangle(cam);
        Win.afficheRender();
        Win.fps(30,SDL_GetTicks() - tempsCalcule);
    }
}