#include <iostream>

#include "json.hpp"
#include "tools.h"
#include "Vec2.h"

using json = nlohmann::json;
using std::cout;
using std::endl;



void testCouleur();
void testVec2();
void testCercle();


int main(){

    testCercle();
    //testCouleur();
    //testVec2();

    return 0;
}

void testCercle(){
    json j;

    for(int i=0; i<10;i++)
        j.push_back(toJson(Cercle(i,i*2,i+5)));

    cout<<j.dump(4)<<endl;
}


void testCouleur(){
    json j;
    for(int i=0;i<10; i++){
        j.push_back(toJson(Couleur(i,i*2,i*3,i*4)));
    }
    cout<<j.dump(4)<<endl;
    Couleur col[j.size()];
    for(int i=0; i<10; i++){
        col[i] = toCouleur(j[i]);
        cout<<col[i]<<endl;
    }

}

void testVec2(){
    json j;
    for(int i=0;i<10; i++){
        j["Vec2"].push_back(toJson(Vec2(i,i*-2)));
    }
    cout<<j.dump(4)<<endl;
    Vec2 tabVec2[j["Vec2"].size()];
    for(int i=0; i<j["Vec2"].size(); i++)
        tabVec2[i] = toVec2(j["Vec2"][i]);

    for(int i=0; i<j["Vec2"].size(); i++)
        cout<<tabVec2[i]<<endl;
    
}