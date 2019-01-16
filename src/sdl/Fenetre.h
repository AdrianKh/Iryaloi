#pragma once

#include "Mur.h"
#include "Couleur.h"
#include "Joueur.h"
#include "Cercle.h"
#include "Camera.h"
#include "Terrain.h"
#include "Rectangle.h"

#include <queue>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>


class Fenetre
{
protected:
	bool quite;
	SDL_Window * fenetre;
	SDL_Renderer * renderer;
	unsigned int largeur, hauteur;
	std::string titre;
	SDL_Event event;
	Couleur Couleur_c;
	SDL_Surface * icone;

	Vec2 *_origine;
	Vec2 posTmp;

	bool keyboardIsPressed;
	SDL_Scancode lastKeyPressed;
	std::queue<SDL_Scancode> keys;

	/**
	 * @brief initsialise sdl2. crée une fenetre et un renderer
	 * @param Titre de la fenetre
	*/
	bool initSdl2(const std::string &Titre,const unsigned int largeur, const unsigned int hauteur);
	void clearEvents();

public:
	Fenetre();
	
	/**
	 * @brief appelle initSdl2
	 * @param Titre de la fenetre
	*/
	Fenetre(const std::string &Titre,const unsigned int largeur, const unsigned int hauteur);
	~Fenetre();
	/**
	 * @brief retourne vraie si la est fermé
	*/
	bool estFerme();
	bool isOpen();
	unsigned int getLargeur();
	unsigned int getHauteur();
	/**
	 * @brief met la couleur d'affichage des objets
	*/
	void color(Couleur c);

	SDL_Renderer * getRenderer(){return renderer;}
	/**
	 * @brief éfface la fond avec la Couleur passe en param
	*/
	void clear(const Couleur c);
	/**
	 * @brief éfface la fond en blanc
	*/
	void clear();
	//void afficheRectangle(const Rectangle & r);
	/**
	 * @brief affiche le renderer sur la fenetre créé. c'est à dire afficher tous les objet dessinés avec draw
	*/
	void afficheRender();
	/**
	 * @brief gère les evenements SDL. 
	 * Ex: souris, clavier, fermer la fenetre
	 * --- !! Important les fonctions keyPressed(),getLastKey() depend du gererEvenement() !! ---
	 * 		  donc il appeler gererEvenement() pour pouvoir les utiliser
	*/
	void gererEvenement();
	/**
	 * @brief determine le nombre d'image par seconde
	 * @param fps le nombre d'image et tempsDeCalcule temps pour tous les calcules ex: affichage, mise-à-jours des objets etc.
	*/
	void fps(unsigned char fps,const Uint32 tempsDeCalcule);
	/**
	 * dessine un Rectangle parrapport à l'origine
	*/
	void afficheRectangle(const Rectangle &r);
	/**
	 * dessine un Cercle remplit de Couleur_c parrapport à l'origine
	*/
	void draw(const Cercle &c);
	/**
	 * dessine un Rectangle remplit de Couleur_c parrapport à l'origine
	*/
	void draw(const Rectangle &r);
	void draw(const Terrain &t);
	void draw(const Camera &c);
	void draw(const Mur &m);
	void draw(Joueur &j);
	void setIcone(const std::string &chemin);
	
	/**
	 * @brief met le repère dans la quelle les objets vont être dissigner modofie pas l'origine
	 * 
	*/
	void setOrigine(Vec2 *origine);
	bool keyPressed();
	/**
	 * @brief renvoie la dernière touche appouyer dans le cas il n'y a pas touche renvoie 
	 * ex: U up, D down, L left, R right
	*/
	const char getLastKey();
	Vec2 mousePos() const;

};