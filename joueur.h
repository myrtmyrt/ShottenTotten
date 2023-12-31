//
// Created by Arman Saint-Marc on 14/05/2023.
//

#ifndef JOUEUR
#define JOUEUR

#include <iostream>
#include <string>
#include <vector>


using namespace std;

class Carte;

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
    void addCarte(Carte *carte);
    void supprimerCarte(Carte* carte);
    void resetTactiquesJouees() {_nbTactiquesJouees = 0; }
    void resetCartes() { _cartes.clear(); }


    Joueur(unsigned int id, bool bot, string pseudo) : _id(id), _pseudo(pseudo), _bot(bot), _nbTactiquesJouees(0), _victoires(0){};
    ~Joueur() = default;

    void afficherCartes() const;
    bool contientCombatDeBoue();
};

#endif //JOUEUR
