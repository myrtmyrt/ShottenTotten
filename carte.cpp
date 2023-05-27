//
// Created by Myrtille Knockaert on 26/04/2023.
//

#include "carte.h"
#include "borne.h"

using namespace std;

string toString(Couleur c) {
    switch (c) {
        case Couleur::Rouge:
            return "R";
        case Couleur::Violet:
            return "Vi";
        case Couleur::Vert:
            return "V";
        case Couleur::Bleu:
            return "B";
        case Couleur::Orange:
            return "O";
        case Couleur::Jaune:
            return "J";
        default:
            throw CarteException("Couleur inconnue");
    }
}

string toString(Nombre v) {
    switch (v) {
        case Nombre::Un:
            return "1";
        case Nombre::Deux:
            return "2";
        case Nombre::Trois:
            return "3";
        case Nombre::Quatre:
            return "4";
        case Nombre::Cinq:
            return "5";
        case Nombre::Six:
            return "6";
        case Nombre::Sept:
            return "7";
        case Nombre::Huit:
            return "8";
        case Nombre::Neuf:
            return "9";
        default:
            throw CarteException("Nombre inconnue");
    }
}

ostream &operator<<(std::ostream &f, Couleur c) {
    f << toString(c);
    return f;
}

ostream &operator<<(std::ostream &f, Nombre v) {
    f << toString(v);
    return f;
}

void jouerJoker(Joueur &j, Borne *b,Tactique* joker) {
    Couleur c;
    Nombre n;
    cout << "Donne la couleur de la carte désirée : " << endl;
    cout << "Rouge(1),Bleu(2), Vert(3), Violet(4), Orange(5), Jaune(6)" << endl;
    int couleurInput;
    cin >> couleurInput;

    // on convertit le nombre en la couleur correspondante dans l'enum
    switch (couleurInput) {
        case 1:
            c = Couleur::Rouge;
            break;
        case 2:
            c = Couleur::Bleu;
            break;
        case 3:
            c = Couleur::Vert;
            break;
        case 4:
            c = Couleur::Violet;
            break;
        case 5:
            c = Couleur::Orange;
            break;
        case 6:
            c = Couleur::Jaune;
            break;
        default:
            cout << "Couleur invalide !" << endl;
    }
    cout << "Donne la nombre en chiffre de la carte désirée (allant de 1 à 9): " << endl;
    int nombreInput;
    cin >> nombreInput;

    // on convertit le nombre avec le nombre correspondant dans l'enum
    switch (nombreInput) {
        case 1:
            n = Nombre::Un;
            break;
        case 2:
            n = Nombre::Deux;
            break;
        case 3:
            n = Nombre::Trois;
            break;
        case 4:
            n = Nombre::Quatre;
            break;
        case 5:
            n = Nombre::Cinq;
            break;
        case 6:
            n = Nombre::Six;
            break;
        case 7:
            n = Nombre::Sept;
            break;
        case 8:
            n = Nombre::Huit;
            break;
        case 9:
            n = Nombre::Neuf;
            break;
        default:
            cout << "Nombre invalide !" << endl;
    }
    if (j.getId() == 1) {
        auto posJoker = find(b->getCartesJoueur1().begin(), b->getCartesJoueur1().end(), joker);
        b->getCartesJoueur1().erase(posJoker);
    } else {
        auto posJoker= find(b->getCartesJoueur2().begin(), b->getCartesJoueur2().end(), joker);
        b->getCartesJoueur2().erase(posJoker);
    }
    Clan *newCarte = new Clan(n, c);
    b->poserCarte(j, newCarte);
}


void Tactique::jouerEspion(Joueur &j, Borne *b, Tactique *espion) {
    Couleur c;
    Nombre n = Nombre::Sept;
    // On récupère la couleur de la carte que le joueur choisi
    cout << "Donne la couleur de la carte désirée : " << endl;
    cout << "Rouge(1),Bleu(2), Vert(3), Violet(4), Orange(5), Jaune(6)" << endl;
    int couleurInput;
    cin >> couleurInput;

    // on convertit le nombre en la couleur correspondante dans l'enum
    switch (couleurInput) {
        case 1:
            c = Couleur::Rouge;
            break;
        case 2:
            c = Couleur::Bleu;
            break;
        case 3:
            c = Couleur::Vert;
            break;
        case 4:
            c = Couleur::Violet;
            break;
        case 5:
            c = Couleur::Orange;
            break;
        case 6:
            c = Couleur::Jaune;
            break;
        default:
            cout << "Couleur invalide !" << endl;
    }
    //On récupère le chiffre désiré par le joueur pour la carte

    cout << "Donne la nombre en chiffre de la carte désirée (allant de 1 à 9): " << endl;
    int nombreInput;
    cin >> nombreInput;
    if (j.getId() == 1) {
        auto posEspion = find(b->getCartesJoueur1().begin(), b->getCartesJoueur1().end(), espion);
        b->getCartesJoueur1().erase(posEspion);
    } else {
        auto posEspion = find(b->getCartesJoueur2().begin(), b->getCartesJoueur2().end(), espion);
        b->getCartesJoueur2().erase(posEspion);
    }
    Clan *newCarte = new Clan(n, c);
    b->poserCarte(j, newCarte);

};

void Tactique::jouerPorteBouclier(Joueur &j, Borne *b, Tactique* porteBouclier) {
    Couleur c;
    Nombre n;
    cout << "Donne la couleur de la carte désirée : " << endl;
    cout << "Rouge(1),Bleu(2), Vert(3), Violet(4), Orange(5), Jaune(6)" << endl;
    int couleurInput;
    cin >> couleurInput;

    // on convertit le nombre en la couleur correspondante dans l'enum
    switch (couleurInput) {
        case 1:
            c = Couleur::Rouge;
            break;
        case 2:
            c = Couleur::Bleu;
            break;
        case 3:
            c = Couleur::Vert;
            break;
        case 4:
            c = Couleur::Violet;
            break;
        case 5:
            c = Couleur::Orange;
            break;
        case 6:
            c = Couleur::Jaune;
            break;
        default:
            cout << "Couleur invalide !" << endl;
    }
    cout << "Donne la nombre en chiffre de la carte désirée (allant de 1 à 3): " << endl;
    int nombreInput;
    cin >> nombreInput;

    // on convertit le nombre avec le nombre correspondant dans l'enum
    switch (nombreInput) {
        case 1:
            n = Nombre::Un;
            break;
        case 2:
            n = Nombre::Deux;
            break;
        case 3:
            n = Nombre::Trois;
            break;
        default:
            cout << "Nombre invalide !" << endl;
    }

    if (j.getId() == 1) {
        auto posPorteBouclier = find(b->getCartesJoueur1().begin(), b->getCartesJoueur1().end(), porteBouclier);
        b->getCartesJoueur1().erase(posPorteBouclier);
    } else {
        auto posPorteBouclier = find(b->getCartesJoueur2().begin(), b->getCartesJoueur2().end(), porteBouclier);
        b->getCartesJoueur2().erase(posPorteBouclier);
    }

    Clan* newCarte = new Clan(n, c);
    b->poserCarte(j, newCarte);
}


void jouerCombatDeBoue(Borne *b) {
    b->setNbCartesMax(4);
}

void effetChasseurdeTete(Pioche p) {
    for (int i = 0; i < 2; i++) {
        Carte* c = new Carte();
        p.piocher();
    }
    cout << "il faut choisir une carte à supprimer"

}

Carte effetStratege() {

}

Carte effetBanshee(Joueur &adversaire, Borne *borneAdversaire, Carte *c) {
    borneAdversaire->retirerCarte(adversaire, c);
}

Carte effetTraitre(Borne *borneAdversaire, Borne *b, Carte *c, Joueur &j, Joueur &adversaire) {
    //vérifier que la carte est bien une carte clan
    b->poserCarte(j, c);
    borneAdversaire->retirerCarte(adversaire, c);
}


void printTextInColor(Couleur color, Nombre numero) {
    switch (color) {
        case Couleur::Rouge:
            std::cout << "\033[31m"; // Set text color to red
            break;
        case Couleur::Vert:
            std::cout << "\033[32m"; // Set text color to green
            break;
        case Couleur::Bleu:
            std::cout << "\033[34m"; // Set text color to blue
            break;
        case Couleur::Violet:
            std::cout << "\033[35m"; // Set text color to blue
            break;
        case Couleur::Orange:
            std::cout << "\033[33m"; // Set text color to blue
            break;
        case Couleur::Jaune:
            std::cout << "\033[93m"; // Set text color to blue
            break;
        default:
            break;
    }

    std::cout << "[" << numero << "]" << "\033[0m"; // Reset text color to default
}



