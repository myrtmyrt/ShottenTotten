//
// Created by Arman Saint-Marc on 14/05/2023.
//

#include "joueur.h"
#include "pioche.h"

Joueur::Joueur(bool bot, bool tactique, const Manche& manche, std::string pseudo){
    _pseudo = pseudo;
    _bot = bot;

    if(tactique == true) _nbCartes = 7;
    else _nbCartes = 6;

    const Carte** mainJoueur = new const Carte*[_nbCartes];
    Pioche pioche = manche.getPioche();

    for (int i = 0; i < _nbCartes; ++i) mainJoueur[i] = &(pioche.piocher());

    _cartes = mainJoueur;
}

Joueur::~Joueur() {
    delete[] _cartes;
}
