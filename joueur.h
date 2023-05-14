//
// Created by Arman Saint-Marc on 14/05/2023.
//

#ifndef JOUEUR
#define JOUEUR

#include <iostream>
#include <string>
#include "carte.h"
#include "manche.h"
#include "pioche.h"

class Joueur {
private:
    const Carte** _cartes = nullptr;
    unsigned int _nbCartes;
    std::string _pseudo;
    bool _bot;
public:

    Joueur(bool bot, bool tactique, const Manche& manche, std::string pseudo = "Janet");

    ~Joueur();
};

#endif //JOUEUR
