#include "Iryal_io.h"

using namespace std;

// jeuLibre = 1, dansLeMenu = 2, quitter = 3, jeuUnNiveau = 4, JeuMulti = 5
etat get_etat_from_int(int e);

void Iryal_io::init()
{
    etat mode_jeu;
    int tmp = 1;
    do{
        cout<<"choissiez un mode de jeu\n";
        cout<<"jeuLibre = 1, dansLeMenu = 2, quitter = 3, jeuUnNiveau = 4, JeuMulti = 5\n mode : ";
        cin>>tmp;
        mode_jeu = get_etat_from_int(tmp);
    }while(mode_jeu == dansLeMenu);
    bool etat_valide_du_jeu = mode_jeu == jeuLibre || mode_jeu == JeuMulti || mode_jeu == jeuUnNiveau;
    unsigned int n_niveau = 1;
    if(mode_jeu == jeuUnNiveau)
    {
        cout<<" Niveau : ";
        cin>>n_niveau;
        win.set_bg_music("data/audio/" + to_string(n_niveau) + ".ogg");
    }
    else if(mode_jeu == quitter)
    {
        exit(EXIT_SUCCESS);
    }
    else{
        win.bg_auto();
    }
    if(etat_valide_du_jeu)
    {        
        j.init(mode_jeu,n_niveau);
        win.init("Iryal.io", 1000, 600);
        win.setView(&j.getJoueur().getCam());

    }
}
void Iryal_io::run()
{
    cout<<"Jeu en execution"<<endl;
    while (win.isOpen())
    {
        win.gererEvenement();
        win.clear(sf::Color(125,125,125));
        win.updateView();

        if (win.spacePressed())
        {
            cout<<"space\n";
            j.getJoueur().diviser();
        }
        else if(win.pressed_f())
        {
            cout<<"f\n";
            j.getJoueur().fussionner();

        }
        j.getJoueur().deplacerJoueur(win.getMousePos());
        j.update();

        win.draw(j);
        win.display();
    }
}

etat get_etat_from_int(int e){
    switch(e)
    {
        case 1: return jeuLibre;
        case 2: return dansLeMenu;
        case 3: return quitter;
        case 4: return jeuUnNiveau;
        case 5: return JeuMulti;
        default: return jeuLibre;
    }
}