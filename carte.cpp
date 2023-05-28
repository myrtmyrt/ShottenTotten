//
// Created by Arman Saint-Marc on 06/05/2023.
//

#include "carte.h"
#include "joueur.h"
#include "borne.h"
#include "manche.h"
#include "jeu.h"

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
    unsigned int choiceBorne = 0;

    std::cout<<std::endl<<std::endl<<"\t2 - Sélectionnez une borne (n°) : ";
    std::cin>>choiceBorne;
    if(manche->getBornes().size() >= choiceBorne && choiceBorne != 0 && manche->getBornes()[choiceBorne-1]->estPleine(j) == false && manche->getBornes()[choiceBorne - 1]->getGagnant() ==
                                                                                                                                     nullptr){

        manche->getBornes()[choiceBorne-1]->poserCarte(j, this);

        if(jeu->getModeDeJeu() == Mode::normal){
            manche->getPioche().piocher("Clan", j);
        }else{
            int choicePioche = 0;
            while(choicePioche != 1 && choicePioche != 2){
                std::cout<<std::endl<<"\t3 - Piocher carte (1 : Clan, 2 : Tactique) : ";
                std::cin>>choicePioche;
            }
            if(choicePioche == 1){
                manche->getPioche().piocher("Clan", j);
            }else{
                manche->getPioche().piocher("Tactique", j);
            }
        }

        return true;
    }else{
        std::cout<<std::endl<<"\t\tErreur - La borne n'existe pas ou est pleine !"<<std::endl;
        return false;
    }
}

void Tactique::effet(Joueur &j, Borne *b, Manche *m) {
    _effet(j, b, m);
}

bool Tactique::jouer(Manche* manche, Joueur& j, Jeu* jeu) {
    return _jouer(manche, j, jeu);
}


void Tactique::effetJoker(Joueur &j, Borne *b, Manche* m) {
    Couleur c;
    Nombre n;
    cout << "Donne la couleur de la carte désirée : " << endl;
    cout << "Rouge(1),Bleu(2), Vert(3), Violet(4), Orange(5), Jaune(6)" << endl;
    int couleurInput;
    cin >> couleurInput;

    // on convertit le nombre en la couleur correspondante dans l'enum
    switch (couleurInput) {
        case 1:
            c = Couleur::rouge;
            break;
        case 2:
            c = Couleur::bleu;
            break;
        case 3:
            c = Couleur::vert;
            break;
        case 4:
            c = Couleur::violet;
            break;
        case 5:
            c = Couleur::orange;
            break;
        case 6:
            c = Couleur::jaune;
            break;
        default:
            cout << "Couleur invalide !" << endl;
    }
    cout << "Donne la nombre en chiffre de la carte désirée (allant de 1 à 9): ";
    int nombreInput;
    cin >> nombreInput;

    // on convertit le nombre avec le nombre correspondant dans l'enum
    switch (nombreInput) {
        case 1:
            n = Nombre::un;
            break;
        case 2:
            n = Nombre::deux;
            break;
        case 3:
            n = Nombre::trois;
            break;
        case 4:
            n = Nombre::quatre;
            break;
        case 5:
            n = Nombre::cinq;
            break;
        case 6:
            n = Nombre::six;
            break;
        case 7:
            n = Nombre::sept;
            break;
        case 8:
            n = Nombre::huit;
            break;
        case 9:
            n = Nombre::neuf;
            break;
        default:
            cout << "Nombre invalide !" << endl;
    }

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
    Couleur c;
    Nombre n = Nombre::sept;

    cout << "Donne la couleur de la carte désirée : " << endl;
    cout << "Rouge(1),Bleu(2), Vert(3), Violet(4), Orange(5), Jaune(6)" << endl;
    int couleurInput;
    cin >> couleurInput;

    // on convertit le nombre en la couleur correspondante dans l'enum
    switch (couleurInput) {
        case 1:
            c = Couleur::rouge;
            break;
        case 2:
            c = Couleur::bleu;
            break;
        case 3:
            c = Couleur::vert;
            break;
        case 4:
            c = Couleur::violet;
            break;
        case 5:
            c = Couleur::orange;
            break;
        case 6:
            c = Couleur::jaune;
            break;
        default:
            cout << "Couleur invalide !" << endl;
    }

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
    Couleur c;
    Nombre n;
    cout << "Donne la couleur de la carte désirée : " << endl;
    cout << "Rouge(1),Bleu(2), Vert(3), Violet(4), Orange(5), Jaune(6)" << endl;
    int couleurInput;
    cin >> couleurInput;

    // on convertit le nombre en la couleur correspondante dans l'enum
    switch (couleurInput) {
        case 1:
            c = Couleur::rouge;
            break;
        case 2:
            c = Couleur::bleu;
            break;
        case 3:
            c = Couleur::vert;
            break;
        case 4:
            c = Couleur::violet;
            break;
        case 5:
            c = Couleur::orange;
            break;
        case 6:
            c = Couleur::jaune;
            break;
        default:
            cout << "Couleur invalide !" << endl;
    }
    cout << "Donne la nombre en chiffre de la carte désirée (allant de 1 à 3): ";
    int nombreInput;
    cin >> nombreInput;

    // on convertit le nombre avec le nombre correspondant dans l'enum
    switch (nombreInput) {
        case 1:
            n = Nombre::un;
            break;
        case 2:
            n = Nombre::deux;
            break;
        case 3:
            n = Nombre::trois;
            break;
        default:
            cout << "Nombre invalide !" << endl;
    }

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

void Tactique::effetCombatBoue(Joueur &j, Borne *b, Manche* m) {
}

void Tactique::effetChasseurTete(Joueur &j, Borne *b, Manche *m) {
}

void Tactique::effetStratege(Joueur &j, Borne *b, Manche *m) {}

void Tactique::effetBanshee(Joueur &j, Borne *b, Manche *m) {}

void Tactique::effetTraitre(Joueur &j, Borne *b, Manche *m) {}


/*
 * Jouer les cartes tactiques
 */
bool Tactique::jouerJoker(Manche* manche, Joueur& j, Jeu* jeu){

    if((j.getId() == 1 && jeu->getJoueur2().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees()) || (j.getId() == 2 && jeu->getJoueur1().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees())) {
        unsigned int choiceBorne = 0;

        std::cout << std::endl << std::endl << "\t2 - Sélectionnez une borne (n°) : ";
        std::cin >> choiceBorne;
        if (manche->getBornes().size() >= choiceBorne && choiceBorne != 0 &&
            manche->getBornes()[choiceBorne - 1]->estPleine(j) == false && manche->getBornes()[choiceBorne - 1]->getGagnant() ==
                                                                           nullptr) {

            Carte* joker;
            for (Carte *card: j.getCartes()) {
                if(card->getType() == "Tactique" && card->getNom() == TypeTactique::joker){
                    joker = card;
                }
            }
            manche->getBornes()[choiceBorne - 1]->poserCarte(j, joker);

            if (jeu->getModeDeJeu() == Mode::normal) {
                manche->getPioche().piocher("Clan", j);
            } else {
                int choicePioche = 0;
                while (choicePioche != 1 && choicePioche != 2) {
                    std::cout << std::endl << "\t3 - Piocher carte (1 : Clan, 2 : Tactique) : ";
                    std::cin >> choicePioche;
                }
                if (choicePioche == 1) {
                    manche->getPioche().piocher("Clan", j);
                } else {
                    manche->getPioche().piocher("Tactique", j);
                }
            }

            j.addTactiquesJouees();
            return true;
        } else {
            std::cout << std::endl << "\t\tErreur - La borne n'existe pas ou est pleine !" << std::endl;
            return false;
        }
    }else{
        std::cout << std::endl << "\t\tErreur - Vous ne pouvez jouer qu'une carte tactique de plus que l'adversaire !" << std::endl;
        return false;
    }
}

bool Tactique::jouerEspion(Manche* manche, Joueur& j, Jeu* jeu){
    if((j.getId() == 1 && jeu->getJoueur2().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees()) || (j.getId() == 2 && jeu->getJoueur1().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees())) {
        unsigned int choiceBorne = 0;

        std::cout << std::endl << std::endl << "\t2 - Sélectionnez une borne (n°) : ";
        std::cin >> choiceBorne;
        if (manche->getBornes().size() >= choiceBorne && choiceBorne != 0 &&
            manche->getBornes()[choiceBorne - 1]->estPleine(j) == false && manche->getBornes()[choiceBorne - 1]->getGagnant() ==
                                                                           nullptr) {

            Carte* espion;
            for (Carte *card: j.getCartes()) {
                if(card->getType() == "Tactique" && card->getNom() == TypeTactique::espion){
                    espion = card;
                }
            }
            manche->getBornes()[choiceBorne - 1]->poserCarte(j, espion);

            if (jeu->getModeDeJeu() == Mode::normal) {
                manche->getPioche().piocher("Clan", j);
            } else {
                int choicePioche = 0;
                while (choicePioche != 1 && choicePioche != 2) {
                    std::cout << std::endl << "\t3 - Piocher carte (1 : Clan, 2 : Tactique) : ";
                    std::cin >> choicePioche;
                }
                if (choicePioche == 1) {
                    manche->getPioche().piocher("Clan", j);
                } else {
                    manche->getPioche().piocher("Tactique", j);
                }
            }

            j.addTactiquesJouees();
            return true;
        } else {
            std::cout << std::endl << "\t\tErreur - La borne n'existe pas ou est pleine !" << std::endl;
            return false;
        }
    }else{
        std::cout << std::endl << "\t\tErreur - Vous ne pouvez jouer qu'une carte tactique de plus que l'adversaire !" << std::endl;
        return false;
    }
}

bool Tactique::jouerPorteBouclier(Manche* manche, Joueur& j, Jeu* jeu){
    if((j.getId() == 1 && jeu->getJoueur2().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees()) || (j.getId() == 2 && jeu->getJoueur1().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees())) {
        unsigned int choiceBorne = 0;

        std::cout << std::endl << std::endl << "\t2 - Sélectionnez une borne (n°) : ";
        std::cin >> choiceBorne;
        if (manche->getBornes().size() >= choiceBorne && choiceBorne != 0 &&
            manche->getBornes()[choiceBorne - 1]->estPleine(j) == false && manche->getBornes()[choiceBorne - 1]->getGagnant() ==
                                                                           nullptr) {

            Carte* porteBouclier;
            for (Carte *card: j.getCartes()) {
                if(card->getType() == "Tactique" && card->getNom() == TypeTactique::porteBouclier){
                    porteBouclier = card;
                }
            }
            manche->getBornes()[choiceBorne - 1]->poserCarte(j, porteBouclier);

            if (jeu->getModeDeJeu() == Mode::normal) {
                manche->getPioche().piocher("Clan", j);
            } else {
                int choicePioche = 0;
                while (choicePioche != 1 && choicePioche != 2) {
                    std::cout << std::endl << "\t3 - Piocher carte (1 : Clan, 2 : Tactique) : ";
                    std::cin >> choicePioche;
                }
                if (choicePioche == 1) {
                    manche->getPioche().piocher("Clan", j);
                } else {
                    manche->getPioche().piocher("Tactique", j);
                }
            }

            j.addTactiquesJouees();
            return true;
        } else {
            std::cout << std::endl << "\t\tErreur - La borne n'existe pas ou est pleine !" << std::endl;
            return false;
        }
    }else{
        std::cout << std::endl << "\t\tErreur - Vous ne pouvez jouer qu'une carte tactique de plus que l'adversaire !" << std::endl;
        return false;
    }
}

bool Tactique::jouerColinMaillard(Manche* manche, Joueur& j, Jeu* jeu){
    if((j.getId() == 1 && jeu->getJoueur2().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees()) || (j.getId() == 2 && jeu->getJoueur1().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees())) {
        unsigned int choiceBorne = 0;

        std::cout << std::endl << std::endl << "\t2 - Sélectionnez une borne (n°) : ";
        std::cin >> choiceBorne;
        if (manche->getBornes().size() >= choiceBorne && choiceBorne != 0 && manche->getBornes()[choiceBorne - 1]->getGagnant() ==
                                                                           nullptr) {

            Carte* colinMaillard;
            for (Carte *card: j.getCartes()) {
                if(card->getType() == "Tactique" && card->getNom() == TypeTactique::colinMaillard){
                    colinMaillard = card;
                }
            }
            manche->getBornes()[choiceBorne - 1]->poserCarte(j, colinMaillard);

            if (jeu->getModeDeJeu() == Mode::normal) {
                manche->getPioche().piocher("Clan", j);
            } else {
                int choicePioche = 0;
                while (choicePioche != 1 && choicePioche != 2) {
                    std::cout << std::endl << "\t3 - Piocher carte (1 : Clan, 2 : Tactique) : ";
                    std::cin >> choicePioche;
                }
                if (choicePioche == 1) {
                    manche->getPioche().piocher("Clan", j);
                } else {
                    manche->getPioche().piocher("Tactique", j);
                }
            }

            j.addTactiquesJouees();
            return true;
        } else {
            std::cout << std::endl << "\t\tErreur - La borne n'existe pas ou est pleine !" << std::endl;
            return false;
        }
    }else{
        std::cout << std::endl << "\t\tErreur - Vous ne pouvez jouer qu'une carte tactique de plus que l'adversaire !" << std::endl;
        return false;
    }
}

bool Tactique::jouerCombatBoue(Manche* manche, Joueur& j, Jeu* jeu){
    if((j.getId() == 1 && jeu->getJoueur2().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees()) || (j.getId() == 2 && jeu->getJoueur1().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees())) {
        unsigned int choiceBorne = 0;

        std::cout << std::endl << std::endl << "\t2 - Sélectionnez une borne (n°) : ";
        std::cin >> choiceBorne;
        if (manche->getBornes().size() >= choiceBorne && choiceBorne != 0 && manche->getBornes()[choiceBorne - 1]->getGagnant() ==
                                                                             nullptr) {

            Carte* combatBoue;
            for (Carte *card: j.getCartes()) {
                if(card->getType() == "Tactique" && card->getNom() == TypeTactique::combatBoue){
                    combatBoue = card;
                }
            }
            manche->getBornes()[choiceBorne - 1]->poserCarte(j, combatBoue);
            manche->getBornes()[choiceBorne - 1]->setNbCartesMax(4);

            if (jeu->getModeDeJeu() == Mode::normal) {
                manche->getPioche().piocher("Clan", j);
            } else {
                int choicePioche = 0;
                while (choicePioche != 1 && choicePioche != 2) {
                    std::cout << std::endl << "\t3 - Piocher carte (1 : Clan, 2 : Tactique) : ";
                    std::cin >> choicePioche;
                }
                if (choicePioche == 1) {
                    manche->getPioche().piocher("Clan", j);
                } else {
                    manche->getPioche().piocher("Tactique", j);
                }
            }

            j.addTactiquesJouees();
            return true;
        } else {
            std::cout << std::endl << "\t\tErreur - La borne n'existe pas ou est pleine !" << std::endl;
            return false;
        }
    }else{
        std::cout << std::endl << "\t\tErreur - Vous ne pouvez jouer qu'une carte tactique de plus que l'adversaire !" << std::endl;
        return false;
    }
}

bool Tactique::jouerChasseurTete(Manche* manche, Joueur& j, Jeu* jeu){
    if((j.getId() == 1 && jeu->getJoueur2().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees()) || (j.getId() == 2 && jeu->getJoueur1().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees())) {
        for (int i = 0; i < 3; ++i) {
            int choicePioche = 0;
            while (choicePioche != 1 && choicePioche != 2) {
                std::cout << std::endl << "\t" << i + 1 << " - Piocher carte (1 : Clan, 2 : Tactique) : ";
                std::cin >> choicePioche;
            }
            if (choicePioche == 1) {
                manche->getPioche().piocher("Clan", j);
            } else {
                manche->getPioche().piocher("Tactique", j);
            }
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
            unsigned int choiceCarte = 0;
            bool carteVerif = false;
            while (choiceCarte == 0 || carteVerif == false) {
                std::cout << std::endl << "\t" << i << " - Sélectionnez une carte à jetter (n°) : ";
                std::cin >> choiceCarte;
                if (j.getCartes().size() >= choiceCarte && choiceCarte != 0) {
                    carteVerif = true;
                } else {
                    carteVerif = false;
                    std::cout << std::endl
                              << "\t\tErreur - La carte n'existe pas ou vous n'avez pas le droit de la jouer !"
                              << std::endl;
                }
            }

            j.supprimerCarte(j.getCartes()[choiceCarte - 1]);
        }
        j.addTactiquesJouees();
        return true;
    }else{
        std::cout << std::endl << "\t\tErreur - Vous ne pouvez jouer qu'une carte tactique de plus que l'adversaire !" << std::endl;
        return false;
    }
}

bool Tactique::jouerStratege(Manche* manche, Joueur& j, Jeu* jeu){
    if((j.getId() == 1 && jeu->getJoueur2().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees()) || (j.getId() == 2 && jeu->getJoueur1().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees())) {
        unsigned int choiceBorne = 0;

        std::cout << std::endl << std::endl << "\t2 - Sélectionnez une borne pour prendre la carte (n°) : ";
        std::cin >> choiceBorne;
        if (manche->getBornes().size() >= choiceBorne && choiceBorne != 0 &&
            manche->getBornes()[choiceBorne - 1]->estPleine(j) == false && manche->getBornes()[choiceBorne - 1]->getGagnant() ==
                                                                                   nullptr) {

            unsigned int choiceCarte = 0;
            std::cout<<std::endl<<"\t3 - Sélectionnez la carte à déplacer (n°) : ";
            std::cin>>choiceCarte;
            if(j.getId() == 1){
                if(manche->getBornes()[choiceBorne - 1]->getCartesJoueur1().size() < choiceCarte || choiceCarte == 0){
                    std::cout<<std::endl<<"\t\tErreur - La carte n'existe pas !"<<std::endl;
                    return false;
                }
            }else{
                if(manche->getBornes()[choiceBorne - 1]->getCartesJoueur2().size() < choiceCarte || choiceCarte == 0){
                    std::cout<<std::endl<<"\t\tErreur - La carte n'existe pas !"<<std::endl;
                    return false;
                }
            }

            unsigned int choiceEffet = 0;
            std::cout << std::endl << "\t4 - Que voulez-vous en faire (1 : Jetter, 2 : Déplacer) : ";
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
                unsigned int choiceBorneDestination = 0;

                std::cout << std::endl << std::endl << "\t5 - Sélectionnez une borne de destination (n°) : ";
                std::cin >> choiceBorneDestination;
                if (manche->getBornes().size() >= choiceBorneDestination && choiceBorneDestination != 0 &&
                    manche->getBornes()[choiceBorneDestination - 1]->estPleine(j) == false && manche->getBornes()[choiceBorneDestination - 1]->getGagnant() ==
                                                                                   nullptr) {
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

                }else{
                    std::cout << std::endl << "\t\tErreur - La borne n'existe pas ou est pleine !" << std::endl;
                    return false;
                }

            }

            if (jeu->getModeDeJeu() == Mode::normal) {
                manche->getPioche().piocher("Clan", j);
            } else {
                int choicePioche = 0;
                while (choicePioche != 1 && choicePioche != 2) {
                    std::cout << std::endl << "\t5 - Piocher carte (1 : Clan, 2 : Tactique) : ";
                    std::cin >> choicePioche;
                }
                if (choicePioche == 1) {
                    manche->getPioche().piocher("Clan", j);
                } else {
                    manche->getPioche().piocher("Tactique", j);
                }
            }

            j.addTactiquesJouees();
            return true;
        } else {
            std::cout << std::endl << "\t\tErreur - La borne n'existe pas ou est pleine !" << std::endl;
            return false;
        }
    }else{
        std::cout << std::endl << "\t\tErreur - Vous ne pouvez jouer qu'une carte tactique de plus que l'adversaire !" << std::endl;
        return false;
    }
}

bool Tactique::jouerBanshee(Manche* manche, Joueur& j, Jeu* jeu){
    if((j.getId() == 1 && jeu->getJoueur2().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees()) || (j.getId() == 2 && jeu->getJoueur1().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees())) {
        unsigned int choiceBorne = 0;

        std::cout << std::endl << std::endl << "\t2 - Sélectionnez une borne pour prendre la carte (n°) : ";
        std::cin >> choiceBorne;
        if (manche->getBornes().size() >= choiceBorne && choiceBorne != 0 &&
            manche->getBornes()[choiceBorne - 1]->estPleine(j) == false && manche->getBornes()[choiceBorne - 1]->getGagnant() ==
                                                                           nullptr) {

            unsigned int choiceCarte = 0;
            std::cout<<std::endl<<"\t3 - Sélectionnez la carte à supprimer (n°) : ";
            std::cin>>choiceCarte;
            if(j.getId() == 1){
                if(manche->getBornes()[choiceBorne - 1]->getCartesJoueur2().size() < choiceCarte || choiceCarte == 0){
                    std::cout<<std::endl<<"\t\tErreur - La carte n'existe pas !"<<std::endl;
                    return false;
                }
            }else{
                if(manche->getBornes()[choiceBorne - 1]->getCartesJoueur1().size() < choiceCarte || choiceCarte == 0){
                    std::cout<<std::endl<<"\t\tErreur - La carte n'existe pas !"<<std::endl;
                    return false;
                }
            }

                Carte* banshee;
                for (Carte *card: j.getCartes()) {
                    if(card->getType() == "Tactique" && card->getNom() == TypeTactique::banshee){
                        banshee = card;
                    }
                }
                j.supprimerCarte(banshee);

                if(j.getId() == 1){
                    manche->getBornes()[choiceBorne - 1]->retirerCarte(jeu->getJoueur2(), manche->getBornes()[choiceBorne - 1]->getCartesJoueur2()[choiceCarte-1]);
                }else{
                    manche->getBornes()[choiceBorne - 1]->retirerCarte(jeu->getJoueur1(), manche->getBornes()[choiceBorne - 1]->getCartesJoueur1()[choiceCarte-1]);
                }




            if (jeu->getModeDeJeu() == Mode::normal) {
                manche->getPioche().piocher("Clan", j);
            } else {
                int choicePioche = 0;
                while (choicePioche != 1 && choicePioche != 2) {
                    std::cout << std::endl << "\t4 - Piocher carte (1 : Clan, 2 : Tactique) : ";
                    std::cin >> choicePioche;
                }
                if (choicePioche == 1) {
                    manche->getPioche().piocher("Clan", j);
                } else {
                    manche->getPioche().piocher("Tactique", j);
                }
            }

            j.addTactiquesJouees();
            return true;
        } else {
            std::cout << std::endl << "\t\tErreur - La borne n'existe pas ou est pleine !" << std::endl;
            return false;
        }
    }else{
        std::cout << std::endl << "\t\tErreur - Vous ne pouvez jouer qu'une carte tactique de plus que l'adversaire !" << std::endl;
        return false;
    }
}

bool Tactique::jouerTraitre(Manche* manche, Joueur& j, Jeu* jeu){
    if((j.getId() == 1 && jeu->getJoueur2().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees()) || (j.getId() == 2 && jeu->getJoueur1().getNbTactiquesJouees()+1 > j.getNbTactiquesJouees())) {
        unsigned int choiceBorne = 0;

        std::cout << std::endl << std::endl << "\t2 - Sélectionnez une borne pour prendre la carte (n°) : ";
        std::cin >> choiceBorne;
        if (manche->getBornes().size() >= choiceBorne && choiceBorne != 0 &&
            manche->getBornes()[choiceBorne - 1]->estPleine(j) == false && manche->getBornes()[choiceBorne - 1]->getGagnant() ==
                                                                           nullptr) {

            unsigned int choiceCarte = 0;
            std::cout<<std::endl<<"\t3 - Sélectionnez la carte à déplacer (n°) : ";
            std::cin>>choiceCarte;
            if(j.getId() == 1){
                if(manche->getBornes()[choiceBorne - 1]->getCartesJoueur2().size() < choiceCarte || choiceCarte == 0){
                    std::cout<<std::endl<<"\t\tErreur - La carte n'existe pas !"<<std::endl;
                    return false;
                }
            }else{
                if(manche->getBornes()[choiceBorne - 1]->getCartesJoueur1().size() < choiceCarte || choiceCarte == 0){
                    std::cout<<std::endl<<"\t\tErreur - La carte n'existe pas !"<<std::endl;
                    return false;
                }
            }

                unsigned int choiceBorneDestination = 0;

                std::cout << std::endl << std::endl << "\t4 - Sélectionnez une borne de destination (n°) : ";
                std::cin >> choiceBorneDestination;
                if (manche->getBornes().size() >= choiceBorneDestination && choiceBorneDestination != 0 &&
                    manche->getBornes()[choiceBorneDestination - 1]->estPleine(j) == false && manche->getBornes()[choiceBorneDestination - 1]->getGagnant() ==
                                                                                              nullptr) {
                    Carte* traitre;
                    for (Carte *card: j.getCartes()) {
                        if(card->getType() == "Tactique" && card->getNom() == TypeTactique::traitre){
                            traitre = card;
                        }
                    }
                    j.supprimerCarte(traitre);

                    Carte* carteDeplace;
                    if(j.getId() == 1){
                        carteDeplace = manche->getBornes()[choiceBorne - 1]->getCartesJoueur2()[choiceCarte-1];
                        manche->getBornes()[choiceBorne - 1]->retirerCarte(jeu->getJoueur2(), carteDeplace);
                        manche->getBornes()[choiceBorneDestination - 1]->changerCarte(j, carteDeplace);
                    }else{
                        carteDeplace = manche->getBornes()[choiceBorne - 1]->getCartesJoueur1()[choiceCarte-1];
                        manche->getBornes()[choiceBorne - 1]->retirerCarte(jeu->getJoueur1(), carteDeplace);
                        manche->getBornes()[choiceBorneDestination - 1]->changerCarte(j, carteDeplace);
                    }

                }else{
                    std::cout << std::endl << "\t\tErreur - La borne n'existe pas ou est pleine !" << std::endl;
                    return false;
                }



            if (jeu->getModeDeJeu() == Mode::normal) {
                manche->getPioche().piocher("Clan", j);
            } else {
                int choicePioche = 0;
                while (choicePioche != 1 && choicePioche != 2) {
                    std::cout << std::endl << "\t5 - Piocher carte (1 : Clan, 2 : Tactique) : ";
                    std::cin >> choicePioche;
                }
                if (choicePioche == 1) {
                    manche->getPioche().piocher("Clan", j);
                } else {
                    manche->getPioche().piocher("Tactique", j);
                }
            }

            j.addTactiquesJouees();
            return true;
        } else {
            std::cout << std::endl << "\t\tErreur - La borne n'existe pas ou est pleine !" << std::endl;
            return false;
        }
    }else{
        std::cout << std::endl << "\t\tErreur - Vous ne pouvez jouer qu'une carte tactique de plus que l'adversaire !" << std::endl;
        return false;
    }
}
