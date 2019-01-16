#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>
#include <fstream>

#include "Jeu.h"
#include "socklib.hpp"
#include "FenetreSFML.h"

using namespace std;
using namespace socklib;

int main()
{

    srand(time(NULL));
    Jeu j;
    string port, ip;
    cout << "port : ";
    cin >> port;
    cout << "ip : ";
    cin >> ip;
    int socket, connection;
    bool serveur = false;
    if (ip.size()<2)
    {
        socket = CreeSocketServeur(port);
        cout<<"server created : \n";
        connection = AcceptConnexion(socket);
        serveur = true;
    }
    else
    {
        connection = CreeSocketClient(ip, port);
    }
    FenetreSFML window;
    window.init("Jeu 1", 1000, 600);
    j.init();
    if (serveur)
    {
        j.sauver(connection);
    }
    else
    {
        j.charger(connection);
    }
    window.setView(&j.getJoueur().getCam());
    while (window.isOpen())
    {
        window.gererEvenement();
        window.clear(sf::Color::Black);
        window.updateView();

        j.getJoueur().deplacerJoueur(window.getMousePos());
        if (window.spacePressed())
        {
            cout << "space" << endl;
            j.getJoueur().diviser();
        }
        j.update();
        window.draw(j);
        window.display();
        if (serveur)
        {
            j.sauver(connection);
            serveur = false;
        }
        else
        {
            j.charger(connection);
            serveur = true;
        }
    }
    close(connection);
    close(socket);

    return 0;
}
