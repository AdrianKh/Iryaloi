#include <iostream>
#include <cstdlib>

#include "Cercle.h"
#include "FenetreSFML.h"

using namespace std;

void drawCercle();

int main()
{
    drawCercle();
   // cout<< ce.vitesse <<ce.r<<endl;
    return 0;
}

void drawCercle(){
    Cercle ce(30,45,100);
    
    FenetreSFML window;
    window.init("Cercle 1",1000,600);

    while(window.isOpen())
    {
        window.gererEvenement();
        window.clear();
        ce.bougerCercle(window.getMousePos());
        window.draw(ce);
        window.display();

    }
}