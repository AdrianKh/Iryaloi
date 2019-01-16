#pragma once
#include "Vec2.h"
#include "Couleur.h"
#include "Image.h"
#include "tools.h"

#include <string>

class Cercle
{
protected:
    Vec2 posCentre;
    Vec2 vitesse;

    /// @brief l'acceleration est en fonction de la taille du cercle.
    float acceleration;
    Couleur c;
    
public:
    float r;
    /**
     * @brief deux constructeurs par default et par copie. 
    */
    Cercle(unsigned int _r = 0,const Vec2 &pos = Vec2(0,0),const Vec2 &_vitesse = Vec2(0,0));
    Cercle(float x,float y,float r);
    Cercle(const Cercle &c);

    ~Cercle();

    void setPosVec2(float x, float y);

    float getAcc() const{return acceleration;};
    Vec2 & getVitesse();
    /**
     * @brief retourne le rayon du cercle 
    */
    float getRayon() const;
    /**
     *@biref modifie le rayon du cercle 
    */
    void setRayon(float);
    /**
     * @brief retourne la cordoné du centre sur les ordonés du centre du cercle 
    */
    float getPosX() const;
    /**
     * @brief retourne la cordoné du centre sur l'apsis du centre du cercle 
    */
    float getPosY() const;
    /**
     * @brief retourne reference du centre du cercle
    */
    Vec2 &getPosVec2();
    Vec2 getPos() const;
    /**
     * @brief modifie position du cercle du cercle
    */
    void setPosVec2(const Vec2 &pos) { posCentre = pos;}
    /**
     *@brief retoune l'aire du cercle 
    */
    float getAire() const;
    /**
     *@brief ajoute le rayon d'un cercle passé en paramétre au rayon du cercle  
    */
    void ajouteAire(unsigned int aire);

    //bool collisionRectangle(const Rectangle &r);
    //bool collisionTerrain(const Rectangle &r);
    //bool estDansLaCamera(const Camera &c) const;7
    /**
     * @brief soustrait le rayon d'un cercle passé en parametre au rayon du cercle 
    */
    void supprimeAire(unsigned int aire);
    /**
     * @brief vérifie si le cercle passé en parametre est dans le cercle
     * @details il vérifie aussi si le cercle cer est plus petit que cercle
    */
    bool estDans(const Cercle & cer) const;
    /**
     * @brief genère et renvoie un cercle dans le rectangle passé en parametre
    */
    Cercle genCercleAlea(const Vec2&,unsigned int w, unsigned int h, unsigned int _r = 10) const;
    /**
     * @brief retourn vraie si il y a collision entre les cercle
    */
    bool collision(const Cercle &) const;
    /**
     * @brief mutateur de couleur
     */
  
    void setCouleur(const Couleur& co);


    /**
     * @brief annule le rayon du cercle passé en parametre si son 
     * rayon est strictement plus petit que celui du notre
     * && si la distance entre les centres des deux rayon = au rayon de notre cercle- le rayon du petit cercle 
     * ( le petit cercle est recouvert par le gros) 
    */
    void mangeCercle( Cercle & cer);
    /**
     * @brief fonction qui fais bouger le cercle en normalisant le vecteur delta.
    */
    void bougerCercle(const Vec2 &direction);

    float getAceleration() const;
    // surchage des operators 
    const Cercle operator + (const Cercle &c) const;
    const Cercle operator - (const Cercle &c) const;

    const Cercle operator * (const float k) const;
    const Cercle operator / (const float k) const;

    bool operator < ( const Cercle& cer ) const;
    bool operator > ( const Cercle& cer ) const;
    
    void sauver(int fd) const;
    void charger(int fd);

    friend std::ostream& operator<< (std::ostream  & flux, const Cercle& c) {
        flux<<c.getRayon()<<" "<< c.getPos();
        return flux;
    }

    friend std::istream& operator>> (std::istream  & flux, Cercle& c) {
        flux>>c.r>>c.getPosVec2();
        return flux;
    }
    
};