#include "FenetreSFML.h"

#include <vector>
#include <dirent.h>
#include <sys/types.h>

using namespace sf;
using namespace std;

FenetreSFML::FenetreSFML()
{
    _w = 0;
    _h = 0;
    open = false;
}

FenetreSFML::FenetreSFML(const string &name, const unsigned int w, const unsigned int h)
{
    init(name, w, h);
}

FenetreSFML::~FenetreSFML()
{
    if (texJoueur)
        delete texJoueur;
    texJoueur = nullptr;
    if (texMurs)
        delete texMurs;
    texMurs = nullptr;
    if (texTerrain)
        delete texTerrain;
    texTerrain = nullptr;
    if (texPtCercle)
        delete texPtCercle;
    if (texMenu)
        delete texMenu;
    texPtCercle = nullptr;
    win.close();
    cerr << "Destrction de la fenetre" << endl;
}

void FenetreSFML::init(const string &name, const unsigned int w, const unsigned int h)
{
    _w = w;
    _h = h;
    open = true;
    space = false;
    mouse = false;
    key_f = false;
    bg_num = 1;
    next_bg = 1;
    init_max_track();
    cam = NULL;
    viewport = View(sf::FloatRect(0, 0, _w, _h));
    settings.antialiasingLevel = 8;
    win.create(VideoMode(_w, _h), name, Style::Close | Style::Resize, settings);
    win.setFramerateLimit(40);
    win.setView(viewport);
    initShapes();
    cerr << "Ceation de fenetre : " << name << endl;
}
RenderWindow &FenetreSFML::getWin()
{
    return win;
}
void FenetreSFML::fps(unsigned char fps)
{
    win.setFramerateLimit(fps);
}

bool FenetreSFML::isOpen()
{
    return open;
}

void FenetreSFML::gererEvenement()
{

    while (win.pollEvent(evt))
    {

        if (evt.type == Event::Closed)
        {
            open = false;
            break;
        }
        else if (evt.type == sf::Event::Resized)
        {
            _w = evt.size.width;
            _h = evt.size.height;
            win.setSize(Vector2u(_w, _h));
            if (cam)
            {
                viewport = View(sf::FloatRect(cam->getCamPos().x, cam->getCamPos().y, _w, _h));
                cam->setWidth(_w);
                cam->setHeight(_h);
            }
            else
            {
                viewport = View(sf::FloatRect(0, 0, _w, _h));
            }
            win.setView(viewport);
        }
        else if (evt.type == sf::Event::KeyPressed)
        {
            if (evt.key.code == sf::Keyboard::Escape)
            {
                open = false;
                break;
            }
            else if (evt.key.code == sf::Keyboard::Space)
                space = true;
            else if (evt.key.code == sf::Keyboard::Up)
                volume_up();
            else if (evt.key.code == sf::Keyboard::Down)
                volume_down();
            else if(evt.key.code == sf::Keyboard::F)
                key_f = true;
            else if (evt.key.code == sf::Keyboard::Left)
            {
                next_bg = -1;
                play_next();
            }
            else if (evt.key.code == sf::Keyboard::Right)
            {
                next_bg = 1;
                play_next();
            }
        }
        else if (evt.type == Event::MouseMoved)
        {
            Vector2i res = Mouse::getPosition(win);
            mousePos = Vec2(res.x, res.y);
        }
        else if (evt.type == sf::Event::MouseButtonPressed)
        {
            if (evt.mouseButton.button == sf::Mouse::Left)
                mouse = true;
        }
    }

    if (bg_is_finished())
    {
        next_bg = 1;
        play_next();
    }
}

void FenetreSFML::display()
{
    win.display();
}

void FenetreSFML::getMousePos(int &x, int &y) const
{
    x = mousePos.x;
    y = mousePos.y;
}

void FenetreSFML::updateView()
{
    viewport = View(sf::FloatRect(cam->getCamPos().x, cam->getCamPos().y, cam->getWidth(), cam->getHeight()));
    win.setView(viewport);
}
Vec2 FenetreSFML::getMousePos() const
{
    return mousePos + cam->getCamPos();
}

void FenetreSFML::clear(Color c)
{
    win.clear(c);
}

void FenetreSFML::initShapes()
{
    font.loadFromFile("data/txt/arial.ttf");
    text.setFont(font);
    text.setCharacterSize(30);
    text.setColor(sf::Color::Red);
    cercle = CircleShape(0);
    rectangle = RectangleShape(sf::Vector2f(0, 0));
    //tmpTexture.loadFromFile(Default());
    if (!textRec.loadFromFile("./data/img/wall3.png"))
    {
        cout << "error";
    }
    else
    {
        textRec.setSmooth(true);
        textRec.setRepeated(true);
    }
    if (!textCer.loadFromFile("./data/pikachu.png"))
    {
        cout << "error";
    }
    else
        textCer.setSmooth(true);

    texMenu = NULL;
    texMurs = NULL;
    texJoueur = NULL;
    texTerrain = NULL;
    texPtCercle = NULL;
}

void FenetreSFML::draw(const Cercle &c)
{
    cercle.setRadius(c.getRayon());
    cercle.setPosition(c.getPosX() - c.getRayon(), c.getPosY() - c.getRayon());
    //cercle.setFillColor(sf::Color(100, 250, 50));
    //cercle.setTexture(&textCer);
    win.draw(cercle);
}

void FenetreSFML::draw(const Rectangle &r)
{
    rectangle.setSize(sf::Vector2f(r.getWidth(), r.getHeight()));
    rectangle.setPosition(r.getPos().getX(), r.getPos().getY());
    //rectangle.setFillColor(sf::Color(100, 250, 50));
    //rectangle.setTexture(&textRec);
    win.draw(rectangle);
}

void FenetreSFML::draw(const Camera &t)
{
    /*// cote gauche
    draw(Rectangle(t.getCamPos()-5,5,t.getHeight()+5));
    // cote droite
    draw(Rectangle(
        Vec2(t.getCamPos().x+t.getWidth(),t.getCamPos().y),
        5,t.getHeight()));
    // cote haut
    draw(Rectangle(t.getCamPos(),t.getWidth()+5,5));
    // cote bas
    draw(Rectangle(
        Vec2(t.getCamPos().x,t.getCamPos().y+t.getHeight()),
        t.getWidth()+5,5));*/
}

void FenetreSFML::setView(Camera *c)
{
    //viewport = View(sf::FloatRect( c.getCamPos().x, c.getCamPos().y, c.getWidth(), c.getHeight()));
    //win.setView(viewport);
    cam = c;
}

void FenetreSFML::draw(const Mur &m)
{
    draw(Rectangle(m.getPos(), m.getWidth(), m.getHeight()));
}
void FenetreSFML::draw(const Terrain &t)
{
    // cote gauche
    draw(Rectangle(t.getPos() - 5, 5, t.getHeight() + 5));
    // cote droite
    draw(Rectangle(
        Vec2(t.getPos().getX() + t.getWidth(), t.getPos().getY()),
        5, t.getHeight()));
    // cote haut
    draw(Rectangle(Vec2(t.getPos().x - 5, t.getPos().y - 5), t.getWidth() + 10, 5));
    // cote bas
    draw(Rectangle(
        Vec2(t.getPos().getX(), t.getPos().getY() + t.getHeight()),
        t.getWidth() + 5, 5));
}
void FenetreSFML::draw(Joueur &j, bool j_actuelle)
{

    if (texJoueur == nullptr)
    {
        texJoueur = new Texture;
        texJoueur->loadFromFile(j.getImage());
        texJoueur->setSmooth(true);
    }
    std::vector<Cercle> cercles = j.getTabCercle();
    cercle.setTexture(texJoueur, true);
    for (unsigned int i = 0; i < cercles.size(); i++)
        draw(cercles[i]);
    cercle.setTexture(nullptr);
    // affichage du text
    if (j_actuelle)
    {
        text.setString("Score : " + to_string(j.get_score()));
        text.setPosition(cam->getCamCercle()->x + cam->getWidth() / 2 - 200, cam->getCamCercle()->y - cam->getHeight() / 2);
        win.draw(text);
    }
}

void FenetreSFML::draw(Jeu &j)
{

    if (texTerrain == NULL)
    {
        texTerrain = new Texture;
        if (texTerrain->loadFromFile(j.getImageTerrain()))
            cout << "Loaded " << j.getImageTerrain() << endl;
        texTerrain->setSmooth(true);
    }
    rectangle.setTexture(NULL);
    //rectangle.setTexture(&textRec);
    rectangle.setTexture(texTerrain, true);
    draw(j.getTerrain());
    rectangle.setTexture(NULL);

    if (texPtCercle == NULL)
    {
        texPtCercle = new Texture;
        texPtCercle->loadFromFile(j.getImgPtCercle());
    }
    cercle.setTexture(texPtCercle, true);
    std::vector<Cercle> &cercles = j.getPtitCercles();
    for (unsigned int i = 0; i < cercles.size(); i++)
        //if (j.getJoueur().getCam().estDansLaCamera(cercles[i]))
        draw(cercles[i]);
    cercle.setTexture(NULL);

    if (texMurs == NULL)
    {
        texMurs = new Texture;
        if (texMurs->loadFromFile(j.getImageMur()))
            cout << "Loaded " << j.getImageMur() << endl;
    }
    std::vector<Mur> &murs = j.getMurs();
    rectangle.setTexture(texMurs, true);
    for (unsigned int i = 0; i < murs.size(); i++)
        //if (j.getJoueur().getCam().estDansLaCamera(murs[i]))
        draw(murs[i]);
    rectangle.setTexture(NULL);
    draw(j.getJoueur());
    if (j.getEtatDeJeu() == JeuMulti)
        draw(j.getJoueur2(), false);
    if (j.getEtatDeJeu() == jeuUnNiveau)
    {
        std::vector<Cercle> &tmp = j.get_point_arrive();
        for (unsigned int i = 0; i < tmp.size(); i++)
            draw(tmp[i]);
    }
}

/**
 * ex: 
 * Z = UP
 * S = DOWN
 * Q = LEFT
 * D = RIGHT
*/
bool FenetreSFML::isKeyPressed(char key)
{
    /*if(!win.pollEvent(evt))
        return false;*/

    switch (key)
    {
    case 'Z':
        return sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
    case 'S':
        return sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    case 'Q':
        return sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
    case 'D':
        return sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    default:
        return false;
    }
}
bool FenetreSFML::isKeyPressed(std::string &key)
{
    if (!win.pollEvent(evt))
        return false;

    if (key == "UP")
        return sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    if (key == "DOWN")
        return sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
    if (key == "LEFT")
        return sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    if (key == "RIGHT")
        return sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

    return false;
}

bool FenetreSFML::spacePressed()
{
    bool tmp = space;
    space = false;
    return tmp;
}

void FenetreSFML::draw(const Case &c)
{
    text.setString(c.getContenu());
    text.setPosition(c.getPos().x, c.getPos().y);
    win.draw(text);
}
void FenetreSFML::draw(Menu &m)
{
    vector<Case> tmp;
    tmp = m.get_home();
    if (!texMenu)
    {
        texMenu = new Texture;
        texMenu->loadFromFile("data/img/black.jpg");
    }
    rectangle.setTexture(texMenu, true);
    for (unsigned int i = 0; i < tmp.size(); i++)
    {
        // cote gauche
        draw(Rectangle(tmp[i].getPos() - 5, 5, tmp[i].getHeight() + 5));
        // cote droite
        draw(Rectangle(
            Vec2(tmp[i].getPos().x + tmp[i].getWidth(), tmp[i].getPos().y),
            5, tmp[i].getHeight()));
        // cote haut
        draw(Rectangle(Vec2(tmp[i].getPos().x - 5, tmp[i].getPos().y - 5), tmp[i].getWidth() + 10, 5));
        // cote bas
        draw(Rectangle(
            Vec2(tmp[i].getPos().x, tmp[i].getPos().getY() + tmp[i].getHeight()),
            tmp[i].getWidth() + 5, 5));

        draw(tmp[i]);
    }
    rectangle.setTexture(NULL);
}

bool FenetreSFML::mousePressed()
{
    bool tmp = mouse;
    mouse = false;
    return tmp;
}
void FenetreSFML::set_bg_music(const std::string &chemin)
{
    if (bg_music.openFromFile(chemin))
        cout << "audio : " << chemin << endl;
    else
    {
    }
    bg_music.setLoop(true);
    bg_music.setVolume(50);
    bg_music.play();
}
void FenetreSFML::stop_bg_music()
{
    bg_music.stop();
}
void FenetreSFML::bg_auto()
{
    bg_num = 1;
    set_bg_music("data/audio/" + to_string(bg_num) + ".ogg");
}
void FenetreSFML::volume_up()
{
    bg_music.setVolume(bg_music.getVolume() + 5 > 100 ? 100 : bg_music.getVolume() + 5);
}
void FenetreSFML::volume_down()
{
    bg_music.setVolume(bg_music.getVolume() - 5 < 5 ? 5 : bg_music.getVolume() - 5);
}
bool FenetreSFML::bg_is_finished()
{
    return (bg_music.getDuration() - bg_music.getPlayingOffset()) < sf::seconds(1);
}
void FenetreSFML::play_next()
{
    bg_num += next_bg;
    if (bg_num > max_audio_tracks )
        bg_num = 1;
    else if(bg_num < 1)
        bg_num = max_audio_tracks;
    set_bg_music("data/audio/" + to_string(bg_num) + ".ogg");
}
bool FenetreSFML::pressed_f()
{
    bool tmp = key_f;
    key_f = false;
    return tmp;
}
void FenetreSFML::init_max_track()
{
    max_audio_tracks = 5;
    /*DIR * audio = new DIR;
    audio = opendir("data/audio/");
    struct dirent * audio_dir = new dirent();
    audio_dir = readdir(audio);
    cout<<audio_dir->d_name<<endl;
    cout<<audio_dir->d_name<<endl;
    closedir(audio);*/
}