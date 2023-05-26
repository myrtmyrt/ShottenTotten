//
// Created by Arman Saint-Marc on 14/05/2023.
//

#ifndef PIOCHE
#define PIOCHE

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "carte.h"
#include "joueur.h"


class Pioche {
private:
    std::vector<Carte*> _cartes;
public:

    Pioche(std::vector<Carte*> cartes);

    void piocher(std::string type, Joueur &jou);

};

#endif //PIOCHE
