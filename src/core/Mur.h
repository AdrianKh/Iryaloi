#pragma once

#include "Cercle.h"
#include "Rectangle.h"
#include "Image.h"

class Mur : public Rectangle{


protected:
    /**
     * @brief retoune un entier pour dire dans quelle coté la coiilison a lieu et mets la distance dans d
     * @details 0 pour cote gauche-haut 1 pour cote gauche ainsi de suite.
     * donc on tourne dans le snse anti-horaire et il y a 8 cote
    */
    //Image im;
public:
    /**
     * @brief constructeur prend une posotion la largeur et l'hauteur en paramètre et au final utilise le
     * constructeur le Rectangle
    */
    Mur(const Vec2  & _posMin = Vec2(0,0),unsigned int w = 1,unsigned int h = 1) : Rectangle(_posMin,w,h){};
    /**
     * @brief prend un Rectangle un paramètre pour construire le Mur
    */
    Mur(const Rectangle &r) : Rectangle(r){};
    /**
     * @brief detecte la collision d'un cercle en generale et prend l'action necessaire.
     * l'action par default est d'arrêter le cercle car c'est un mur.
     * @bug des fois la double collision ne marche pas.
     * la plupart des cas c'est se voit quand la distance entre deux mur est plus grand
     * que le rayon et inférieur 2*r.
     * 
    */
    void collision(Cercle &) const;
    /**
     * @brief retourne le lien vers l'image
    */
    //std::string getImage(){return im.get_lien();};
    /**
     * @brief met à jour le lien de l'image
    */
    //void setImage(const std::string & s){im.set_lien(s);};

    /**
     * @brief genere un mur aléatoirement dans le ractangle passe en param
    */
    Mur genereMurAlea(const Vec2 &, unsigned int w ,unsigned int h ) const;
};