//
// Created by Myrtille Knockaert on 26/04/2023.
//

#ifndef PROJET_PIOCHE_H
#define PROJET_PIOCHE_H

#include <algorithm>
#include <random>
#include <functional>
#include <iterator>
#include <string>
#include <list>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "carte.h"
#include "joueur.h"

using namespace std;

class Pioche {
private:
    vector<Carte*> _cartes;
public:

    Pioche(vector<Carte*> cartes);

    void piocher(string type, Joueur &jou);

};


//
////On utilise le design pattern stratégie
//class Pioche {
//protected:
//    const size_t _nbCartes;
//    vector<Carte*> _Cartes;
//public:
//    Pioche(vector<Carte*> c) : _Cartes(c), _nbCartes(64) {} //Constructeur
//    size_t getNbMax() const { return _nbCartes; }
//
//    virtual size_t getNbcarte() const { return _Cartes.size(); }
//
//    virtual bool estVide() const = 0;
//
//    virtual Carte* piocher() = 0;
//};
//
//
//class PiocheClan : public StrategiePioche {
//private:
//public:
//    //méthodes
//    PiocheClan(vector<Carte*> c) : StrategiePioche(c) {}; //constructeur
//    bool estVide() const override { return _Cartes.size() == 0; }
//
//    Carte* piocher() override {
//        shuffle(begin(_Cartes), end(_Cartes), default_random_engine());
//        Carte* cartePioche= new Carte;
//        cartePioche = _Cartes.back();
//        while (typeid(cartePioche) != typeid(CarteClan)) {
//            shuffle(begin(_Cartes), end(_Cartes), default_random_engine());
//            cartePioche = _Cartes.back();
//        }
//        _Cartes.pop_back();
//        return cartePioche;
//    };
//};
//
//class StrategiePiocheTactique : public StrategiePioche {
//private:
//public:
//    StrategiePiocheTactique(vector<Carte*> c) : StrategiePioche(c) {};
//
//};
//
//class Contexte {
//    Pioche *maStrategie;
//public:
//    void executeEstVide() { maStrategie->estVide(); }
//
//    void executePiocher() { maStrategie->piocher(); }
//
//    void setStrategie(Pioche *s) {maStrategie;}
//};




#endif //PROJET_PIOCHE_H
