//
// Created by Myrtille Knockaert on 26/04/2023.
//

#include <iostream>
#include "carte.h"
#include "borne.h"
#include "joueur.h"
#include "pioche.h"

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

std::ostream &operator<<(std::ostream &f, Couleur c) {
    f << toString(c);
    return f;
}

std::ostream &operator<<(std::ostream &f, Nombre v) {
    f << toString(v);
    return f;
}

Carte effetJoker(Joueur &j, Borne *b) {
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
    CarteClan* joker=new CarteClan(c, n);
    b->poserCarte(j, joker);
}

Carte effetEspion(Joueur &j, Borne *b) {
    Couleur c;
    Nombre n = Nombre::Sept;
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

    CarteClan* espion= new CarteClan(c, n);
    b->poserCarte(j, espion);

};

Carte effetPorteBouclier(Joueur &j, Borne *b) {
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
    CarteClan* porteBouclier= new CarteClan(c, n);
    b->poserCarte(j, porteBouclier);
}

//Carte effetColinMaillard() {
//
//}

Carte effetCombatDeBoue(Borne *b) {
    b->setNbCartesMax(4);
}

Carte effetChasseurdeTete(vector<Carte*> p) {
    for (int i = 0; i <2; i++){
        Carte* c=new Carte;
        c=p.piocher();
    }
    cout<<"il faut choisir une carte à supprimer"

}

Carte effetStratege() {

}

Carte effetBanshee(Joueur &adversaire, Borne *borneAdversaire,Carte *c) {
    borneAdversaire->retirerCarte(adversaire,c);
}

Carte effetTraitre(Borne *borneAdversaire,Borne *b,Carte *c,Joueur &j,Joueur &adversaire) {
    //vérifier que la carte est bien une carte clan
    b->poserCarte(j,c);
    borneAdversaire->retirerCarte(adversaire,c);
}




