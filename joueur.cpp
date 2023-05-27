//
// Created by Arman Saint-Marc on 14/05/2023.
//

#include "joueur.h"

void Joueur::afficherCartes() const{
    for (Carte* card : _cartes) {
        card->afficher();
    }
}


