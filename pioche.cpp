//
// Created by Myrtille Knockaert on 26/04/2023.
//

#include "pioche.h"
#include "carte.h"

using namespace std;

Pioche::Pioche(vector<Carte*> cartes) {
    _cartes = cartes;
}

void Pioche::piocher(string type, Joueur &jou) {
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

