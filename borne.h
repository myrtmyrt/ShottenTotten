//
// Created by Myrtille Knockaert on 26/04/2023.
//

#ifndef BORNE
#define BORNE

#include <iostream>
#include <string>
#include <algorithm>
#include "carte.h"
#include "joueur.h"

using namespace std;

class Borne {
private:
    size_t _numero;
    size_t _nbCartesMax;
    vector<Carte *> _cartesJoueur1;
    vector<Carte *> _cartesJoueur2;
    Joueur *_gagnant;
public:
    //GETTERS
    vector<Carte *> getCartesJoueur1() const { return _cartesJoueur1; }

    vector<Carte *> getCartesJoueur2() const { return _cartesJoueur2; }

    Joueur &getGagnant() const { return *_gagnant; }

    //SETTERS
    void setGagnant(Joueur *j) { _gagnant = j; }

    void setNbCartesMax(size_t t) { _nbCartesMax = t; }

    //Contructeur, destructeur, recopie par défaut
    Borne(size_t numero) : _gagnant(nullptr), _nbCartesMax(3), _numero(numero) {}

    ~Borne() { delete _gagnant; }
    //ICI CONSTRUCTEUR RECOPIE...

    bool estPleine(Joueur &j) {
        size_t taille;
        for (unsigned int i = 0; i < j.getCartes().size(); i++) {
            if (j.getCartes()[i].getType() == "Clan") {
                taille++;
            }
        }
        if (j.getCartes().contientCombatDeBoue()==true){
            if(taille>=4){
                return true;
            } else{
                return false;
            }
        }else
        {
            if(taille>=3){
                return true;
            } else{
                return false;
            }
        }
    }


    //Ajouter/Retirer une carte
    void poserCarte(Joueur &j, Carte *c);

    void retirerCarte(Joueur &j, Carte *c);

    //Afficher une borne
    void afficherBorne() const;
    //void revendiquerBorne();

};


#endif //BORNE
