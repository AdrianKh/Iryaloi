#pragma once


#include <string>
/**
 * @brief crée une connection soit un client ou un serveur
*/
int get_connection();

class Reseau{

protected:
    int connection;
    bool v_is_server;
    bool v_flip_turn;
    /**
     * @brief vérifie la validité d'une adresse ip . 
    */
    bool valid_ip(const std::string & ip);
public:
    Reseau();
    ~Reseau();
    void init();
    int get_connection() const;
    bool is_server() const;
    bool flip_trun();
};