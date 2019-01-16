#include "Menu.h"
#include <iostream>

#include "FenetreSFML.h"

using namespace std;

int main(){

    FenetreSFML window;
    window.init("Jeu 1", 1000, 600);
    Menu m;
    m.init();

    while (window.isOpen())
    {
        window.gererEvenement();
        window.clear(sf::Color::White);
        window.draw(m);
        window.display();
    }
    
    return 0;
}