#pragma once

#include "Mur.h"
#include "Image.h"
#include "Menu.h"
#include "Joueur.h"
#include "Reseau.h"
#include "Terrain.h"

#include <vector>
#include <string>

#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>
#include <iostream>
#include <fstream>

class Jeu{

protected:

    Terrain t;
    Joueur j;
    Joueur j2;

    //etat d'avancement
    etat etatDeJeu;
    std::vector<Cercle> petitCercles;
    std::vector<Mur> murs;
    Image imgMurs;
    Image imgTerrain;
    Image imgPtCercle;

    // dans le multijoueur
    Reseau r;
    
    // pour les niveaux
    int fd_file;
    int v_niveau;
    std::vector<Cercle> point_arrive;
    void last_niveau();
    int v_last_niveau;

    // initialise le terrain de jeu ,generer les murs en fonction de la taille du terrain. 
    void init();
    // initialise des images dans nos elements murs, cercles ..
    void init_imgs();
public:
    /**
     * @brief ouvre un ficher dans le fd_file les mode sont 
     *      'r' read , 'w' write vide le fd 'a' append 'b' rw et 'c' creat
    */
    void init_fd_niveau(int n_niveau,char mode);
    Jeu();
    ~Jeu();
    /**
     * @brief initialise le jeu selon l'etat
    */
    void init(const etat e, unsigned int niveau = 1);
    /**
     * @brief mets à jours le jeu selon l'etat
    */
    void update();
    /**
     * les gets et les sets
    */
    Terrain &getTerrain();
    Joueur &getJoueur();
    Joueur &getJoueur2();
    Camera &getCam(){return j.getCam();}
    std::vector<Cercle> &get_point_arrive(){return point_arrive;}
    std::vector<Cercle> &getPtitCercles();
    std::vector<Mur> &getMurs();
    std::string getImageMur() const;
    void setImageMur(const std::string &);
    std::string getImageTerrain() const;
    void setImageTerrain(const std::string &);
    std::string getImgPtCercle() const;
    void setImgPtCercle(const std::string &);
    etat getEtatDeJeu() const;
    void change_etat(const etat e);
    /**
     * @brief sauvgarde le jeu dans un descripteur de fiche
    */
    void sauver(int fd, bool init = false) const;
    /**
     * @brief chergele le jeu à partir d'un fd
    */
    void charger(int fd, bool init = false);


};

