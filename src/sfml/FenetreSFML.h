#pragma once

#include <string>
#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Jeu.h"
#include "Mur.h"
#include "Vec2.h"
#include "Menu.h"
#include "Image.h"
#include "Couleur.h"
#include "Joueur.h"
#include "Cercle.h"
#include "Camera.h"
#include "Terrain.h"
#include "Rectangle.h"


class FenetreSFML
{
  protected:
    sf::RenderWindow win;
    sf::ContextSettings settings;
    unsigned int _w;
    unsigned int _h;
    Vec2 mousePos;
    Camera *cam;
    bool open;
    sf::Event evt;
    sf::View viewport;
    bool space;
    bool mouse;
    bool key_f;

    // obj to draw
    sf::CircleShape cercle;
    sf::RectangleShape rectangle;
    sf::Texture textRec;
    sf::Texture *texJoueur;
    sf::Texture *texMurs;
    sf::Texture *texTerrain;
    sf::Texture *texPtCercle;
    sf::Texture *texMenu;
    sf::Text text;
    sf::Font font;
    sf::Texture textCer;
    void initShapes();
    // sons
    sf::Music bg_music;
    int bg_num;
    int next_bg;
    void init_max_track();
    int max_audio_tracks;
    

  public:
    FenetreSFML();
    FenetreSFML(const std::string &name, const unsigned int w, const unsigned int h);
    ~FenetreSFML();
    sf::RenderWindow &getWin();
    void init(const std::string &name, const unsigned int w, const unsigned int h);
    bool isOpen();
    /**
     * @brief genere des evenements en générale comme les touches resize la position de la souris et la camera.
     * attetion cette fonction nécéssite un objet Camera c'est à dire il faut setView(cam *) avant de l'uiliser
    */
    void gererEvenement();
    void display();
    void getMousePos(int &x, int &y) const;
    Vec2 getMousePos() const;
    void clear(sf::Color c = sf::Color::White);
    void fps(unsigned char fps);
    void setView(Camera *);
    void updateView();

    void draw(const Cercle &c);
    void draw(const Rectangle &r);
    void draw(const Terrain &t);
    void draw(const Camera &);
    void draw(const Mur &m);
    void draw(Joueur &j, bool j_actuelle = true);
    void draw(Jeu &j);
    void draw(const Case &);
    void draw(Menu &);
    /**
     * @brief verifie si la touche a été appouyé.attention la fonction marche que pour les touches Z S Q D
     * et prend un cher en parametre.
     * ex: 
     * Z = UP
     * S = DOWN
     * Q = LEFT
     * D = RIGHT
    */
    bool isKeyPressed(char key);
    /**
     * @brief verifie si la touche a été appuyé. 
     * ex: 
     * "UP" = UP
     * "DOWN" = DOWN
     * "LEFT" = LEFT
     * "RIGHT" = RIGHT
    */
    bool isKeyPressed(std::string &key);
    /**
     * @brief retourne vrai si l'espace est appuyer
    */
    bool spacePressed();
    /**
     * @brief dit si la touche gauche de la souris a été appuyé
    */
    bool mousePressed();

    /**
    * @brief set the bg music from a pathname this will play repitatedly
   */
    void set_bg_music(const std::string &chemin);
    /**
     * @brief renvoie si la music couratn est finit
    */
    bool bg_is_finished();
    /**
   * @brief comme son nom arrete la musique du fond
  */
    void stop_bg_music();
    /**
   * @brief augmente le volume de musique du fond
  */
    void volume_up();
    /**
     * @brief diminue le volume de music de fond
    */
    void volume_down();
    /**
   * @brief commence à jouer à partir de 1.ogg
  */
    void bg_auto();
    /**
     * @brief jeu la musique suivant selon next_bg
    */
    void play_next();
    /**
     * @brief retourne si f a été appuyé
    */
    bool pressed_f();
};