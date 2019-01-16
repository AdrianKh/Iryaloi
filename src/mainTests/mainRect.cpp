#include <iostream>

#include "Rectangle.h"


using namespace std;


int main()
{
    Rectangle rect;
    cout<<rect<<endl;
    cin>>rect;
    cout<<rect<<endl;
    rect = Rectangle(Vec2(34,34),22,22);
    cout<<rect<<endl;
    Rectangle rect2(rect);
    cout<<rect2<<endl;
    return 0;
}