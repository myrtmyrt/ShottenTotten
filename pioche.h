//
// Created by Myrtille Knockaert on 26/04/2023.
//

#ifndef PROJET_PIOCHE_H
#define PROJET_PIOCHE_H

#include <iostream>
#include <list>
#include "carte.h"

class Pioche{
private:
    const ::size_t nbCartesMax=54;
    list <CarteClan> Cartes;
public:
    //constructeur
    Pioche(){
        Couleur CouleursPossibles[]={Couleur::rouge, Couleur::bleu, Couleur::vert, Couleur::violet,Couleur::orange, Couleur::jaune};
        Nombre NombresPossibles[]={Nombre::un,Nombre::deux,Nombre::trois,Nombre::quatre,Nombre::cinq,Nombre::six,Nombre::sept,Nombre::huit,Nombre::neuf};
        for (int i = 0; i < sizeof(CouleursPossibles); i++) {
            for (int j = 0; j < sizeof(NombresPossibles); j++) {
                CarteClan newCarte(CouleursPossibles[i],NombresPossibles[j]);
                Cartes.insert(getNbcarte()+1,newCarte);
            }
        }
    }
    //Accesseurs en lecture
    ::size_t getNbcarte() const { return Cartes.size();}
    ::size_t getNbMax()const { return nbCartesMax;}
    //méthodes
    bool estVide() const { return Cartes.size() == 0; }
    void melanger();
    Carte piocher() const {return ::rand(Cartes);};
};

class PiocheTactique{
};

#endif //PROJET_PIOCHE_H
