#include "Image.h"

#include <iostream>
#include <string>

using namespace std;

void testIm(const Image &);

int main()
{
    Image m = Default();
    m.print();
    Image m1("data/map.jpg");
    m1.print();
    m1.set_lien("data/img/wall1.jpg");
    m1.print();
    Image m2("data/non.png");
    
    testIm(m);
    testIm(m1);
    testIm(m2);

    return 0;
}

void testIm(const Image & im){
   if(im.valide())
        cout<<im.get_lien()<<" est valide"<<endl;
    else
        cout<<im.get_lien()<<" n'est pas valide"<<endl;
}
