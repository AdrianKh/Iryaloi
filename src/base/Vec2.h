#pragma once
#include <iostream>

/** @brief une Class permet de gérer des vecteur 2D ainsi que diffétentes operations.
*   @details:
    EX: @code{.cpp}
    Vec2 v1(3,8); // creation d'un vecteur
    Vec2 v2(v1); // constructeur par copie
    Vec2 v3 = v1 + v2; // addition de deux vecteur v1 et v2 ne sont pas modifiés

    // et idème pour les autres operations - *
    @endcode
*   @param x et y sont deux variable privé contient les valeurs
*
* */

class Vec2{
protected:

public:
    float x, y;
    /** @brief constructeur par default
     *  @param x y float veut 0 par default
     * @code
     * Vec2 v(); //v.x=v.y=0
     * VecZ v1(3,6); // v.x=3 v.y=6
     * @endcode
     *
     * */
    Vec2( const float _x= 0, const float _y= 0 ) : x(_x), y(_y) {}
    /**
     * @brief constructeur par copie
     * @param v vec2
     * @code
     * Vec2 v(3,6); //v.x=3 v.y=6
     * VecZ v1(v); // v.x=3 v.y=6
     * @endcode
     *
     * */
    Vec2(const Vec2 &v) : x(v.x), y(v.y){}
    /// @brief destructeur Vec2
    ~Vec2();

    /**
     * @brief Distance entre deux vecteur 2D v1 et v2
     * @param v est un vecteur 2D
     * @return {Vec2}
     *
     * */
    float distance(const Vec2 & v) const;
    /** @brief renvoie v1 + v2
     *  @param v est un vecteur 2D
     *  @return {Vec2}
     *
     * */
    bool operator == (const Vec2& v) const;

    const Vec2 operator + (const Vec2 &v) const;
    const Vec2 operator - (const Vec2 &v) const;
    //const Vec2 operator * (const Vec2 &v) const;
    //! renvoie le vecteur v*k;
    const Vec2 operator * (const float k) const;
    //! renvoie le vecteur v/k;
    const Vec2 operator/ ( const float k) const;
    /// @brief
    Vec2 operator+=(const Vec2& v) { x += v.x; y += v.y; return *this; }
    Vec2 operator-=(const Vec2& v) { x -= v.x; y -= v.y; return *this; }
    Vec2 operator*=(const float k) { x *= k; y *= k; return *this; }
    Vec2 operator/=(const float k) { x /= k; y /= k; return *this; }
    ///@brief la surcharge de cout/cin
    friend std::ostream& operator<< (std::ostream  & flux, const Vec2& d) {
        flux << d.getX()<<" "<<d.getY()<<" ";
        return flux;
    }

    friend std::istream& operator>> (std::istream  & flux, Vec2& d) {
        flux>>d.x>>d.y;
        return flux;
    }

    /// @brief affiche le vecteur sous forme x:4, y:6 endl
    void print() const;
    void setX(float _x){ x =_x;}
    void setY(float _y){ y = _y;}
    void setVec(const Vec2& v){ x = v.x; y = v.y;}


    float getX() const {return x;}
    float getY() const {return y;}
    /**
    *@brief retourner le vecteur normaliser
    *@param
    *@code return vectn // vectn.x=x/norme  vect.y=y/norme
    */
    Vec2 normalise()const;

    //! renvoie le vecteur -v.
    Vec2 operator- ();

};