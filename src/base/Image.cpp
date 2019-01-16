#include "Image.h"

#include <fstream>
#include <unistd.h>
#include <iostream>
#include <string>

using namespace std;



Image::Image(){
    lien.clear();
}
Image::Image(const std::string &_lien)
{
    set_lien(_lien);
    
}
Image::Image(const char * _lien){
    set_lien(_lien);
}
Image::~Image(){
    lien.clear();
}
void Image::set_lien(const std::string &_lien){
    lien.clear();
    lien += _lien;
}
void Image::set_lien(const char * _lien){
    lien.clear();
    lien += _lien;
}
std::string Image::get_lien() const{
    return lien;
}

bool Image::valide() const{

    if(lien.size() == 0)
        return false;

    if( access( lien.c_str(), R_OK ) == -1)
        return false;

    return true;
}
void Image::print() const{
    std::cout<<lien<<"\n";
}
Image Default(){
    return Image("data/img/default.png");
}
Image Wall1(){
    return Image("data/img/wall1.jpg");
}