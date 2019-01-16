#include "Jeu.h"

#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */

#include "tools.h"
#include "socklib.hpp"

using namespace std;
using namespace socklib;

Jeu::Jeu()
{
    fd_file = -1;
}

Jeu::~Jeu()
{
    if(fd_file != -1)
        close(fd_file);
}


void Jeu::init_imgs()
{
    j.setImage("data/img/bangladesh_flag1.png");
    setImageTerrain("data/img/black.jpg");
    setImageMur("data/img/wall3.png");
    setImgPtCercle("data/img/tomato.png");
}

void Jeu::init()
{
    
    init_imgs();
    t = Terrain(Vec2(0,0), 3000, 3000);

    unsigned char nbMurs = rand() % t.getWidth() / 50;
    murs.resize((unsigned int)nbMurs);
    for (char i = 0; i < nbMurs; i++)
        murs[i] = murs[i].genereMurAlea(t.getPos(), t.getWidth(), t.getHeight());

    unsigned int nbCercles = rand() % t.getWidth() / 20 + 10;
    petitCercles.resize((unsigned int)nbCercles);
    for (unsigned int i = 0; i < nbCercles; i++)
        petitCercles[i] = petitCercles[i].genCercleAlea(t.getPos(), t.getWidth(), t.getHeight());
    cout<<"Jeu initialisé avec succes\n";
}


void Jeu::update()
{
    if(etatDeJeu == JeuMulti)
    {
        if(r.flip_trun())
        {
            sauver(r.get_connection());

        }else{
            charger(r.get_connection());
        }
        j.actionJoueur(j2);
        int n;
        // fin de jeu et échèque
        if(j.all_zero(n))
        {
            cout<<"Vous avez perdu\n";
            exit(EXIT_SUCCESS);
        }
        // le joueur a gagné
        if(j2.all_zero(n))
        {
            cout<<"Vous avez gagné\n";
            send_close(r.get_connection());
            exit(EXIT_SUCCESS);
        }
    }
    else if(etatDeJeu == jeuUnNiveau)
    {
        for(unsigned int i=0; i<point_arrive.size(); i++)
        {
            for(unsigned int k=0; k<j.getTabCercle().size(); k++)
            {
                if(point_arrive[i].collision(j.getTabCercle()[k]))
                {
                    cout<<"bravo vous avez ternimer le niveau"<<endl;
                    v_niveau++;
                    if(v_niveau > v_last_niveau)
                    {
                        cout<<"Bravo vous avez terminé tous les niveau"<<endl;
                        exit(EXIT_SUCCESS);
                    }
                    init(etatDeJeu,v_niveau);
                }
            }
        }
    }
    j.collision_entre_cercles();
    j.collision(t);
    for (unsigned int i = 0; i < petitCercles.size(); i++)
    {
        if (j.actionCercle(petitCercles[i]))
            petitCercles[i] = petitCercles[i].genCercleAlea(t.getPos(), t.getWidth(), t.getHeight());
    }

    for (unsigned int i = 0; i < murs.size(); i++)
    {
        j.collision(murs[i]);
    }
}

void Jeu::init(const etat e, unsigned int niveau)
{
    etatDeJeu = e;
if (e == jeuLibre)
    {
        
        init();
    }
else if (e == JeuMulti)
    {
        
        init();
        r.init();
     if(r.is_server())
        {
            sauver(r.get_connection(),true);

        }else{

            charger(r.get_connection(),true);
        }
    }
else if(e == jeuUnNiveau)
    {
        init_imgs();
        v_niveau = niveau;
        cout<<"niveau "<<v_niveau<<endl;
        init_fd_niveau(v_niveau,'b');
        charger(fd_file,true);
        cout<<"chargement succes\n";
        last_niveau();
    }
}

std::string Jeu::getImageTerrain() const
{
    return imgTerrain.get_lien();
}
void Jeu::setImageTerrain(const std::string &s)
{
    imgTerrain.set_lien(s);
}

Terrain &Jeu::getTerrain()
{
    return t;
}
Joueur &Jeu::getJoueur()
{
    return j;
}
Joueur &Jeu::getJoueur2()
{
    return j2;
}
std::vector<Cercle> &Jeu::getPtitCercles()
{
    return petitCercles;
}
std::vector<Mur> &Jeu::getMurs()
{
    return murs;
}

std::string Jeu::getImageMur() const
{
    return imgMurs.get_lien();
}
void Jeu::setImageMur(const std::string &s)
{
    imgMurs.set_lien(s);
}
std::string Jeu::getImgPtCercle() const
{
    return imgPtCercle.get_lien();
}
void Jeu::setImgPtCercle(const std::string &s)
{
    imgPtCercle.set_lien(s);
}

etat Jeu::getEtatDeJeu() const
{
    return etatDeJeu;
}

void Jeu::change_etat(const etat e)
{
    etatDeJeu = e;
}

void Jeu::sauver(int fd, bool init) const
{
    // enregistrement du terrain
    if(init)
        t.sauver(fd);
    // enregistrement des murs
    // le nombre de murs
    string tmp = "";
    if(init)
    {

        tmp += to_string(murs.size()) + '\n';
        save(tmp, fd);
        for (unsigned int i = 0; i < murs.size(); i++)
            murs[i].sauver(fd);
    }
    // enregistrement des petits cercles
    // le nombre de cercles
    tmp.clear();
    tmp += to_string(petitCercles.size()) + '\n';
    save(tmp, fd);
    for (unsigned int i = 0; i < petitCercles.size(); i++)
        petitCercles[i].sauver(fd);
    // enregistrement du joueur
    j.sauver(fd);
    if(etatDeJeu == JeuMulti)
        j2.sauver(fd);
    // enregistrement des point d'arrivé
    if(etatDeJeu == jeuUnNiveau)
    {
        tmp += to_string(point_arrive.size()) + '\n';
        save(tmp, fd);
        for (unsigned int i = 0; i < point_arrive.size(); i++)
            point_arrive[i].sauver(fd);
    }
}

void Jeu::charger(int fd, bool init)
{
    // chergement du terrain
    if(init)
        t.charger(fd);
    // chargement des murs
    // le nombre de murs
    string tmp = "";
    unsigned int taille;
    if(init)
    {
        tmp += read_line(fd);
        taille = stoul(tmp);
        if (taille != murs.size())
            murs.resize(taille);
        for (unsigned int i = 0; i < taille; i++)
            murs[i].charger(fd);
    }
    // chargement des petits cercle
    tmp.clear();
    tmp += read_line(fd);
    verif_reciv(tmp);
    taille = stoul(tmp);
    if (taille != petitCercles.size())
        petitCercles.resize(taille);
    for (unsigned int i = 0; i < taille; i++)
        petitCercles[i].charger(fd);
    // chargement de l'autre joueur
    if(etatDeJeu == JeuMulti)
    {
        j2.charger(fd);
        j.charger(fd);
        j.update_cam();
    }
    else 
        j.charger(fd);
    // chargement des point d'arrivé
    if(etatDeJeu == jeuUnNiveau)
    {
        tmp.clear();
        tmp += read_line(fd);
        taille = stoul(tmp);
        if (taille != point_arrive.size())
            point_arrive.resize(taille);
        for (unsigned int i = 0; i < taille; i++)
            point_arrive[i].charger(fd);
    }
}
void Jeu::init_fd_niveau(int n_niveau,char mode)
{
    string niveau ="";
    niveau += "data/niveaux/" + to_string(n_niveau);
    if(!Image(niveau).valide())
    {
        cerr<<"le niveau n'est pas valide\n";
        exit(EXIT_FAILURE);
    }
    if(mode == 'b')
    {
        fd_file = open(niveau.c_str(),O_RDWR);
        cout<<niveau<<endl;
    }

}

void Jeu::last_niveau(){
    int tmp = open("data/niveaux/last",O_RDONLY);
    string tmp_s = "";
    tmp_s += read_line(tmp);
    v_last_niveau = stoul(tmp_s);
    close(tmp);
}