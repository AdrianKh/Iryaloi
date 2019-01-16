#include "Camera.h"



Camera::~Camera(){
}

Vec2 & Camera::getPosRef(){
    return pos;
}

void Camera::setPos(Vec2 * p){
    CamCercle = p;
}
bool Camera::estDansLaCamera(const Cercle &c) const
{
    // le meme que rectangle
    return Rectangle(*CamCercle,w,h).estDans(c);
}
Vec2 Camera::getCamPos()const
{
    return *CamCercle - Vec2(w,h)/2;
}

bool Camera::estDansLaCamera(const Rectangle &r) const
{
    if(r.getPos().getX() + r.getWidth() < CamCercle->getX()) return false;
    else if(r.getPos().getY() + r.getHeight() < CamCercle->getY()) return false;
    else if(r.getPos().getX() > CamCercle->getX()+w) return false;
    else if(r.getPos().getY() > CamCercle->getY()+h) return false;
    return true;
}
