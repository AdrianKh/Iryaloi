#pragma once

#include "Rectangle.h"
#include "Cercle.h"
#include "Rectangle.h"
#include "Terrain.h"

/**
 * @brief hérite du class Rectangle cette classe permet de afficher que les objet sur la camera
*/
class Camera : public Rectangle{ // héritage de la classe Rectangle
// toutes les donées et fonctions membres sont accessibles dans la classe Camera 
protected:    
    Vec2 * CamCercle;
public:
    /**
     * @creer une camera avec la position posMin, largeur et hauteur w et h en utilisant le constructeur du Rectangle
    */
    Camera( const Vec2  & _posMin = Vec2(0,0),unsigned int w = 1,unsigned int h = 1):Rectangle(_posMin,w,h){};
    Camera(const Rectangle & rec, Vec2 * c ):Rectangle(rec){CamCercle = c;};
    Vec2 * getCamCercle(){return CamCercle;};
    Vec2 getCamPos()const;
    Vec2 & getPosRef();
    bool estDansLaCamera(const Cercle &) const;
    bool estDansLaCamera(const Rectangle &) const;
    /**
     * @brief prends un pointeur comme la posiotion de camera
     * on va l'utiliser pour mettre l'addresse de la position d'un cercle
    */
    void setPos(Vec2 *);
    void resteDansLeTerrain(const Terrain&);
    ~Camera();
};