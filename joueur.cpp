//
// Created by Arman Saint-Marc on 14/05/2023.
//

#include "joueur.h"
#include "manche.h"
#include "borne.h"

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

unsigned int Joueur::jouerCarteIA() {
    return rand() %(_cartes.size()) + 1;
}

unsigned int Joueur::jouerBorneIA(Manche& manche) {
    std::vector<Borne*> bornes = manche.getBornes();
    unsigned int possibleChoice = 0;
    while(possibleChoice == 0){
        unsigned int random = rand() % bornes.size();
        if(bornes[random]->getGagnant() == nullptr){
            possibleChoice = random;
        }
    }
    return possibleChoice+1;
}

unsigned int Joueur::jouerPiocheIA() {
    size_t nbCartesTactiques = 0;
    for (Carte* carte : _cartes) {
        if(carte->getType() == "Tactique"){
            nbCartesTactiques++;
        }
    }
    if(nbCartesTactiques >= 2){
        return 1;
    }else{
        return rand()%(2) + 1;
    }
}

unsigned int Joueur::jouerAutreIA(unsigned int min, unsigned int max) {
    return rand()%(max-min+1) + min;
}