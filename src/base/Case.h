#pragma once

#include "Rectangle.h"
#include "Vec2.h"

/**
 * @brief coorepond aux différents état du jeu. la boucle principale et init du jeu change 
 * selon le choix.
*/

enum etat{
    jeuLibre = 1, dansLeMenu = 2, quitter = 3, jeuUnNiveau = 4, JeuMulti = 5
};

class Case : public Rectangle{
protected:
    etat etat_to_return;
    std::string contenu;

public:
    /**
     * @brief constructeur pas copie initié.
     **/
    Case(const Vec2  & _posMin = Vec2(0,0),unsigned int w = 1,unsigned int h = 1) : Rectangle(_posMin,w,h){};
    /** 
     * @brief constructeur par default.
     **/
    Case(const Vec2  & _posMin,unsigned int w ,unsigned int h,const std::string & s,const etat e = jeuLibre);
    ~Case();
    std::string getContenu() const ;
    void setContenu(const std::string & );

    /**
     * @brief Retourne si la case est appouyyé. 
    */
    
    bool pressed(const Vec2 &) const;
    /**
     * @brief retourne l'etat courant de la case
    */
   etat get_etat() const;
}; 