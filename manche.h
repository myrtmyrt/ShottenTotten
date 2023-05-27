//
// Created by Arman Saint-Marc on 24/04/2023.
//

#ifndef MANCHE
#define MANCHE

#include <iostream>
#include <vector>

#include "jeu.h"
#include "borne.h"
#include "pioche.h"

using namespace std;

class Carte;
enum class Couleur;
enum class Nombre;

extern initializer_list<Couleur> Couleurs;
extern initializer_list<Nombre> Nombres;

class Manche {
private:
    vector<Borne*> _bornes;
    vector<Carte*> _cartes;
    Pioche *_pioche;

public:
    std::vector<Borne *> getBornes() const { return _bornes; }

    std::vector<Carte*> getCartes() const { return _cartes; }

    Pioche &getPioche() const { return *_pioche; }

    Manche(Jeu &jeu);

    ~Manche() { delete _pioche; }
};


#endif //MANCHE

