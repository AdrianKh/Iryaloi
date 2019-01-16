#include "Mur.h"


#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


// collision parfait
void Mur::collision(Cercle & c) const{
    Vec2 pos_obj = c.getPos();
    Vec2 pos_tmp;
    bool dans_rect_en_y = pos_obj.y > pos.y && pos_obj.y < pos.y+h;
    bool dans_rect_en_x = pos_obj.x > pos.x && pos_obj.x < pos.x+w;
    bool pas_dans_xy = !dans_rect_en_y && !dans_rect_en_x;

    Vec2 les_coins_de_rect[4] = {
        // coin haut-gauche
        pos,
        // coin bas-gauche
        Vec2(pos.x,pos.y+h),
        // coin bas-droite
        Vec2(pos.x+w,pos.y+h),
        // coin haut-droite
        Vec2(pos.x+w,pos.y)
    };
    int i = 0;
    while(i<4)
    {
        if(les_coins_de_rect[i].distance(pos_obj)<c.r && pas_dans_xy){
            Vec2 delta = pos_obj - les_coins_de_rect[i];
            delta = delta.normalise();
            c.setPosVec2(les_coins_de_rect[i] + delta*c.r);
            return;
        }
        i++;
    }
    Vec2 les_cote_de_rect[4] = {
        // cote gauche
        Vec2(pos.x,pos_obj.y),
        // cote droite
        Vec2(pos.x+w,pos_obj.y),
        // cote bas
        Vec2(pos_obj.x,pos.y+h),
        // cote haut
        Vec2(pos_obj.x,pos.y)
    };
    i = 0;
    // cote droite et gauche
    while(i<2)
    {
        if(les_cote_de_rect[i].distance(pos_obj)<c.r && dans_rect_en_y){
            Vec2 delta = pos_obj - les_cote_de_rect[i];
            delta = delta.normalise();
            c.setPosVec2(les_cote_de_rect[i] + delta*c.r);
            return;
        }
        i++;
    }
    // cota haut et bas
    while(i<4)
    {
        if(les_cote_de_rect[i].distance(pos_obj)<c.r && dans_rect_en_x){
            Vec2 delta = pos_obj - les_cote_de_rect[i];
            delta = delta.normalise();
            c.setPosVec2(les_cote_de_rect[i] + delta*c.r);
            return;
        }
        i++;
    }
}

Mur Mur::genereMurAlea(const Vec2 & pos, unsigned int w ,unsigned int h ) const{
    int posX, posY;
    unsigned int tmpW,tmpH;
    tmpW = (rand() % 200 )+ 70;
    tmpH = (rand() % 200 )+ 70;
    posX = rand() % (w - tmpW) + pos.getX();
    posY = rand() % (h - tmpH) + pos.getY();
    return Mur(Vec2(posX,posY),tmpW,tmpH);
}