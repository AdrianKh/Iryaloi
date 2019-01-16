#include "TabDyn.h"
#include "Vec2.h"
#include "Cercle.h"
#include <cstdlib>
#include <ctime>


using namespace std;

int main()
{
    srand(time(NULL));
    TabDyn<Cercle> t;
    for(int i=0; i<100;i++)
        t.ajouterElement(Cercle(rand()%200));
    cout<<t.taille_utilise()<<endl;
    t.trier();
    t.afficherTab();
    return 0;
}
