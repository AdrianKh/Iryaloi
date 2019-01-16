#include "Terrain.h"
#include "Fenetre.h"

using namespace std;


int main()
{
    Terrain t(Vec2(50,50),1000,800);
    Fenetre Win("Terrain",600,400);
    Camera cam(Vec2(0,0),600,400);
    Cercle c(50,Vec2(0,0),5);
    Win.Couleur(Couleur(255,0,0,255));
    Uint32 tempsCalcule;
    while(!Win.estFerme())
    {
        tempsCalcule = SDL_GetTicks();
        Win.clear(Couleur(22,22,22,22));
        Win.gererEvenement();
        c.bougerCercle(Win.mousePos());
        t.collision(c);
        cam.suitCercle(c);
        Win.draw(t);
        Win.Couleur(Couleur(0,255,0,255));
        Win.draw(c);
        Win.Couleur(Couleur(255,0,0,255));
        Win.afficheRectangle(cam);
        Win.afficheRender();
        Win.fps(30,SDL_GetTicks() - tempsCalcule);
    }
    return 0;
}