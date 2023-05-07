//
// Created by Myrtille Knockaert on 26/04/2023.
//

#include <iostream>
#include "carte.h"

string toString(Couleur c) {
    switch (c) {
        case Couleur::rouge: return "R";
        case Couleur::violet: return "Vi";
        case Couleur::vert: return "V";
        case Couleur::bleu: return "B";
        case Couleur::orange: return "O";
        case Couleur::jaune: return "J";
        default: throw CarteException("Couleur inconnue");
    }
}

string toString(Nombre v) {
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