#include <iostream>
#include "jeu.h"

using namespace std;

//On initialise le jeu unique à un pointeur null par défaut
Jeu *Jeu::jeuUnique = nullptr;

//On initialise le constructeur de Jeu
Jeu::Jeu(int nbManchesGagnantes, bool adversaireBot, int modeDeJeu) {
    _nbManchesGagnantes = nbManchesGagnantes;
    _adversaireBot = adversaireBot;
    _modeDeJeu = modeDeJeu;
    _victoireJoueur1 = 0;
    _victoireJoueur2 = 0;
}

//On initalise la fonction statique permettant d'avoir qu'un seul jeu en même temps
Jeu &Jeu::donneInstance(int nbManchesGagnantes, bool adversaireBot, int modeDeJeu) {
    if (jeuUnique == nullptr) {
        jeuUnique = new Jeu(nbManchesGagnantes, adversaireBot, modeDeJeu);
        return *jeuUnique;
    }
}

//On initialise la fonction statique permettant de supprimer le jeu actuel
void Jeu::libereInstance() {
    delete jeuUnique;
    jeuUnique = nullptr;
}

//On initialise la fonction statique permettant de récupérer le jeu
Jeu &Jeu::getInstance() { return *jeuUnique; }
