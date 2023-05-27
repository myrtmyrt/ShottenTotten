//
// Created by Myrtille Knockaert on 26/04/2023.
//

#ifndef PIOCHE
#define PIOCHE

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "carte.h"
#include "joueur.h"

using namespace std;

class Pioche {
private:
    vector<Carte*> _cartes;
public:

    Pioche(vector<Carte*> cartes);

    void piocher(string type, Joueur &jou);

};

#endif //PIOCHE

