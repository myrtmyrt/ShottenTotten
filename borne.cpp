//
// Created by Arman Saint-Marc on 06/05/2023.
//

#include "borne.h"

void Borne::poserCarte(Joueur &j, Carte *c) {
    if (j.getId() == 1) {
        if (_cartesJoueur1.size() < _nbCartesMax) {
            _cartesJoueur1.push_back(c);

            j.supprimerCarte(c);

            if (_cartesJoueur1.size() == _nbCartesMax) {
                //revendiquerBorne();
            }
        } else throw "Attention : nombre max atteint, vous ne pouvez pas ajouter une carte.";

    } else {
        if (_cartesJoueur2.size() < _nbCartesMax) {
            _cartesJoueur2.push_back(c);

            j.supprimerCarte(c);

            if (_cartesJoueur2.size() == _nbCartesMax) {
                //revendiquerBorne();
            }
        } else throw "Attention : nombre max atteint, vous ne pouvez pas ajouter une carte.";
    }
}

void Borne::retirerCarte(Joueur &j, Carte *c) {

    if (j.getId() == 1) {
        auto it = find(_cartesJoueur1.begin(), _cartesJoueur1.end(), c);

        if (it != _cartesJoueur1.end()) {
            // La carte a été trouvée, vous pouvez maintenant la supprimer
            _cartesJoueur1.erase(it);
        } else throw "Cette carte n'est pas sur cette borne";
    }
}

void Borne::afficherCartesJ1() const{
    for (Carte* card : _cartesJoueur1) {
        card->afficher();
    }
}

void Borne::afficherCartesJ2() const{
    for (Carte* card : _cartesJoueur2) {
        card->afficher();
    }
}

void Borne::afficher() const {
    std::cout<<"\tJ1 - ";
    afficherCartesJ1();
    if(_gagnant != nullptr){
        std::cout<<"| Borne "<<_numero+1<<" (gagnée par "<<_gagnant->getPseudo()<<") | ";
    }else{
        std::cout<<"| Borne "<<_numero+1<<" | ";
    }
    afficherCartesJ2();
    std::cout<<"- J2"<<std::endl;
}

bool Borne::estPleine(Joueur &j) const {
    size_t taille;
    for (unsigned int i = 0; i < j.getCartes().size(); i++) {
        if (j.getCartes()[i].getType() == "Clan") {
            taille++;
        }
    }
    if(_nbCartesMax >= taille){

    }else{
        
    }
}