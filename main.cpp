#include <iostream>
#include "jeu.h"
#include "carte.h"
#include "pioche.h"

using namespace std;

int main(int argc, char **argv) {
    Jeu j1 = Jeu::donneInstance(1, true, 0);
    cout << "Nombre de manches : " << j1.getNbManchesGagnantes()<<endl;
    cout << "Partie Normale : 0 ou tactique: 1 :" << j1.getmodeDeJeu()<<endl;
    auto p = new Pioche();
    cout<<p->getNbcarte()<<endl;
    return 0;
}

