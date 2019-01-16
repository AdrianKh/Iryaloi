#include "Cercle.h"

#include <cmath>
#include <time.h>       /* time */
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <assert.h>

using namespace std;
Cercle::Cercle(unsigned int _r,const Vec2 &pos,const Vec2 &_vitesse)
{
    //@brief acceleration du cercle en fonction de son rayon r. 
    r = _r;
    posCentre = pos;
    vitesse = _vitesse;
    if(r<10)
        acceleration = 0.0f;
    else
    acceleration = 200/r;
    
}
// @brief fonction retourne l'acceleration en fonction du rayon r.
float Cercle::getAceleration() const{
    return 200.0f/r;
}


Cercle::Cercle(const Cercle & c)
{
    r = c.r;
    posCentre = c.posCentre;
    vitesse = c.vitesse;
}
Cercle::Cercle(float x,float y,float r){
    *this = Cercle(r,Vec2(x,y));
}

void Cercle::setPosVec2(float x, float y){
    posCentre.setX(x);
    posCentre.setY(y);
}
float Cercle::getRayon() const { return r; }
void Cercle::setRayon(float _r){ r = _r;}
float Cercle::getPosX() const { return posCentre.getX();}
float Cercle::getPosY() const { return posCentre.getY();}
Vec2 &Cercle::getPosVec2() { return posCentre;}
Vec2 Cercle::getPos() const{return posCentre;}
float Cercle::getAire() const{return M_PI*r*r;}

void Cercle::ajouteAire(unsigned int aire){r += sqrt(aire/M_PI);}

void Cercle::supprimeAire(unsigned int aire){r -= sqrt(aire/M_PI);}

void Cercle::mangeCercle( Cercle & cer)
{
    r += cer.getRayon()/80;
    cer.setRayon(0);
}

Vec2 & Cercle::getVitesse(){
    return vitesse;
}
void Cercle::bougerCercle(const Vec2 &direction)
{
    if(direction.distance(posCentre) < r)
        return;
    Vec2 delta = direction - getPos();
    vitesse = delta.normalise();
    posCentre += vitesse*getAceleration();

}
void Cercle::setCouleur(const Couleur& co){
    this->c=co;
 }

 bool Cercle::collision(const Cercle & c) const{
    return posCentre.distance(c.getPos()) < r + c.r;
}

const Cercle Cercle::operator + (const Cercle &c) const{
    Cercle c1;
    c1.r= this->r + c.r;
    c1.setPosVec2(getPos());
    return c1;
}

const Cercle Cercle::operator - (const Cercle &c) const{
    Cercle c1;
    c1.r= this->r - c.r;
    return c1;
}

const Cercle Cercle::operator * (const float k) const{
    Cercle c1;
    c1.r= this->r * k;
    return c1;
}

const Cercle Cercle::operator / (const float k) const{
    Cercle c1;
    assert(k!=0);
    c1.setPosVec2(posCentre);
    c1.r= this->r / k;
    return c1;
}

bool Cercle::operator < ( const Cercle& cer ) const{ 
    return r < cer.r;
}

bool Cercle::operator > ( const Cercle& cer ) const{
    return r > cer.r;
}
Cercle::~Cercle(){}


bool Cercle::estDans(const Cercle & cer) const{
    if(*this < cer)
        return false;
    return posCentre.distance(cer.getPos())+cer.getRayon() < r;
}

Cercle Cercle::genCercleAlea(const Vec2& pos,unsigned int w, unsigned int h,  unsigned int _r) const{
    int posX, posY;
    posX = rand() % (w - 2*_r) + pos.getX()+_r + 5;
    posY = rand() % (h - 2*_r) + pos.getY()+_r + 5;
    return Cercle(_r,Vec2(posX,posY));
}


void Cercle::sauver(int fd) const{
    string tmp = "";
    tmp += to_string(posCentre.x);
    tmp += " " + to_string(posCentre.y);
    tmp += " " + to_string(r) + '\n';
    save(tmp,fd);
    tmp.clear();
}

void Cercle::charger(int fd){
    string tmp = "";
    tmp += read_line(fd);
    //verif_reciv(tmp);
    std::string::size_type mot = 0, nbr_char;
    posCentre.x = stof(tmp,&nbr_char);
    mot += nbr_char;
    posCentre.y = stof(tmp.substr(mot),&nbr_char);
    mot += nbr_char;
    r = stof(tmp.substr(mot),&nbr_char);
}