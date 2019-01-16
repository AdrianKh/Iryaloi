#ifndef TOOLS_H_
#define TOOLS_H_


#include <string>
#include <unistd.h>
#include <iostream>

/**
 * @brief sauvgarde une chaine de char dans un file descripteur
*/
void save(const std::string &s, int fd);
/**
 * @brief lit dans un fd jusqu'à un char stop,
 * ici c'est '\n' et inclue ce char dans le resultat
*/
std::string read_line(int fd,const char stop = '\n');

/**
 * @brief crée un serveur ou un client fd = -1 si err. reourne varie si c'est un serveur qui est creé sinon retourne faux.
 * la fonction tante de connecter à un serveur si ne reussi pas alors crée un client
 * dans le cas contraire crée un serveur.
 * @param fd est le fd crée
*/
bool get_fd(int &fd);

/**
* @brief send close to the player
* par default msg = "CLOSE\n"
*/
void send_close(int fd,const std::string &msg = "CLOSE\n");
/**
 * @brief termine le programme si close à été envoyé
 * fonction abondoné
*/
void verif_reciv(const std::string &msg);

#endif