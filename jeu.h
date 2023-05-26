//
// Created by Arman Saint-Marc on 24/04/2023.
//

#ifndef JEU
#define JEU

#include <iostream>
#include "joueur.h"

enum class Mode { normal, tactique };

class Jeu {
private:
    static Jeu* _jeuUnique;
    unsigned int _nbManchesGagnantes;
    Joueur* _joueur1;
    Joueur* _joueur2;
    Mode _modeDeJeu;

    Jeu(const std::string nomJ1, bool adversaireBot, const std::string nomJ2, Mode modeDeJeu, unsigned int nbManchesGagnantes);

public:
    //GETTERS
    unsigned int getNbManchesGagnantes() const { return _nbManchesGagnantes; }
    Joueur& getJoueur1() const { return *_joueur1; }
    Joueur& getJoueur2() const { return *_joueur2; }
    Mode getModeDeJeu() const { return _modeDeJeu; }

    static Jeu& donneInstance(const std::string nomJ1, bool adversaireBot = true, const std::string nomJ2 = "Janet", Mode modeDeJeu = Mode::normal, unsigned int nbManchesGagnantes = 1);
    static void libereInstance();
    static Jeu &getInstance();

    void jouerManche();
};

#endif //JEU

