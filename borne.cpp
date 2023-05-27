//
// Created by Myrtille Knockaert on 26/04/2023.
//

#include "borne.h"

void Borne::poserCarte(Joueur &j, Carte *c) {
    if (j.getId() == 1) {
        if (_cartesJoueur1.size() < _nbCartesMax) {
            _cartesJoueur1.push_back(c);
            j.supprimerCarte(c);
            if (_cartesJoueur1.size() == _nbCartesMax) {
                //revendiquerBorne();
            }
        } else throw "Attention : nombre max atteint, vous ne pouvez pas ajouter une carte.";

    } else {
        if (_cartesJoueur2.size() < _nbCartesMax) {
            _cartesJoueur2.push_back(c);
            j.supprimerCarte(c);
            if (_cartesJoueur2.size() == _nbCartesMax) {
                //revendiquerBorne();
            }
        } else throw "Attention : nombre max atteint, vous ne pouvez pas ajouter une carte.";
    }
}


void Borne::retirerCarte(Joueur &j, Carte *c) {

    if (j.getId() == 1) {
        auto it = find(_cartesJoueur1.begin(), _cartesJoueur1.end(), c);

        if (it != _cartesJoueur1.end()) {
            // La carte a été trouvée, vous pouvez maintenant la supprimer
            _cartesJoueur1.erase(it);
        } else throw "Cette carte n'est pas sur cette borne";
    }
}
