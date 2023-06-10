//
// Created by Arman Saint-Marc on 09/06/2023.
//


#ifndef UTILS
#define UTILS

#include <cstdlib>
#include <limits>

#include "jeu.h"
#include "manche.h"
#include "carte.h"
#include "joueur.h"
#include "pioche.h"


void clearScreen();
void waitForEnter();
void clearCin();

void afficherJoueur1();
void afficherJoueur2();

Couleur pickAColor(Joueur& joueur);
Nombre pickANumber(Joueur& joueur, unsigned int min, unsigned int max);

Carte& askForCard(Joueur* joueur, Manche* mancheActuelle, Jeu* jeuActuel);
unsigned int askForBorne(Joueur& joueur, Manche* mancheActuelle, Jeu* jeuActuel, bool jouerSurBorne);
void pickACardInDeck(Joueur& joueur, Manche* mancheActuelle, Jeu* jeuActuel);
unsigned int askForCardToDelete(Joueur& joueur, Manche* mancheActuelle, Jeu* jeuActuel);
unsigned int askForCardToChange(Joueur& joueur, Manche* mancheActuelle, Jeu* jeuActuel, unsigned int borneNum);
unsigned int askForCardToChangeOtherPlayer(Joueur& joueur, Manche* mancheActuelle, Jeu* jeuActuel, unsigned int borneNum);
unsigned int askForBorneId(Joueur& joueur, Manche* mancheActuelle, Jeu* jeuActuel);


std::vector<std::vector<Carte *>> creerPossibilites(std::vector<Carte *> cartesPosees, std::vector<Carte *> cartesNonPosees);
#endif //UTILS
