#include "Case.h"
#include "Cercle.h"

using namespace std;

string Case::getContenu()const {
    return contenu;
}

void Case::setContenu(const string & s){
    contenu = s; 
}
Case::~Case(){};
Case::Case(const Vec2  & _posMin,unsigned int w ,unsigned int h,const std::string & s,const etat e){
    pos = _posMin; 
    this->w= w;
    this->h = h;
    contenu = "";
    contenu += s; 
    etat_to_return = e;
}
bool Case::pressed(const Vec2 &) const{
    return estDans(Cercle(0,pos));
}
etat Case::get_etat() const{
    return etat_to_return;
}
