#pragma once

#include <iostream>

class Couleur
{
protected:

public:
    unsigned char r,g,b,a;
    ///@brief Constructeur de la classe par defaut. l
    Couleur(unsigned char r1=0,unsigned char g1=0,unsigned char b1=0, unsigned char a1=0);
    ///@brief constructeur par copie. 
    Couleur(const Couleur & c);
    unsigned char getR()const ;
    unsigned char getG()const;
    unsigned char getB()const ;
    unsigned char getA()const ;
    
    void setR(unsigned char r2);
    void setG(unsigned char g2);
    void setB(unsigned char b2);
    void setA(unsigned char a2);

    ~Couleur();
    /**
     * @brief genere une couleur aléatoirement différent du blanc 0 <= r, g, b, a <= 255
     * r + g + b + a != 255+255+255+255 
    */
    void genCouleurAleatoire();

        friend std::ostream& operator<< (std::ostream  & flux, const Couleur c) {
        flux << (int)c.r<<" "<<(int)c.g<<" "<<(int)c.b<<" "<<(int)c.a<<" ";
        return flux;
    }

    friend std::istream& operator>> (std::istream  & flux, Couleur& c) {
        flux>>c.r>>c.g>>c.b>>c.a;
        return flux;
    }

};