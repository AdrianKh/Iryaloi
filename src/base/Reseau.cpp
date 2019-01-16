#include "Reseau.h"

#include <string>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "socklib.hpp"

#include <unistd.h>
#include <iostream>
#include <sstream>

#include <SFML/Network.hpp>

using namespace std;
using namespace socklib;
using namespace sf;

int get_connection(){
    int server , connection = 0;
    string port, ip;
    cout << "c'est le même dans le client et serveur \nport : ";
    cin >> port;
    cout << "saisir uniquement si c'est client sinon saisir 's'\nip : ";
    cin >> ip;
    sf::IpAddress ip_to_p =  sf::IpAddress::getLocalAddress();

    if(ip.size()<2)
    {
        server = CreeSocketServeur(port);
        cout<<"connecter avec client pour commencer à jouer"<<endl;
        cout<<"taper l'adresse suivant dans le client : "<<ip_to_p.toString()<<endl;
        connection = AcceptConnexion(server);
        close(server);
    }

    else
    {
        connection = CreeSocketClient(ip,port);
    }

    return connection;
}

Reseau::Reseau(){
    connection = -1;
    v_is_server = false;
    v_flip_turn = false;
}
Reseau::~Reseau(){
    if(connection > 2)
        close(connection);
}

bool Reseau::valid_ip(const std::string &ip){

    return ip.size() > 10;
}

void Reseau::init(){
    int server = 0;
    string port, ip;
    cout << "c'est le même dans le client et serveur ex: 8080 \nport : ";
    cin >> port;
    cout << "si vous voulez créee un serveur saisir 's' \nsinon l'adress afficher dans le serveur \nip : ";
    cin >> ip;

    if(ip.size()<2)
    {
        sf::IpAddress ip_to_p =  sf::IpAddress::getLocalAddress();
        server = CreeSocketServeur(port);
        cout<<" Se connecter avec client pour commencer à jouer"<<endl;
        cout<<"Taper l'adresse suivante dans le client : "<<ip_to_p.toString()<<endl;
        connection = AcceptConnexion(server);
        close(server);
        v_is_server = true;
        v_flip_turn = true;
    }

    else
    {
        while(!valid_ip(ip))
        {
            cout<<"taper une adresse ip valide\n ip: ";
            cin>>ip;

        }
        connection = CreeSocketClient(ip,port);
    }
}

int Reseau::get_connection() const{
    return connection;
}

bool Reseau::is_server() const{
    return v_is_server;
}

bool Reseau::flip_trun(){
    bool tmp = v_flip_turn;
    v_flip_turn = !v_flip_turn;
    return tmp;
}