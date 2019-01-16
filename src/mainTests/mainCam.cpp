#include "Camera.h"
#include "Fenetre.h"

using namespace std;

void test2();

int main()
{
    test2();
    return 0;
}

void test2()
{
    Fenetre Win("Cercle Est Dans Cam",600,400);
    Camera cam(Vec2(0,0),600,400);
    Cercle c(50,Vec2(0,0),5);
    Cercle petitCercles[10];
    for(int i=0;i<10;i++)
        petitCercles[i] = Cercle(20,Vec2(i*50,i*50),0);
    Win.color(Couleur(255,0,0,255));
    Win.setOrigine(&cam.getPosRef());
    Uint32 tempsCalcule;
    while(!Win.estFerme())
    {
        tempsCalcule = SDL_GetTicks();
        Win.clear(Couleur(22,22,22,22));
        Win.gererEvenement();
        c.bougerCercle(Win.mousePos());
        cam.suitCercle(c);
        Win.color(Couleur(0,255,0,255));
        Win.draw(c);
        Win.color(Couleur(255,0,0,255));
        for(int i=0;i<10;i++)
            if(cam.estDansLaCamera(petitCercles[i]))
                Win.draw(petitCercles[i]);
        Win.afficheRectangle(cam);
        Win.afficheRender();
        Win.fps(30,SDL_GetTicks() - tempsCalcule);
    }
}
