#include "Iryal_io.h"

using namespace std;


// jeuLibre = 1, dansLeMenu = 2, quitter = 3, jeuUnNiveau = 4, JeuMulti = 5

int main()
{
    srand(time(NULL));
    Iryal_io jeu;
    jeu.init();
    jeu.run();
    return 0;
}