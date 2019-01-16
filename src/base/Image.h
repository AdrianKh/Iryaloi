#pragma once

#include <string>

/**
 * @brief la classe contoent le lien vers une image dans une chaine de tableau
*/
class Image{

protected:
    std::string lien;

public:
    /**
     * @brief crée une image à partir une lien passé en paramètre
     * par default le lien est vide donc pas acune image
    */
    Image(const std::string &_lien);
    Image(const char * _lien);
    /**
     * @brief crée un image par default "data/img/default.png"
    */
    Image();
    ~Image();
    /**
     * @brief met à jour le lien vers l'image
    */
    void set_lien(const std::string &_lien);
    void set_lien(const char * _lien);
    /**
     * @berife verifie si l'image existe
    */
    bool valide() const;
    /**
     * @brief retourne le lien
    */
    std::string get_lien() const;
    /**
     * @brief affiche le de l'image
    */
   void print() const;
   
    

};
/**
 * @brief Image par defult
*/
Image Default();
Image Wall1();