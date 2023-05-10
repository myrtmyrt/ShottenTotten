#include <iostream>


#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <random>


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



    PiocheClan p;




    CarteClan* Ctest = p.Piocher();
    j.ajouterCarte(Ctest);

    CarteClan* Ctest2 = p.Piocher();
    j.ajouterCarte(Ctest2);

    CarteClan* Ctest3 = p.Piocher();
    j.ajouterCarte(Ctest3);

    CarteClan* Ctest4 = p.Piocher();
    j.ajouterCarte(Ctest4);














    j.afficherCartesClan();






    return 0;

}








