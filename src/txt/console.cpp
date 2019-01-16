#include "console.h"
using namespace std;

void console::initTerrain(){
    ter=Terrain(Vec2(0,0),dimx,dimy);
}

console::console(unsigned int dimx, unsigned int dimy){
    this->dimx = dimx;
    this->dimy = dimy;
    initTerrain();
    grille = new char[dimx*dimy];
    initGrille();
}

Terrain & console::getTerrain(){
    return ter;
}

void console::initGrille()
{
    viderConsole();
}

console::~console()
{
    delete[] grille;
    grille = NULL;
}

char console::getValeur(unsigned int x, unsigned int y) const
{
    return grille[y*dimx + x];
}

void console::setVal(unsigned int x, unsigned int y, char val)
{
    if(x<dimx && y<dimy)
    {
        grille[y*dimx + x] = val;
    }
}

void console::afficheConsole()const{
    cout<<endl;
    for (unsigned int j=0; j<dimy; j++){
        for (unsigned int i=0; i<dimx; i++){
            cout<<getValeur(i,j);
        }
        cout<<endl;
    }
}
void console::effaceConsole(){
    system("clear");
}

void console::viderConsole(){
    for (unsigned int j=0; j<dimy; j++){
        for (unsigned int i=0; i<dimx; i++){
            setVal(i,j,' ');
        }
    }
}

void console::dessineRectangle(int x0, int y0, int h , int w){
    for (int i=y0; i<h+y0; i+=h-1){
        for (int j=x0; j<w+x0; j++){
            setVal(i,j,'#');
        }
    }

    for (int i=y0; i<h+y0; i++){
        for (int j=x0; j<w+x0; j+=w-1){
            setVal(i,j,'#');
        }
    }
    
}

void console::dessineRectangle(const Rectangle & rec){
     dessineRectangle(rec.getPos().getX(), rec.getPos().getY(), rec.getHeight(), rec.getWidth());
}

void console::dessineCercle(unsigned int x0,unsigned int y0, unsigned int radius) 
{
    int x = radius-2;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);

    while (x >= y)
    {
        setVal(x0 + x, y0 + y,'*');
        setVal(x0 + y, y0 + x,'*');
        setVal(x0 - y, y0 + x,'*');
        setVal(x0 - x, y0 + y,'*');
        setVal(x0 - x, y0 - y,'*');
        setVal(x0 - y, y0 - x,'*');
        setVal(x0 + y, y0 - x,'*');
        setVal(x0 + x, y0 - y,'*');

        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }
        
        if (err > 0)
        {
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }
}

void console::dessineCercle(const Cercle & cer){
    dessineCercle(cer.getPosX(), cer.getPosY(), cer.getRayon());
}

void console::dessineTabrec(const std::vector<Rectangle>& v){
    for (unsigned int i=0; i<v.size(); i++){
       dessineRectangle(v[i]);  
    }
}

void console::initTabcer(std::vector <Cercle> & cer,const Cercle & c, int indice ){
    cer[indice]=c;
}

void console::dessineTabcer(const std::vector<Cercle> & cer){
     for (int i=0; i<2; i++ ){
        dessineCercle(cer[i]); 
        }

}