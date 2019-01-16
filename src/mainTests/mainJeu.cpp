#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>
#include <fstream>

#include "Jeu.h"
#include "FenetreSFML.h"

using namespace std;

int main()
{
    srand(time(NULL));
    Jeu j;
    FenetreSFML window;
    window.init("Jeu 1", 1000, 600);
    j.init(jeuLibre);
    window.setView(&j.getJoueur().getCam());
    //int fd = open("data/ter.txt",O_RDWR);
    //j.sauver(fd);
    //j.charger(fd);
    while (window.isOpen())
    {
        window.gererEvenement();
        window.clear(sf::Color::Black);
        window.updateView();

        j.getJoueur().deplacerJoueur(window.getMousePos());
        if (window.spacePressed())
        {
            cout<<"space"<<endl;
            j.getJoueur().diviser();
        }
        j.update();
        window.draw(j);
        window.display();
    }
    //close(fd);
    //fd = open("data/ter.txt",O_RDWR);
    //j.sauver(fd);

    return 0;
}