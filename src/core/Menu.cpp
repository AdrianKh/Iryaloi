#include "Menu.h"

#include <assert.h>

Menu::Menu(){
    home.resize(0);
}

void Menu::init(){
    home.resize(0);
    home.push_back(Case(Vec2(400,100),400,50,"Jouer mode libre",jeuLibre));
    home.push_back(Case(Vec2(400,150),400,50,"Jouer mode multijoueur",JeuMulti));
    home.push_back(Case(Vec2(400,200),400,50,"Jouer les niveaux",jeuUnNiveau));
}
etat Menu::get_etat(const Vec2 & v)const{
    for(unsigned int i=0; i<home.size(); i++)
    {
        if(home[i].pressed(v))
            return home[i].get_etat();
    }
    return dansLeMenu;
}