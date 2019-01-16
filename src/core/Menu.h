#pragma once

#include <iostream>
#include "Case.h"
#include <string>
#include <vector>


class Menu{
protected:
    std::vector<Case> home;
public:
    Menu();
    ~Menu(){};
    void init();
    std::vector<Case> &get_home(){ return home;}
    etat get_etat(const Vec2 &)const;
};