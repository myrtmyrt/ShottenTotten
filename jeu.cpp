//
// Created by Arman Saint-Marc on 24/04/2023.
//

#include "jeu.h"
#include "manche.h"


//On initialise le jeu unique à un pointeur null par défaut
Jeu *Jeu::_jeuUnique = nullptr;

//On initialise le constructeur de Jeu
Jeu::Jeu(const std::string nomJ1, bool adversaireBot, const std::string nomJ2, Mode modeDeJeu, unsigned int nbManchesGagnantes) {
    _nbManchesGagnantes = nbManchesGagnantes;
    _modeDeJeu = modeDeJeu;
    _joueur1 = new Joueur(1, false, nomJ1);
    _joueur2 = new Joueur(2, adversaireBot, nomJ2);
}

//On initalise la fonction statique permettant d'avoir qu'un seul jeu en même temps
Jeu& Jeu::donneInstance(const std::string nomJ1, bool adversaireBot, const std::string nomJ2, Mode modeDeJeu, unsigned int nbManchesGagnantes) {
    if (_jeuUnique == nullptr) {
        _jeuUnique = new Jeu(nomJ1, adversaireBot, nomJ2, modeDeJeu, nbManchesGagnantes);
        return *_jeuUnique;
    }
}

//On initialise la fonction statique permettant de supprimer le jeu actuel
void Jeu::libereInstance() {
    delete _jeuUnique;
    _jeuUnique = nullptr;
}

//On initialise la fonction statique permettant de récupérer le jeu
Jeu& Jeu::getInstance() { return *_jeuUnique; }

void Jeu::jouerManche(){
    const Manche* mancheActuelle = new Manche(*_jeuUnique);

    return;
}
