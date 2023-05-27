//
// Created by Arman Saint-Marc on 06/05/2023.
//

#include "carte.h"

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

std::ostream& operator<<(std::ostream& f, Couleur c) { f << toString(c); return f; }
std::ostream& operator<<(std::ostream& f, Nombre v) {	f << toString(v); return f; }

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
