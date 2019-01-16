#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <assert.h>
#include <algorithm>


template <class T>
class TabDyn{
protected:
    std::vector<T> elements;
public:
    T elementI(unsigned int indice) const;
    void ajouterElement(const T&);
    unsigned int taille_utilise() const;
    void trier();
    void supprimerElementI(unsigned int indice);
    void afficherTab() const;
    /**
     * @brief sauvgarde le tableau en vidant le ficher dans le ficher passé en parametre
    */
    void sauverTab(const std::string &chemin);
    /**
     * @brief charge le tableau à partir du ficher.
    */
    void chargerTab(const std::string &chemin);
    /**
     * @brief sauvgarde le tableau dans le descripteur du ficher.
     * @param le descripteur du ficher peut être un socket ou pipe
    */
    void sauverTab(int fd);
    /**
     * @brief charge le tableau à partir du descripteur du ficher.
     * @param le descripteur du ficher peut être un socket ou pipe
    */
    void chargerTab(int fd);
};



template <class T>
unsigned int TabDyn<T>::taille_utilise() const{
    return elements.size();
}

template <class T>
T TabDyn<T>::elementI(unsigned int indice) const{
    assert(taille_utilise()<indice);
    return elements[indice];
}

template <class T>
void TabDyn<T>::ajouterElement(const T& ele){
    elements.push_back(ele);
}

template <class T>
void TabDyn<T>::afficherTab() const{
    for(unsigned int i =0; i<elements.size();i++)
        std::cout<<elements[i]<<" ";
    std::cout<<std::endl;
}

template <class T>
void TabDyn<T>::supprimerElementI(unsigned int indice){
    if(indice>=elements.size()){
        std::cerr<<"TabDyn indice est plus grand que la taille \n";
        return;
    }
    elements.erase(elements.begin()+indice);
}

template <class T>
void TabDyn<T>::trier(){
    std::sort (elements.begin(), elements.end());
}

template <class T>
void TabDyn<T>::sauverTab(const std::string &chemin){
    
}

template <class T>
void TabDyn<T>::chargerTab(const std::string &chemin){

}