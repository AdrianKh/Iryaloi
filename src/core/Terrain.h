#pragma once

#include "Cercle.h"
#include "Rectangle.h"

/**
 * @brief un terrain possède une position, un largeur et une hauteur.
 * @details les accesseur et les mutateur sont les meme que le class Rectangle. en plus des focntions de la classe
 * Rectangle le terrain dectect ausssi les cillisions et ainsi ne permet pas aux objets de sortir du terrain
*/

class Terrain : public Rectangle
{

  protected:
  public:
    /**
     * @brief Constructeur par default utilise celle du Rectangle
    */
    Terrain(const Vec2 &_posMin = Vec2(0, 0), unsigned int w = 1, unsigned int h = 1) : Rectangle(_posMin, w, h){};
    Terrain(const Rectangle &rec) : Rectangle(rec){};
    /**
     * @brief verifie si le cercle sort du terrain 
     * dans le cercle sort il le remet dans le terrain
    */
    void collision(Cercle &) const;
    /**
     * @brief verifie si le Rectangle sort du terrain 
     * dans le cercle sort il le remet dans le terrain
    */
    void collision(Rectangle &);
    /**
     * @brief verifie si le Triangle sort du terrain 
     * dans le cercle sort il le remet dans le terrain
    */
    //void collision(Triangle &);
};