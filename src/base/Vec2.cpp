#include "Vec2.h"
#include <cmath>
#include <iostream>
#include <assert.h>

using namespace std;

float Vec2::distance(const Vec2 & v) const
{
    return sqrt( (x-v.x)*(x-v.x) + (y-v.y)*(y-v.y));
}

void Vec2::print()const{
  cout<<"x :"<<this->x<<" , y :"<<this->y<<endl;
}

bool Vec2::operator == (const Vec2& v) const{
  return (v.x==x && v.y== y);
}

const Vec2 Vec2::operator + (const Vec2 &v) const{
    Vec2 vec;
    vec.x= this->x + v.x;
    vec.y= this->y + v.y;
    return vec;
}

const Vec2 Vec2::operator - (const Vec2 &v) const{
    Vec2 vec;
    vec.x= x - v.x;
    vec.y= y - v.y;
    return vec;
}

const Vec2 Vec2::operator * (const float k) const{
  Vec2 vec;
  vec.x= this->x * k;
  vec.y= this->y * k;
  return vec;
}

const Vec2 Vec2::operator/ ( const float k) const{
  Vec2 vec;
  assert(k!=0);
  vec.x= this->x / k;
  vec.y= this->y / k;
  return vec;
}

Vec2 Vec2::operator -(){
  Vec2 vecteur;
  vecteur.x= -this->x;
  vecteur.y= -this->y;
  return vecteur;
}


Vec2 Vec2::normalise()const{
  float norme= sqrt((x*x) + (y*y));
  Vec2 vectn;
  if (norme!= 0){
    vectn.x= x/norme;
    vectn.y= y/norme;
  }
  return vectn;

}

Vec2::~Vec2() {}