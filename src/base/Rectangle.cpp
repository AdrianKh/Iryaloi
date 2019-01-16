#include "Rectangle.h"

#include <string>

using namespace std;

Rectangle::Rectangle( const Vec2  & _posMin,unsigned int w,unsigned int h){
    setPos(_posMin);
    setWidth(w);
    setHeight(h);
}

Rectangle::Rectangle(const Rectangle & rec){
    setPos(rec.getPos());
    setWidth(rec.getWidth());
    setHeight(rec.getHeight());
}

Rectangle::~Rectangle(){}

Vec2 Rectangle::getPos() const{ 
    return pos;
}
void Rectangle::setPos(const Vec2 &pos){
    this->pos = pos;
}
unsigned int Rectangle::getWidth() const{
    return w;
}
unsigned int Rectangle::getHeight() const{
    return h;
}
void Rectangle::setWidth(unsigned int w){
    this->w = w;
}
void Rectangle::setHeight(unsigned int h){
    this->h = h;
}
bool Rectangle::estDans(const Cercle &c) const{
    if((c.getPosX() + c.getRayon()) < pos.getX()) return false;
    else if((c.getPosY() + c.getRayon()) < pos.getY()) return false;
    else if((c.getPosX() - c.getRayon()) > pos.getX() + w) return false;
    else if( (c.getPosY() - c.getRayon()) > pos.getY() + h) return false;
    return true;
}
void Rectangle::sauver(int fd) const{
    string tmp = "";
    tmp += to_string(pos.x);
    tmp += " " + to_string(pos.y);
    tmp += " " + to_string(w);
    tmp += " " + to_string(h) + '\n';
    save(tmp,fd);
    tmp.clear();
}
void Rectangle::charger(int fd){
    string tmp = "";
    tmp += read_line(fd);
    //verif_reciv(tmp);
    std::string::size_type mot = 0, nbr_char;
    pos.x = stof(tmp,&nbr_char);
    mot += nbr_char;
    pos.y = stof (tmp.substr(mot),&nbr_char);
    mot += nbr_char;
    w = stoul(tmp.substr(mot),&nbr_char);
    mot += nbr_char;
    h = stoul(tmp.substr(mot),&nbr_char);
}