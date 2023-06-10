//
// Created by Arman Saint-Marc on 24/04/2023.
//

#include "jeu.h"
#include "manche.h"
#include "utils.h"

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
    /*
     * On reset les données du joueur
     */
    _joueur1->resetCartes();
    _joueur2->resetCartes();

    _joueur1->resetTactiquesJouees();
    _joueur2->resetTactiquesJouees();

    /*
     * Création de manche
     */
    Manche* mancheActuelle = new Manche(*_jeuUnique);

    /*
     * Jouer manche
     */
    while(1){

        /*
         * Joueur 1 choisir une carte et la jouer
         */
        afficherJoueur1();
        std::cout<<std::endl<<std::endl<<"\tCartes de "<<_joueur1->getPseudo()<<" : ";
        _joueur1->afficherCartes();
        mancheActuelle->afficherBornes();

        bool playedProperly = false;
        while(!playedProperly) {
            Carte &cardToPlay = askForCard(_joueur1, mancheActuelle, this);
            playedProperly = cardToPlay.jouer(mancheActuelle, *_joueur1, this);
        }

        if(_modeDeJeu != Mode::expert) {
            clearScreen();
            mancheActuelle->afficherBornes();
            unsigned int borneId = askForBorneId(*_joueur1, mancheActuelle, this);
            if(borneId != 0){
                mancheActuelle->getBornes()[borneId-1]->revendiquer(borneId, *_joueur1, *_joueur2, mancheActuelle, &mancheActuelle->getPioche());
            }

            for (Borne* borne : mancheActuelle->getBornes()) {
                bool isGagnant = mancheActuelle->verifGagnant(*_joueur1);
                if (isGagnant == true) {
                    clearScreen();
                    _joueur1->addPoint();
                    std::cout << std::endl << std::endl << _joueur1->getPseudo() << " A GAGNE LA MANCHE !!!!";
                    waitForEnter();
                    return;
                }
                isGagnant = mancheActuelle->verifGagnant(*_joueur2);
                if (isGagnant == true) {
                    clearScreen();
                    _joueur2->addPoint();
                    std::cout << std::endl << std::endl << _joueur2->getPseudo() << " A GAGNE LA MANCHE !!!!";
                    waitForEnter();
                    break;
                }

            }

        }




        /*
         * Joueur 2 choisir une carte et la jouer
         */
        if(_joueur2->getIsBot() == false) {
            afficherJoueur2();
        }
        std::cout << std::endl << std::endl << "\tCartes de " << _joueur2->getPseudo() << " : ";
        _joueur2->afficherCartes();
        mancheActuelle->afficherBornes();

        playedProperly = false;
        while(!playedProperly) {
            Carte &cardToPlay = askForCard(_joueur2, mancheActuelle, this);
            playedProperly = cardToPlay.jouer(mancheActuelle, *_joueur2, this);
        }

        if(_modeDeJeu != Mode::expert) {
            clearScreen();
            mancheActuelle->afficherBornes();
            unsigned int borneId = askForBorneId(*_joueur2, mancheActuelle, this);
            if(borneId != 0){
                mancheActuelle->getBornes()[borneId-1]->revendiquer(borneId, *_joueur2, *_joueur1, mancheActuelle, &mancheActuelle->getPioche());
            }

            for (Borne* borne : mancheActuelle->getBornes()) {
                bool isGagnant = mancheActuelle->verifGagnant(*_joueur1);
                if (isGagnant == true) {
                    clearScreen();
                    _joueur1->addPoint();
                    std::cout << std::endl << std::endl << _joueur1->getPseudo() << " A GAGNE LA MANCHE !!!!";
                    waitForEnter();
                    return;
                }
                isGagnant = mancheActuelle->verifGagnant(*_joueur2);
                if (isGagnant == true) {
                    clearScreen();
                    _joueur2->addPoint();
                    std::cout << std::endl << std::endl << _joueur2->getPseudo() << " A GAGNE LA MANCHE !!!!";
                    waitForEnter();
                    break;
                }

            }

        }

    }
    return;
}
