#pragma once

#include "Jeu.h"
#include "FenetreSFML.h"


// jeuLibre = 1, dansLeMenu = 2, quitter = 3, jeuUnNiveau = 4, JeuMulti = 5
class Iryal_io{

protected:
    Jeu j;
    FenetreSFML win;
    Camera menu_cam;
public:
    /**
     * @brief initialise le jeu et demande à l'utilisateur quel niveau pour commancer.
    */
    void init();
    /**
     * @brief execute le jeu 
    */
    void run();

};