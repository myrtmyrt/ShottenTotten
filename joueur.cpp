//
// Created by Arman Saint-Marc on 14/05/2023.
//

#include "joueur.h"
#include "carte.h"

void Joueur::afficherCartes() const{
    for (Carte* card : _cartes) {
        card->afficher();
    }
}

bool Joueur::contientCombatDeBoue(){
    for (unsigned int i = 0; i < _cartes.size(); i++) {
        if (_cartes[i]->getType()=="Tactique") {
            if (_cartes[i]->getNom()==TypeTactique::CombatBoue){
                return true;
            };
        }
    }
    return false;
}

void Joueur::addCarte(Carte *carte) {
    _cartes.push_back(carte);
}

void Joueur::supprimerCarte(Carte *carte) {
    auto position = std::find(_cartes.begin(), _cartes.end(), carte);
    _cartes.erase(position);
}



