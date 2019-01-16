#pragma once
#include "Vec2.h"
#include "Cercle.h"
#include "Couleur.h"

#include <iostream>
#include "tools.h"


class Rectangle{

protected:
    Vec2 pos;
    unsigned int w,h;
public:

    /// @brief cree un rectangle avec _posMin comme pos et largeur w et hauteur h
    explicit Rectangle( const Vec2  & _posMin = Vec2(0,0),unsigned int w = 1,unsigned int h = 1 );
    /// @breif constructeur par copie
    explicit Rectangle (const Rectangle & rec);
    /// @destructeur par default
    ~Rectangle();

    ///@brief get/set pour la position max et min 
    Vec2 getPos() const;
    void setPos(const Vec2 &pos);
    unsigned int getWidth() const;
    unsigned int getHeight() const;
    void setWidth(unsigned int);
    void setHeight(unsigned int);
    /**
     * @brief verifie si un cercle est dans un rectangle
    */
    bool estDans(const Cercle &c) const;
    /**
     * @brief enregistrer le terrain dans un file descripteur.
     * le format est "pos.x' 'pos.y' 'w' 'h'\n'" 
    */
    void sauver(int fd) const;
    /**
     * @brief charge le terrain à d'un file descripteur
    */
    void charger(int fd);

    /// @brief surcharge pour des flux de sortie comme cout<<
    friend std::ostream& operator<< (std::ostream  & flux, const Rectangle& r) {
        flux << r.getPos()<<" "<<r.getWidth()<<" "<<r.getHeight();
        return flux;
    }
    /// @brief surcharge pour des fllux d'entrée comme cin>>
    friend std::istream& operator>> (std::istream  & flux, Rectangle& r) {
        flux>>r.pos>>r.w>>r.h;
        return flux;
    }


};