#include <iostream>
#include "Jeu.h"
#include "Carte.h"
#include "Joueur.h"
#include "Pioche.h"

using namespace std;

int main(int argc, char **argv) {
    string name;
    cout << "Type your name: ";
    cin >> name;

    Joueur j (2, name, true);
    cout<<"Numero : "<< j.getNumero()<<endl;
    cout<<"Nom : "<< j.getName()<<endl;
    cout<<"Humain (1=oui, 2=non) : "<< j.getHuman()<<endl;

    j.afficherCartesClan();

    PiocheClan p;
    p.Melange();
    CarteClan Ctest = *p.Piocher();

    CarteClan* Ctest2=new CarteClan(Ctest.getCouleur(),Ctest.getNombre());
    p.Effacer();
    j.ajouterCarte(Ctest2);





    return 0;

}



