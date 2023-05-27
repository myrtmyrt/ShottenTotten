//
// Created by Arman Saint-Marc on 06/05/2023.
//

#ifndef BORNE
#define BORNE

#include <iostream>
#include <string>
#include <algorithm>

#include "carte.h"
#include "joueur.h"

int toInt(Nombre n);

class Borne {
private:
    size_t _numero;
    size_t _nbCartesMax;
    std::vector<Carte*> _cartesJoueur1;
    std::vector<Carte*> _cartesJoueur2;
    Joueur* _gagnant;
public:
    //GETTERS
    std::vector<Carte*> getCartesJoueur1() const { return _cartesJoueur1; }
    std::vector<Carte*> getCartesJoueur2() const { return _cartesJoueur2; }
    Joueur& getGagnant() const { return *_gagnant; }

    //SETTERS
    void setGagnant(Joueur* j) { _gagnant = j; }

    //Contructeur, destructeur, recopie par défaut
    Borne(size_t numero) : _gagnant(nullptr), _nbCartesMax(3), _numero(numero){}
    ~Borne() { delete _gagnant; }
    //ICI CONSTRUCTEUR RECOPIE...


    //Ajouter/Retirer une carte
    void poserCarte(Joueur& j, Carte* c);
    void retirerCarte(Joueur& j, Carte* c);

    //Afficher une borne
    void afficher() const;
    void afficherCartesJ1() const;
    void afficherCartesJ2() const;
    //void revendiquerBorne();

    bool estPleine(Joueur &j) const;

    unsigned int trouverGagnant();
    unsigned int calculerPoints(std::vector<Carte*> _cartesJoueur);

};


#endif //BORNE
