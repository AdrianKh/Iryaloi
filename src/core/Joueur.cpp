#include "Joueur.h"

using namespace std;

Joueur::Joueur()
{
    init();
}

void Joueur::init()
{
    score = 0;
    cercles.resize(1);
    cercles[0] = Cercle(60, Vec2(rand() % 500, rand()%1000), Vec2(0.5, 2));
    cam = Camera(Rectangle(Vec2(0, 0), 1000, 600), &(cercles[0].getPosVec2()));
}

Joueur::Joueur(const Vec2 &pos, int r)
{
    //cercles.push_back(Cercle(r,pos));
    init();
    //setImage(lien);
}

void Joueur::deplacerJoueur(const Vec2 &direction)
{
    for (unsigned int i = 0; i < cercles.size(); i++)
    {
        cercles[i].bougerCercle(direction);
    }
}

void Joueur::moveUp()
{
    for (unsigned int i = 0; i < cercles.size(); i++)
        cercles[i].bougerCercle(Vec2(cercles[i].getPosX(), cercles[i].getPosY() - cercles[i].getRayon()));
}
void Joueur::moveDown()
{
    for (unsigned int i = 0; i < cercles.size(); i++)
        cercles[i].bougerCercle(Vec2(cercles[i].getPosX(), cercles[i].getPosY() + cercles[i].getRayon()));
}
void Joueur::moveRight()
{
    for (unsigned int i = 0; i < cercles.size(); i++)
        cercles[i].bougerCercle(Vec2(cercles[i].getPosX() + cercles[i].getRayon(), cercles[i].getPosY()));
}
void Joueur::moveLeft()
{
    for (unsigned int i = 0; i < cercles.size(); i++)
        cercles[i].bougerCercle(Vec2(cercles[i].getPosX() - cercles[i].getRayon(), cercles[i].getPosY()));
}
unsigned int Joueur::get_score() const
{
    return score;
}
void Joueur::add_score(unsigned int s)
{
    score += s;
}

void Joueur::collision(const Terrain &t)
{
    for (unsigned int i = 0; i < cercles.size(); i++)
        t.collision(cercles[i]);
}
void Joueur::collision(const Mur &m)
{
    for (unsigned int i = 0; i < cercles.size(); i++)
        m.collision(cercles[i]);
}

bool Joueur::actionCercle(Cercle &c)
{
    for (unsigned int i = 0; i < cercles.size(); i++)
    {
        if (cercles[i].estDans(c))
        {
            add_score(1);
            cercles[i].mangeCercle(c);
            return true;
        }
    }
    return false;
}

std::vector<Cercle> &Joueur::getTabCercle()
{
    return cercles;
}

void Joueur::sauver(int fd) const
{
    string tmp = "";
    tmp += to_string(cercles.size()) + '\n';
    save(tmp, fd);
    for (unsigned int i = 0; i < cercles.size(); i++)
    {
        cercles[i].sauver(fd);
    }
}

void Joueur::charger(int fd)
{
    string tmp = "";
    tmp += read_line(fd);
    unsigned int size = stoul(tmp);
    cercles.resize(size);
    for (unsigned i = 0; i < size; i++)
    {
        cercles[i].charger(fd);
    }
    update_cam();
}
void Joueur::diviser()
{
    unsigned int size = cercles.size();
    std::vector<Cercle> tmp_cercles;
    Cercle tmp;
    unsigned int i = 0;
    while (i < size)
    {
        if (cercles[i].r < 30)
            tmp_cercles.push_back(cercles[i]);
        else
        {
            tmp = cercles[i] / 2;
            tmp_cercles.push_back(tmp);
            tmp = Cercle(tmp.getPos().x + tmp.r + 20, tmp.getPos().y, tmp.r);
            tmp_cercles.push_back(tmp);
        }
        i++;
    }
    if (tmp_cercles.size() <= size)
        return;
    i = 0;
    while (i < size)
    {
        cercles[i] = tmp_cercles[i];
        i++;
    }
    while (i < tmp_cercles.size())
    {
        cercles.push_back(tmp_cercles[i]);
        i++;
    }
    cam = Camera(Rectangle(Vec2(0, 0), cam.getWidth(), cam.getHeight()), &(cercles[0].getPosVec2()));
    cout << "divise" << endl;
}

void Joueur::collision_entre_cercles()
{
    for (unsigned int i = 0; i < cercles.size(); i++)
    {
        for (unsigned int j = i + 1; j < cercles.size(); j++)
        {
            if (cercles[i].collision(cercles[j]))
            {
                /** le calcule non optimisé
                Vec2 tmp = cercles[i].getPos() - cercles[j].getPos();
                tmp = tmp.normalise();
                tmp = cercles[j].getPos() + tmp * 2*cercles[i].r;
                cercles[i].setPosVec2(tmp)*/
                // le calcule plus optimisé
                cercles[i].setPosVec2(cercles[j].getPos() +
                                      (cercles[i].getPos() - cercles[j].getPos()).normalise() * 2 * cercles[j].r);
            }
        }
    }
}

void Joueur::fussionner()
{
    unsigned int i = 0;
    unsigned int size = cercles.size();
    vector<Cercle> tmp_cercle;
    bool recopie = false;
    while (i + 1 < size)
    {
        tmp_cercle.push_back(cercles[i] + cercles[i + 1]);
        i +=2;
        recopie = true;
    }
    if(recopie)
    {

        for(i=0; i<tmp_cercle.size(); i++)
            cercles[i] = tmp_cercle[i];
        for(i=tmp_cercle.size();  i<=cercles.size(); i++)
            cercles.pop_back();
        cout << "fusion" << endl;
        update_cam();
    }
}

void Joueur::actionJoueur(Joueur & j){
    vector<Cercle> &tmp = j.getTabCercle();
    for(unsigned int i=0; i<tmp.size(); i++)
        actionCercle(tmp[i]);
}

bool Joueur::all_zero(int & n)
{
    if(cercles.size() == 0)
        return true;
    unsigned int i = 0;
    while(i<cercles.size())
    {
        if(cercles[i].r > 5)
        {
            n = i;
            return false;
        }
        i++;
    }
    return true;
}
void Joueur::update_cam()
{
    int n;
    if(all_zero(n))
        cam = Camera(Rectangle(Vec2(0, 0), cam.getWidth(), cam.getHeight()), &tmp_cam);
    else
       cam = Camera(Rectangle(Vec2(0, 0), cam.getWidth(), cam.getHeight()), &(cercles[n].getPosVec2()));
}