#pragma once

#include <vector>
#include <string>

#include "Mur.h"
#include "Vec2.h"
#include "Cercle.h"
#include "Camera.h"
#include "Rectangle.h"
#include "cstring"


class Joueur{
protected:
    std::vector<Cercle> cercles;
    Camera cam;
    Rectangle miniTerrain;
    unsigned int score;
    Image im;
    Vec2 tmp_cam;
public:
    Joueur();
    Joueur(const Vec2 &pos ,int r );
    /// @destructeur par default
    ~Joueur(){};
    void init();
    unsigned int get_score() const;
    void add_score(unsigned int);
    std::vector<Cercle> & getTabCercle();
    float getscore(){return score;}
    Camera & getCam(){return cam;}

    //le joueur a la possibilité de choisir une image qui le represente 
    std::string getImage() const{return im.get_lien();}
    void setImage(const std::string & s) {im.set_lien(s);}
    void deplacerJoueur(const Vec2& direction);
    void collision(const Terrain &);
    //pour la collision entre le mur et tous les cerles du joueur
    void collision(const Mur &);
    /**
     * @brief l'action néccéssaire en de collision avec un cercle. 
     * ex: manger un cercle si c'est plus petit /  rajoute des points au score 
    */
    bool actionCercle(Cercle &);
    /**
     * @brief fait l'action néccésaire pour le jeu en ligne
    */
    void actionJoueur(Joueur &);
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void sauver(int fd) const;
    void charger(int fd);
    /**
     * @brief divise tous les cercles en deux si le rayon > 50
    */
    void diviser();
    /**
     * @brief fussionne les cercles deux par deux.
    */
    void fussionner();
    /**
     * @brief gére les collision entre ses propre cercle
    */
    void collision_entre_cercles();
    /**
     * @brief retourne vraie si tous les cerles du joueur ont r = 0 ou il n'y a aucun cercle
     * et dans int n met le quelle est différent de 0
    */
   bool all_zero(int & n);
   /**
    * @brief met à jours la camera de joueur
   */
  void update_cam();
};