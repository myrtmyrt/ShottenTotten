//
// Created by Arman Saint-Marc on 14/05/2023.
//

#ifndef JOUEUR
#define JOUEUR

#include <iostream>
#include <string>
#include <vector>

#include "carte.h"

using namespace std;

class Joueur {
private:
    unsigned int _id;
    vector<Carte*> _cartes;
    string _pseudo;
    bool _bot;
    unsigned int _nbTactiquesJouees;
    unsigned int _victoires;

public:
    //GETTERS
    unsigned int getId() const { return _id; }
    vector<Carte*> getCartes() const { return _cartes; }
    string getPseudo() const { return _pseudo; }
    bool getIsBot() const { return _bot; }
    unsigned int getNbTactiquesJouees() const { return _nbTactiquesJouees; }
    unsigned int getVictoires() const { return _victoires; }

    //SETTERS
    void addPoint() { _victoires++; }
    void addTactiquesJouees() { _nbTactiquesJouees++; }
    void addCarte(Carte* carte){ _cartes.push_back(carte); }
    void supprimerCarte(unsigned int position){_cartes.erase(_cartes.begin()+position);}
    void resetTactiquesJouees() {_nbTactiquesJouees = 0; }
    void resetCartes() { _cartes.clear(); }


    Joueur(unsigned int id, bool bot, std::string pseudo) : _id(id), _pseudo(pseudo), _bot(bot), _nbTactiquesJouees(0), _victoires(0){};
    ~Joueur() = default;

    void afficherCartes() const;
    bool contientCombatDeBoue(){
        for (unsigned int i = 0; i < _cartes.size(); i++) {
            if (_cartes[i]->getType()=="Tactique") {
                if (_cartes[i])
            }
        }
    }
};

#endif //JOUEUR
