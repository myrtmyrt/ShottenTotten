//
// Created by Arman Saint-Marc on 24/04/2023.
//

#ifndef MANCHE
#define MANCHE

#include <iostream>
#include <vector>

#include "jeu.h"
#include "carte.h"
#include "borne.h"
#include "pioche.h"

extern std::initializer_list<Couleur> Couleurs;
extern std::initializer_list<Nombre> Nombres;

class Manche {
private:
    std::vector<Borne*> _bornes;
    std::vector<Carte*> _cartes;
    Pioche* _pioche;

public:
    std::vector<Borne*> getBornes() const {return _bornes; }
    std::vector<Carte*> getCartes() const {return _cartes; }
    Pioche& getPioche() const { return *_pioche; }

    Manche(Jeu& jeu);
    ~Manche() { delete _pioche; }
};


#endif //MANCHE
