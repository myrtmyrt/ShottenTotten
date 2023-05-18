//
// Created by Myrtille Knockaert on 26/04/2023.
//

#include <iostream>
#include "carte.h"

string toString(Couleur c) {
    switch (c) {
        case Couleur::Rouge: return "R";
        case Couleur::Violet: return "Vi";
        case Couleur::Vert: return "V";
        case Couleur::Bleu: return "B";
        case Couleur::Orange: return "O";
        case Couleur::Jaune: return "J";
        default: throw CarteException("Couleur inconnue");
    }
}

string toString(Nombre v) {
    switch (v) {
        case Nombre::Un: return "1";
        case Nombre::Deux: return "2";
        case Nombre::Trois: return "3";
        case Nombre::Quatre: return "4";
        case Nombre::Cinq: return "5";
        case Nombre::Six: return "6";
        case Nombre::Sept: return "7";
        case Nombre::Huit: return "8";
        case Nombre::Neuf: return "9";
        default: throw CarteException("Nombre inconnue");
    }
}

std::ostream& operator<<(std::ostream& f, Couleur c) { f << toString(c); return f; }
std::ostream& operator<<(std::ostream& f, Nombre v) {	f << toString(v); return f; }

Carte joker(){
    Couleur c;
    Nombre n;
    cout<<"donne la couleur de la carte désirée"<<endl;
}