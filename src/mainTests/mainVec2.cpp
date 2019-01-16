#include "Vec2.h"
#include <iostream>

using namespace std;

void test1();
void test2();

int main()
{
    test2();
    return 0;
}

void test2()
{
    Vec2 t;
    cin>>t;
    cout<<t;
}

void test1()
{
    Vec2 v(0,1);
    //Vec2 v2(0,4);
    Vec2 n = v.normalise();
    cout<<n;
    cin>>n;
    Vec2 v3 = v + n;
    cout<<v3;
    Vec2 v4 = v + n + v3;
    cout<<v4;
}