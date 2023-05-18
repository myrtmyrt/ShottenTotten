#include <iostream>
#include "jeu.h"
#include "carte.h"
#include "pioche.h"

using namespace std;

int main(int argc, char **argv) {
    Jeu j1 = Jeu::donneInstance(1, true, 0);
    cout << "Nombre de manches : " << j1.getNbManchesGagnantes() << endl;
    cout << "Partie Normale : 0 ou tactique: 1 :" << j1.getmodeDeJeu() << endl;
    vector<Carte> c;
    Couleur CouleursPossibles[6] = {Couleur::Rouge, Couleur::Bleu, Couleur::Vert, Couleur::Violet, Couleur::Orange,
                                    Couleur::Jaune};
    Nombre NombresPossibles[9] = {Nombre::Un, Nombre::Deux, Nombre::Trois, Nombre::Quatre, Nombre::Cinq, Nombre::Six,
                                  Nombre::Sept, Nombre::Huit, Nombre::Neuf};
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 9; j++) {
            CarteClan newCarte(CouleursPossibles[i], NombresPossibles[j]);
            c.push_back(newCarte);
        }
    }
    StrategiePiocheClan pioche(c);
    auto test=pioche.piocher();
    test.afficher();
    return 0;
}

