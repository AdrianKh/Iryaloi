#include "Terrain.h"

/**
 * @brief empeche la sortie du terrain en replaçant l'objet à sa posiotion precedente .
 **/
void Terrain::collision(Cercle & c) const{
    
    // empeche la sortie par la gauche du terrain.
    if(c.getPosX()<getPos().getX() + c.getRayon()){
        c.setPosVec2( Vec2(getPos().getX()+c.getRayon(),c.getPosY()) );
    }
    // sort par la droite du terrain.
    if(c.getPosX()+c.getRayon()>getPos().getX()+getWidth()){
        c.setPosVec2( Vec2(getPos().getX() + getWidth() - c.getRayon(),c.getPosY()) );
    }
    // sort par le haut.
    if(c.getPosY()-c.getRayon()<getPos().getY()){
        c.setPosVec2( Vec2(c.getPosX(),getPos().getY() + c.getRayon()) );
    }
    // sort par le bas.
    if(c.getPosY()+c.getRayon() > getPos().getY() + getHeight() ){
        c.setPosVec2(Vec2(c.getPosX(),getPos().getY()+getHeight() - c.getRayon()));
    }
}

