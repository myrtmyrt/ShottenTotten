//
// Created by Myrtille Knockaert on 26/04/2023.
//
#include <iostream>
#include "carte.h"
#include "borne.h"
#include "joueur.h"
#include "pioche.h"

using namespace std;

void Pioche::piocher(std::string type, Joueur &jou) {
    std::vector<Carte*> cartesTypes;
    for (Carte* card : _cartes) {
        if (card->getType() == type) {
            cartesTypes.push_back(card);
        }
    }
    srand (time(NULL));
    size_t random = rand() % cartesTypes.size();

    Carte* carte = cartesTypes[random];

    size_t j = 0;
    for (j = 0; j < _cartes.size(); ++j) {
        if (_cartes[j] == carte) {
            break;
        }
    }

    _cartes.erase(_cartes.begin()+j);

    jou.addCarte(carte);

}