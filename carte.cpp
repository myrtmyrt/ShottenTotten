//
// Created by Arman Saint-Marc on 06/05/2023.
//

#include "carte.h"
#include "joueur.h"
#include "borne.h"
#include "manche.h"
#include "jeu.h"

#include "utils.h"

using namespace std;

std::string toString(Couleur c) {
    switch (c) {
        case Couleur::rouge: return "R";
        case Couleur::vert: return "E";
        case Couleur::jaune: return "J";
        case Couleur::orange: return "O";
        case Couleur::violet: return "V";
        case Couleur::bleu: return "B";
        default: std::cout<<"erreur";
    }
}

std::string toString(Nombre v) {
    switch (v) {
        case Nombre::un: return "1";
        case Nombre::deux: return "2";
        case Nombre::trois: return "3";
        case Nombre::quatre: return "4";
        case Nombre::cinq: return "5";
        case Nombre::six: return "6";
        case Nombre::sept: return "7";
        case Nombre::huit: return "8";
        case Nombre::neuf: return "9";
        default: std::cout<<"erreur";
    }
}

std::string toString(TypeTactique v) {
    switch (v) {
        case TypeTactique::porteBouclier: return "Porte bouclier";
        case TypeTactique::espion: return "Espion";
        case TypeTactique::joker: return "Joker";
        case TypeTactique::colinMaillard: return "Colin maillard";
        case TypeTactique::combatBoue: return "Combat boue";
        case TypeTactique::chasseurTete: return "Chasseur tête";
        case TypeTactique::stratege: return "Stratege";
        case TypeTactique::banshee: return "Banshee";
        case TypeTactique::traitre: return "Traitre";
        default: std::cout<<"erreur";
    }
}

std::ostream& operator<<(std::ostream& f, Couleur c) { f << toString(c); return f; }
std::ostream& operator<<(std::ostream& f, Nombre v) {	f << toString(v); return f; }
std::ostream& operator<<(std::ostream& f, TypeTactique v) {	f << toString(v); return f; }

void printTextInColor(Couleur color, Nombre numero) {
    switch (color) {
        case Couleur::rouge:
            std::cout << "\033[31m"; // Mettre texte en rouge
            break;
        case Couleur::vert:
            std::cout << "\033[32m"; // Mettre texte en vert
            break;
        case Couleur::bleu:
            std::cout << "\033[34m"; // Mettre texte en bleu
            break;
        case Couleur::violet:
            std::cout << "\033[35m"; // Mettre texte en violet
            break;
        case Couleur::orange:
            std::cout << "\033[38;5;208m"; // Mettre texte en orange
            break;
        case Couleur::jaune:
            std::cout << "\033[93m"; // Mettre texte en jaune
            break;
        default:
            break;
    }

    std::cout << "["<<numero<<"]" << "\033[m "; // Reset text color to default
}

void printTactique(TypeTactique v) {
    std::cout << "["<<v<<"] ";
}


bool Clan::jouer(Manche* manche, Joueur &j, Jeu* jeu) {

    unsigned int choiceBorne = askForBorne(j, manche, jeu, true);
    if(choiceBorne == 0) return false;
    manche->getBornes()[choiceBorne-1]->poserCarte(j, this);

    pickACardInDeck(j, manche, jeu);

    return true;

}

void Tactique::effet(Joueur &j, Borne *b, Manche *m) {
    _effet(j, b, m);
}

bool Tactique::jouer(Manche* manche, Joueur& j, Jeu* jeu) {
    return _jouer(manche, j, jeu);
}


void Tactique::effetJoker(Joueur &j, Borne *b, Manche* m) {
    if(j.getIsBot() == false){
        if(j.getId() == 1) {
            afficherJoueur1();
        }else{
            afficherJoueur2();
        }
    }

    std::cout<<"\t- Donnez les caractéristiques de votre joker : "<<std::endl;

    Couleur c;
    c = pickAColor(j);

    Nombre n;
    n = pickANumber(j, 1, 9);

    vector<Carte*> cartes;
    if (j.getId() == 1) {
        cartes = b->getCartesJoueur1();
    } else {
        cartes = b->getCartesJoueur2();
    }


    size_t index = 0;
    for (Carte* card : cartes) {
        if(card->getType() == "Tactique") {
            if(card->getNom() == TypeTactique::joker){
                break;
            }
        }
        index++;
    }


    b->retirerCarte(j, cartes[index]);

    Carte* newCarte = new Clan(n, c);
    b->changerCarte(j, newCarte);

}

void Tactique::effetEspion(Joueur &j, Borne *b, Manche* m) {

    if(j.getIsBot() == false){
        if(j.getId() == 1) {
            afficherJoueur1();
        }else{
            afficherJoueur2();
        }
    }

    std::cout<<"\t- Donnez les caractéristiques de votre espion : "<<std::endl;

    Couleur c;
    c = pickAColor(j);

    Nombre n = Nombre::sept;

    vector<Carte*> cartes;
    if (j.getId() == 1) {
        cartes = b->getCartesJoueur1();
    } else {
        cartes = b->getCartesJoueur2();
    }


    size_t index = 0;
    for (Carte* card : cartes) {
        if(card->getType() == "Tactique") {
            if(card->getNom() == TypeTactique::espion){
                break;
            }
        }
        index++;
    }


    b->retirerCarte(j, cartes[index]);

    Carte* newCarte = new Clan(n, c);
    b->changerCarte(j, newCarte);

};

void Tactique::effetPorteBouclier(Joueur &j, Borne *b, Manche* m) {

    if(j.getIsBot() == false){
        if(j.getId() == 1) {
            afficherJoueur1();
        }else{
            afficherJoueur2();
        }
    }

    std::cout<<std::endl<<"\t- Donnez les caractéristiques de votre porte bouclier : "<<std::endl<<std::endl;

    Couleur c;
    c = pickAColor(j);

    Nombre n;
    n = pickANumber(j, 1, 3);

    vector<Carte*> cartes;
    if (j.getId() == 1) {
        cartes = b->getCartesJoueur1();
    } else {
        cartes = b->getCartesJoueur2();
    }


    size_t index = 0;
    for (Carte* card : cartes) {
        if(card->getType() == "Tactique") {
            if(card->getNom() == TypeTactique::porteBouclier){
                break;
            }
        }
        index++;
    }


    b->retirerCarte(j, cartes[index]);

    Carte* newCarte = new Clan(n, c);
    b->changerCarte(j, newCarte);

}

void Tactique::effetColinMaillard(Joueur &j, Borne *b, Manche* m) {}

void Tactique::effetCombatBoue(Joueur &j, Borne *b, Manche* m) {}

void Tactique::effetChasseurTete(Joueur &j, Borne *b, Manche *m) {}

void Tactique::effetStratege(Joueur &j, Borne *b, Manche *m) {}

void Tactique::effetBanshee(Joueur &j, Borne *b, Manche *m) {}

void Tactique::effetTraitre(Joueur &j, Borne *b, Manche *m) {}


/*
 * Jouer les cartes tactiques
 */
bool Tactique::jouerJoker(Manche* manche, Joueur& j, Jeu* jeu){

    if((j.getId() == 1 && jeu->getJoueur2().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees()) || (j.getId() == 2 && jeu->getJoueur1().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees())) {

        unsigned int choiceBorne = askForBorne(j, manche, jeu, true);
        if(choiceBorne == 0) return false;

        Carte* joker;
        for (Carte *card: j.getCartes()) {
            if(card->getType() == "Tactique" && card->getNom() == TypeTactique::joker){
                joker = card;
            }
        }
        manche->getBornes()[choiceBorne - 1]->poserCarte(j, joker);

        pickACardInDeck(j, manche, jeu);
        j.addTactiquesJouees();
        return true;
    }else {
        std::cout << std::endl << "\t\tErreur - Vous ne pouvez pas jouer 2 cartes tactiques de plus que l'adversaire !" << std::endl;
        return false;
    }
}

bool Tactique::jouerEspion(Manche* manche, Joueur& j, Jeu* jeu){
    if((j.getId() == 1 && jeu->getJoueur2().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees()) || (j.getId() == 2 && jeu->getJoueur1().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees())) {
        unsigned int choiceBorne = askForBorne(j, manche, jeu, true);
        if(choiceBorne == 0) return false;

        Carte* espion;
        for (Carte *card: j.getCartes()) {
            if(card->getType() == "Tactique" && card->getNom() == TypeTactique::espion){
                espion = card;
            }
        }
        manche->getBornes()[choiceBorne - 1]->poserCarte(j, espion);

        pickACardInDeck(j, manche, jeu);
        j.addTactiquesJouees();
        return true;
    }else {
        std::cout << std::endl << "\t\tErreur - Vous ne pouvez pas jouer 2 cartes tactiques de plus que l'adversaire !" << std::endl;
        return false;
    }
}

bool Tactique::jouerPorteBouclier(Manche* manche, Joueur& j, Jeu* jeu){
    if((j.getId() == 1 && jeu->getJoueur2().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees()) || (j.getId() == 2 && jeu->getJoueur1().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees())) {
        unsigned int choiceBorne = askForBorne(j, manche, jeu, true);
        if(choiceBorne == 0) return false;

        Carte* porteBouclier;
        for (Carte *card: j.getCartes()) {
            if(card->getType() == "Tactique" && card->getNom() == TypeTactique::porteBouclier){
                porteBouclier = card;
            }
        }
        manche->getBornes()[choiceBorne - 1]->poserCarte(j, porteBouclier);

        pickACardInDeck(j, manche, jeu);
        j.addTactiquesJouees();
        return true;
    }else {
        std::cout << std::endl << "\t\tErreur - Vous ne pouvez pas jouer 2 cartes tactiques de plus que l'adversaire !" << std::endl;
        return false;
    }
}

bool Tactique::jouerColinMaillard(Manche* manche, Joueur& j, Jeu* jeu){
    if((j.getId() == 1 && jeu->getJoueur2().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees()) || (j.getId() == 2 && jeu->getJoueur1().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees())) {
        unsigned int choiceBorne = askForBorne(j, manche, jeu, false);
        if(choiceBorne == 0) return false;

        Carte* colinMaillard;
        for (Carte *card: j.getCartes()) {
            if(card->getType() == "Tactique" && card->getNom() == TypeTactique::colinMaillard){
                colinMaillard = card;
            }
        }
        manche->getBornes()[choiceBorne - 1]->poserCarte(j, colinMaillard);

        pickACardInDeck(j, manche, jeu);
        j.addTactiquesJouees();
        return true;
    }else {
        std::cout << std::endl << "\t\tErreur - Vous ne pouvez pas jouer 2 cartes tactiques de plus que l'adversaire !" << std::endl;
        return false;
    }
}

bool Tactique::jouerCombatBoue(Manche* manche, Joueur& j, Jeu* jeu){
    if((j.getId() == 1 && jeu->getJoueur2().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees()) || (j.getId() == 2 && jeu->getJoueur1().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees())) {
        unsigned int choiceBorne = askForBorne(j, manche, jeu, false);
        if(choiceBorne == 0) return false;

        Carte* combatBoue;
        for (Carte *card: j.getCartes()) {
            if(card->getType() == "Tactique" && card->getNom() == TypeTactique::combatBoue){
                combatBoue = card;
            }
        }
        manche->getBornes()[choiceBorne - 1]->poserCarte(j, combatBoue);
        manche->getBornes()[choiceBorne - 1]->setNbCartesMax(4);

        pickACardInDeck(j, manche, jeu);
        j.addTactiquesJouees();
        return true;
    }else {
        std::cout << std::endl << "\t\tErreur - Vous ne pouvez pas jouer 2 cartes tactiques de plus que l'adversaire !" << std::endl;
        return false;
    }
}

bool Tactique::jouerChasseurTete(Manche* manche, Joueur& j, Jeu* jeu){
    if((j.getId() == 1 && jeu->getJoueur2().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees()) || (j.getId() == 2 && jeu->getJoueur1().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees())) {

        for (int i = 0; i < 3; ++i) {
            pickACardInDeck(j, manche, jeu);
        }

        Carte* chasseurTete;
        for (Carte *card: j.getCartes()) {
            if(card->getType() == "Tactique" && card->getNom() == TypeTactique::chasseurTete){
                chasseurTete = card;
            }
        }
        j.supprimerCarte(chasseurTete);

        for (int i = 0; i < 2; ++i) {
            j.afficherCartes();
            unsigned int choiceCarte = askForCardToDelete(j, manche, jeu);
            j.supprimerCarte(j.getCartes()[choiceCarte - 1]);
        }
        j.addTactiquesJouees();
        return true;
    }else {
        std::cout << std::endl << "\t\tErreur - Vous ne pouvez pas jouer 2 cartes tactiques de plus que l'adversaire !" << std::endl;
        return false;
    }
}

bool Tactique::jouerStratege(Manche* manche, Joueur& j, Jeu* jeu){
    if((j.getId() == 1 && jeu->getJoueur2().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees()) || (j.getId() == 2 && jeu->getJoueur1().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees())) {
        unsigned int choiceBorne = askForBorne(j, manche, jeu, true);
        if(choiceBorne == 0) return false;

            unsigned int choiceCarte = askForCardToChange(j, manche, jeu, choiceBorne);

            unsigned int choiceEffet = 0;
            std::cout << std::endl << "\t- Que voulez-vous en faire (1 : Jetter, 2 : Déplacer) : ";
            std::cin >> choiceEffet;

            if(choiceEffet != 1 && choiceEffet != 2){
                std::cout<<std::endl<<"\t\tErreur - Action inconnue !"<<std::endl;
                return false;
            }

            if(choiceEffet == 1){
                Carte* stratege;
                for (Carte *card: j.getCartes()) {
                    if(card->getType() == "Tactique" && card->getNom() == TypeTactique::stratege){
                        stratege = card;
                    }
                }
                j.supprimerCarte(stratege);

                if(j.getId() == 1){
                    manche->getBornes()[choiceBorne - 1]->retirerCarte(j, manche->getBornes()[choiceBorne - 1]->getCartesJoueur1()[choiceCarte-1]);
                }else{
                    manche->getBornes()[choiceBorne - 1]->retirerCarte(j, manche->getBornes()[choiceBorne - 1]->getCartesJoueur2()[choiceCarte-1]);
                }


            }else{
                unsigned int choiceBorneDestination = askForBorne(j, manche, jeu, true);
                if(choiceBorneDestination == 0) return false;

                Carte* stratege;
                for (Carte *card: j.getCartes()) {
                    if(card->getType() == "Tactique" && card->getNom() == TypeTactique::stratege){
                        stratege = card;
                    }
                }
                j.supprimerCarte(stratege);

                Carte* carteDeplace;
                if(j.getId() == 1){
                    carteDeplace = manche->getBornes()[choiceBorne - 1]->getCartesJoueur1()[choiceCarte-1];
                    manche->getBornes()[choiceBorne - 1]->retirerCarte(j, carteDeplace);
                    manche->getBornes()[choiceBorneDestination - 1]->changerCarte(j, carteDeplace);
                }else{
                    carteDeplace = manche->getBornes()[choiceBorne - 1]->getCartesJoueur2()[choiceCarte-1];
                    manche->getBornes()[choiceBorne - 1]->retirerCarte(j, carteDeplace);
                    manche->getBornes()[choiceBorneDestination - 1]->changerCarte(j, carteDeplace);
                }

            }

        pickACardInDeck(j, manche, jeu);

        j.addTactiquesJouees();
        return true;
    }else {
        std::cout << std::endl << "\t\tErreur - Vous ne pouvez pas jouer 2 cartes tactiques de plus que l'adversaire !" << std::endl;
        return false;
    }
}

bool Tactique::jouerBanshee(Manche* manche, Joueur& j, Jeu* jeu) {
    if((j.getId() == 1 && jeu->getJoueur2().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees()) || (j.getId() == 2 && jeu->getJoueur1().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees())) {
        unsigned int choiceBorne = askForBorne(j, manche, jeu, true);
        if (choiceBorne == 0) return false;

        unsigned int choiceCarte = askForCardToChangeOtherPlayer(j, manche, jeu, choiceBorne);

        Carte *banshee;
        for (Carte *card: j.getCartes()) {
            if (card->getType() == "Tactique" && card->getNom() == TypeTactique::banshee) {
                banshee = card;
            }
        }
        j.supprimerCarte(banshee);

        if (j.getId() == 1) {
            manche->getBornes()[choiceBorne - 1]->retirerCarte(jeu->getJoueur2(), manche->getBornes()[choiceBorne -1]->getCartesJoueur2()[choiceCarte - 1]);
        } else {
            manche->getBornes()[choiceBorne - 1]->retirerCarte(jeu->getJoueur1(), manche->getBornes()[choiceBorne -1]->getCartesJoueur1()[choiceCarte - 1]);
        }


        pickACardInDeck(j, manche, jeu);

        j.addTactiquesJouees();
        return true;
    }else {
        std::cout << std::endl << "\t\tErreur - Vous ne pouvez pas jouer 2 cartes tactiques de plus que l'adversaire !" << std::endl;
        return false;
    }
}

bool Tactique::jouerTraitre(Manche *manche, Joueur &j, Jeu *jeu) {
    if((j.getId() == 1 && jeu->getJoueur2().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees()) || (j.getId() == 2 && jeu->getJoueur1().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees())) {
        unsigned int choiceBorne = askForBorne(j, manche, jeu, true);
        if(choiceBorne == 0) return false;

        unsigned int choiceCarte = askForCardToChangeOtherPlayer(j, manche, jeu, choiceBorne);

        unsigned int choiceBorneDestination = askForBorne(j, manche, jeu, true);
        if(choiceBorneDestination == 0) return false;

        Carte *traitre;
        for (Carte *card: j.getCartes()) {
            if (card->getType() == "Tactique" && card->getNom() == TypeTactique::traitre) {
                traitre = card;
            }
        }
        j.supprimerCarte(traitre);

        Carte *carteDeplace;
        if (j.getId() == 1) {
            carteDeplace = manche->getBornes()[choiceBorne - 1]->getCartesJoueur2()[choiceCarte - 1];
            manche->getBornes()[choiceBorne - 1]->retirerCarte(jeu->getJoueur2(), carteDeplace);
            manche->getBornes()[choiceBorneDestination - 1]->changerCarte(j, carteDeplace);
        } else {
            carteDeplace = manche->getBornes()[choiceBorne - 1]->getCartesJoueur1()[choiceCarte - 1];
            manche->getBornes()[choiceBorne - 1]->retirerCarte(jeu->getJoueur1(), carteDeplace);
            manche->getBornes()[choiceBorneDestination - 1]->changerCarte(j, carteDeplace);
        }


        pickACardInDeck(j, manche, jeu);

        j.addTactiquesJouees();
        return true;
    }else {
        std::cout << std::endl << "\t\tErreur - Vous ne pouvez pas jouer 2 cartes tactiques de plus que l'adversaire !" << std::endl;
        return false;
    }
}
