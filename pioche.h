//
// Created by Myrtille Knockaert on 26/04/2023.
//

#ifndef PROJET_PIOCHE_H
#define PROJET_PIOCHE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#include "carte.h"

using namespace std;

class StrategiePioche{
protected:
    const size_t _nbCartes;
    vector<Carte*> _Cartes;
public:
    StrategiePioche(vector <Carte*> c):_Cartes(c),_nbCartes(64){}

    StrategiePioche() {};
    size_t getNbMax()const { return _nbCartes;}
    virtual size_t getNbcarte() const { return _Cartes.size();}
    virtual bool estVide() const=0;
    virtual Carte* piocher() =0;
};


class StrategiePiocheClan: public StrategiePioche{
private:
public:
    //méthodes

    bool estVide() const override{ return _Cartes.size() == 0;}
    Carte* piocher() override{
    shuffle(begin(_Cartes), end(_Cartes), default_random_engine());
    Carte* cartePioche= new Carte;
    cartePioche= _Cartes.back();
    _Cartes.pop_back();
    return cartePioche;
    };
};

class StategiePiocheTactique:public StrategiePioche{
private:
public:

};

class Contexte{
    StrategiePioche* maStrategie;
public:
    void executeEstVide(){maStrategie->estVide();}
    void executePiocher(){maStrategie->piocher();}
    void setStrategie(StrategiePioche* s){maStrategie;}
};

//Couleur CouleursPossibles[6]={Couleur::rouge, Couleur::bleu, Couleur::vert, Couleur::violet,Couleur::orange, Couleur::jaune};
//        Nombre NombresPossibles[9]={Nombre::un,Nombre::deux,Nombre::trois,Nombre::quatre,Nombre::cinq,Nombre::six,Nombre::sept,Nombre::huit,Nombre::neuf};
//        for (int i = 0; i < 6; i++) {
//            for (int j = 0; j < 9; j++) {
//                auto* newCarte = new CarteClan(CouleursPossibles[i],NombresPossibles[j]);
//                Cartes.push_back(newCarte);
//            }
//        }
#endif //PROJET_PIOCHE_H
