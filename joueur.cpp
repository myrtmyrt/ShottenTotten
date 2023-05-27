//
// Created by Arman Saint-Marc on 14/05/2023.
//

#include "joueur.h"

void Joueur::afficherCartes() const{
    for (Carte* card : _cartes) {
        card->afficher();
    }
}

void Joueur::addCarte(Carte *carte) {
    _cartes.push_back(carte);
}

void Joueur::supprimerCarte(Carte *carte) {
    auto position = std::find(_cartes.begin(), _cartes.end(), carte);
    _cartes.erase(position);
}

