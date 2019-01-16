#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Fenetre.h"

const unsigned int WIDTH = 640 ;
const unsigned int HEIGHT = 480;

using namespace std; 

void test0();
void test1();
void test2();
void testDessineRect();
void testCercle();
void testCercleBouger();
void testCercleBougerMouse();
void bougeCercle(Cercle &c,const Vec2 &dir);

int main(int argc, char* argv[])
{
      srand(time(NULL));
      testCercleBougerMouse();
      return 0;
}


void initC(Cercle &c)
{
      c = Cercle(10,Vec2(50,50));
}

void testCercleBougerMouse()
{
      Fenetre win("Iryal.io Cercle",WIDTH,HEIGHT);
      Couleur col;
      col.genCouleurAleatoire();
      win.Couleur(col);
      Uint32 tempsCalcule;
      Cercle c(100,Vec2(50,50));
      Rectangle r(Vec2(50,0), 50,50);
      Vec2 origine = Vec2(100,100);
      win.setOrigine(&origine);

      while(!win.estFerme())
      {
            tempsCalcule = SDL_GetTicks();
            win.gererEvenement();
            win.clear();
            bougeCercle(c,win.mousePos());
            win.draw(c);
            win.draw(r);
            win.afficheRender();
            win.fps(30,SDL_GetTicks()-tempsCalcule);
      }
}
void bougeCercle(Cercle &c,const Vec2 &dir)
{
      Vec2 &posC = c.getPosVec2();

      if(dir.distance(posC) > 5)
      {
            Vec2 direction = dir - posC;
            direction = direction.normalise();
            posC += direction * c.getAire()*0.00009f;
      }
}
void updateCercle(Cercle &c,const char key)
{
      float k = 5;
      switch(key)
      {
            case 'U':
            {
                  c.getPosVec2() += Vec2(0,-1)*k;
                  break;
            }
            case 'D':
            {
                  c.getPosVec2() += Vec2(0,1)*k;
                  break;
            }
            case 'L':
            {
                  c.getPosVec2() += Vec2(-1,0)*k;
                  break;
            }
            case 'R':
            {
                  c.getPosVec2() += Vec2(1,0)*k;
                  break;
            }
            default: break;
      }
}

void testCercleBouger()
{
      Fenetre win("Iryal.io Cercle",WIDTH,HEIGHT);
      Couleur col;
      col.genCouleurAleatoire();
      win.Couleur(col);
      Uint32 tempsCalcule;
      Cercle c(100,Vec2(50,50));
      while(!win.estFerme())
      {
            tempsCalcule = SDL_GetTicks();
            win.gererEvenement();
            win.clear();
            if(win.keyPressed())
            {
                  updateCercle(c,win.getLastKey());
            }
            win.draw(c);
            win.afficheRender();
            win.fps(40,SDL_GetTicks()-tempsCalcule);
      }
}


void testCercle()
{
      Fenetre win("Iryal.io Cercle",WIDTH,HEIGHT);
      win.Couleur(Couleur(255,0,0,255));
      Uint32 tempsCalcule;
      Cercle c(10,Vec2(50,50));
      while(!win.estFerme())
      {
            tempsCalcule = SDL_GetTicks();
            win.gererEvenement();
            win.clear();
            win.draw(c);
            win.afficheRender();
            win.fps(30,SDL_GetTicks()-tempsCalcule);
      }
}


void test2()
{
      Fenetre win("Iryal.io Test1",WIDTH,HEIGHT);
      Uint32 tempsCalcule;
      while(!win.estFerme())
      {
            tempsCalcule = SDL_GetTicks();
            win.gererEvenement();
            win.clear();
            win.afficheRender();
            win.fps(30,SDL_GetTicks()-tempsCalcule);
      }
}

void test1()
{
      Fenetre win("Iryal.io test1",WIDTH,HEIGHT);
      SDL_Event evt;
      bool quit = false;
      while(!quit)
      {
            while(SDL_PollEvent(&evt))
            {
                  if(evt.type == SDL_QUIT)
                        quit = true;
            }
            win.clear();
            win.afficheRender();
            SDL_Delay(1000/30);
      }

}

void testDessineRect()
{
      Fenetre win("Iryal.io Test1",WIDTH,HEIGHT);
      win.Couleur(Couleur(255,0,0,255));
      Rectangle r(Vec2(10,10),200,100);
      Uint32 tempsCalcule;
      while(!win.estFerme())
      {
            tempsCalcule = SDL_GetTicks();
            win.gererEvenement();
            win.clear();
            win.afficheRectangle(r);
            win.afficheRender();
            win.fps(30,SDL_GetTicks()-tempsCalcule);
      }
}

void test0()
{
   SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
   SDL_Window *window = SDL_CreateWindow("Test0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
   SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
   SDL_Surface * image = IMG_Load("../data/map.jpg");
   if(!image) image = IMG_Load("data/map.jpg");
   SDL_Texture * imageTex = SDL_CreateTextureFromSurface(renderer,image);
   //SDL_GL_GetDrawableSize(window,&WIDTH,&HEIGHT);
   SDL_Rect camera;
   camera.x = 0; camera.y = 0;
   camera.h = HEIGHT; camera.w = WIDTH;
   SDL_FreeSurface(image);


   SDL_Event e;

   bool quit = false;
   while (!quit)
   {
      while(SDL_PollEvent(&e))
      {
         if(e.type == SDL_QUIT)
            quit = true;

         else
         {
            switch(e.key.keysym.scancode)
            {
                  case SDL_SCANCODE_UP:
                        if(camera.y>0)camera.y -= 3;
                  break;
                  case SDL_SCANCODE_DOWN:
                        cout<<camera.y<<endl;
                        if(camera.y<240) camera.y+=3;
                  break;
                  case 'L':
                       if(camera.x>0) camera.x-=3;
                  break;
                  case SDL_SCANCODE_RIGHT:
                        if(camera.x<400) camera.x+=3;
                  break;
                  default: break;
            }
         }
      }
      SDL_SetRenderDrawCouleur(renderer,255,255,255,255);
      SDL_RenderClear(renderer);
      SDL_RenderCopy(renderer,imageTex,&camera,NULL);
      //filledCircleRGBA(renderer,WIDTH/2,HEIGHT/2,100,0,255,0,255);
      //filledCircleRGBA(renderer,WIDTH/4,HEIGHT/4,100,255,0,0,255);
      SDL_RenderPresent(renderer);
      SDL_Delay(1000/50);
   }

   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   SDL_Quit();
}
