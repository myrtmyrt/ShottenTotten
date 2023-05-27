//
// Created by Myrtille Knockaert on 26/04/2023.
//

#ifndef BORNE
#define BORNE

#include <iostream>
#include <string>
#include "carte.h"
#include "joueur.h"

using namespace std;

class Borne {
private:
    size_t _numero;
    size_t _nbCartesMax;
    vector<Carte*> _cartesJoueur1;
    vector<Carte*> _cartesJoueur2;
    Joueur* _gagnant;
public:
    //GETTERS
    vector<Carte*> getCartesJoueur1() const { return _cartesJoueur1; }
    vector<Carte*> getCartesJoueur2() const { return _cartesJoueur2; }
    Joueur& getGagnant() const { return *_gagnant; }

    //SETTERS
    void setGagnant(Joueur* j) { _gagnant = j; }
    void setNbCartesMax(Joueur* j) { _gagnant = j; }

    //Contructeur, destructeur, recopie par défaut
    Borne(size_t numero) : _gagnant(nullptr), _nbCartesMax(3), _numero(numero){}
    ~Borne() { delete _gagnant; }
    //ICI CONSTRUCTEUR RECOPIE...


    //Ajouter/Retirer une carte
    void poserCarte(Joueur& j, Carte* c);
    void retirerCarte(Joueur& j, Carte* c);

    //Afficher une borne
    void afficherBorne() const;
    //void revendiquerBorne();
};


#endif //BORNE
