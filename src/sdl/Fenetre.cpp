#include "Fenetre.h"

#include <vector>
#include <iostream>
#include <assert.h>

using namespace std;

Fenetre::Fenetre()
{
	largeur = 0;
	hauteur = 0;
	fenetre = NULL;
	renderer = NULL;
	quite = true;
	_origine = NULL;


}

Fenetre::Fenetre(const std::string &Titre,const unsigned int largeur, const unsigned int hauteur)
{
	cout<<"Creation de la fenetre "<<Titre<<"...\n";
	if(!initSdl2(Titre,largeur,hauteur))
	{
		cout<<"\nInitialisation de sdl2 a échoué !!"<<endl;
		assert(0);
		exit(1);
	}
	cout<<" : Success!!"<<endl;
}

bool Fenetre::initSdl2(const std::string &Titre,const unsigned int largeur, const unsigned int hauteur)
{
	cout<<"initSdl2("<<Titre<<","<<largeur<<","<<hauteur<<")"<<endl;
	titre.clear();
	titre += Titre;
	_origine = new Vec2(0,0);
	this->largeur = largeur;
	this->hauteur = hauteur;
	quite = true;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
	{
      cout<<"SDL_Init Error: "<<SDL_GetError()<<endl;
      return false;
  	}

  	fenetre = SDL_CreateWindow(titre.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, largeur, hauteur, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  	if (fenetre == NULL)
  	{
      cout<<"SDL create win: "<<SDL_GetError()<<endl;
      SDL_Quit();
      return false;
  	}
	renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  	if (renderer == NULL)
  	{
      SDL_DestroyWindow(fenetre);
      cout<<"SDL_CreateRenderer Error: "<< SDL_GetError()<<endl;
      SDL_Quit();
      return false;
  	}
	quite = false;
	return true;
}
unsigned int Fenetre::getLargeur(){return largeur;}
unsigned int Fenetre::getHauteur(){return hauteur;}
bool Fenetre::isOpen(){return !quite;}
void Fenetre::setOrigine(Vec2 *origine){
	if(_origine) delete _origine;
	_origine = origine;
}

Fenetre::~Fenetre()
{
	clearEvents();
	_origine = NULL;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(fenetre);
	SDL_Quit();
	cout<<"Destruction de la fenetre "<<titre<<endl;
}

void Fenetre::clearEvents()
{
	while(!keys.empty())
	{
		keys.pop();
	}
}

void Fenetre::color(Couleur c)
{
	Couleur_c = c;
}

void Fenetre::clear(const Couleur c)
{
	SDL_SetRenderDrawColor(renderer,c.getR(),c.getG(),c.getB(),c.getA());
    SDL_RenderClear(renderer);
}

void Fenetre::clear()
{
	clear(Couleur(255,255,255,255));
}
void Fenetre::afficheRender()
{
	SDL_RenderPresent(renderer);
}
bool Fenetre::estFerme()
{
	return quite;
}
void Fenetre::gererEvenement()
{
	while(SDL_PollEvent(&event))
	{
		keyboardIsPressed = false;
		if(event.type == SDL_QUIT)
		{
			quite = true;
			break;
		}
		else if(event.type == SDL_WINDOWEVENT)
		{
			switch(event.window.event)
			{
				case SDL_WINDOWEVENT_SIZE_CHANGED:
					largeur = event.window.data1;
					hauteur = event.window.data2;
				break;

			}
		}
		else if(event.type == SDL_KEYDOWN)
		{
			if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				quite = true;
				break;
			}
			keys.push(event.key.keysym.scancode);
		}

	}
}

void Fenetre::fps(unsigned char fps,const Uint32 tempsDeCalcule)
{
	assert(fps!=0 && (1000-tempsDeCalcule) > 0);
	SDL_Delay((1000-tempsDeCalcule)/(int)fps);
}

void Fenetre::afficheRectangle(const Rectangle &r)
{
	posTmp = r.getPos();
	posTmp -= *_origine;
	rectangleRGBA(renderer,posTmp.getX(),posTmp.getY(),posTmp.getX()+r.getWidth(),posTmp.getY()+r.getHeight()
	,Couleur_c.getR(),Couleur_c.getG(),Couleur_c.getB(),Couleur_c.getA());
}


void Fenetre::draw(const Cercle &c)
{
	posTmp = c.getPos();
	posTmp -= *_origine;
	filledCircleRGBA(renderer,posTmp.getX(),posTmp.getY(),c.getRayon()
	,Couleur_c.getR(),Couleur_c.getG(),Couleur_c.getB(),Couleur_c.getA());
}


void Fenetre::draw(const Rectangle &r)
{
	posTmp = r.getPos();
	posTmp -= *_origine;
	boxRGBA(renderer, posTmp.getX(), posTmp.getY(),posTmp.getX()+r.getWidth(), posTmp.getY()+r.getHeight(),
	Couleur_c.getR(),Couleur_c.getG(),Couleur_c.getB(),Couleur_c.getA());
}


bool Fenetre::keyPressed()
{
	return !keys.empty();
}

const char Fenetre::getLastKey()
{

	if(keys.empty()) return *SDL_GetScancodeName(SDL_SCANCODE_0);

	const char * res =  SDL_GetScancodeName(keys.front());
	keys.pop();
	return *res;
}

Vec2 Fenetre::mousePos() const
{
	int x = 0,y = 0;
	SDL_GetMouseState(&x,&y);
	return Vec2(x,y);
}

void Fenetre::draw(const Terrain &t){

	rectangleRGBA(renderer,t.getPos().getX(),t.getPos().getY(),
				t.getPos().getX() + t.getWidth(),t.getPos().getY()+t.getHeight(),
				Couleur_c.getR(),Couleur_c.getG(),Couleur_c.getB(),Couleur_c.getA()
	);
}

void Fenetre::draw(const Mur &m){
	draw(Rectangle(m.getPos(),m.getWidth(),m.getHeight()));
}
void Fenetre::draw(Joueur &j){
	std::vector<Cercle> cercles = j.getTabCercle();
	for(int i=0;i<cercles.size();i++)
		draw(cercles[i]);
}
