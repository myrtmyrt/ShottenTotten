//
// Created by Myrtille Knockaert on 26/04/2023.
//

#ifndef PROJET_CARTE_H
#define PROJET_CARTE_H

#include <iostream>
#include "carte.h"
#include "borne.h"
#include "pioche.h"
#include "manche.h"

using namespace std;

enum class Couleur {
    Rouge, Bleu, Vert, Violet, Orange, Jaune
};
enum class Nombre {
    Un = 1, Deux = 2, Trois = 3, Quatre = 4, Cinq = 5, Six = 6, Sept = 7, Huit = 8, Neuf = 9
};
enum class TypeTactique {
    Joker, Espion, PorteBouclier, ColinMaillard, CombatBoue, ChasseurTete, Stratege, Banshee, Traitre
};

//// conversion d'une caractéristique en string
//string toString(Couleur c);

string toString(Nombre v);

//// écriture d'une caractéristique sur un flux ostream
//ostream &operator<<(ostream &f, Couleur c);

ostream &operator<<(ostream &f, Nombre v);


void printTextInColor(Couleur color, Nombre numero);

//// listes contenant les valeurs possibles pour chacune des caractéristiques
//extern std::initializer_list<Couleur> Couleurs;
//extern std::initializer_list<Nombre> Nombres;

// classe pour gérer les exceptions
class CarteException {
public:
    CarteException(const string &i) : info(i) {}

    string getInfo() const { return info; }

private:
    string info;
};

class Carte{
public:
    // Opérateur d'affectation
    Carte &operator=(const Carte &c) = default; // optionnel
    virtual void jouer() = 0;

    virtual void afficher() = 0;

    virtual std::string getType() = 0;
    virtual TypeTactique getNom()=0;
    virtual Nombre getNombre() = 0;
    virtual Couleur getCouleur() = 0;

};

// Concrete card classes
class Clan : public Carte {
    Nombre _numero;
    Couleur _couleur;
public:
    //Constructeur
    Clan(Nombre numero, Couleur couleur) : Carte(), _numero(numero), _couleur(couleur) {};

    // Destructeur
    ~Clan() = default; // optionnel
    // Constructeur par recopie
    Clan(const Clan &c) = default; // optionnel
    void jouer() override {
        std::cout << "Playing an attack card." << std::endl;
    }

    std::string getType() override {
        return "Clan";
    }

    Nombre getNombre() override {
        return _numero;
    };

    Couleur getCouleur() override {
        return _couleur;
    };

    void afficher() override {
        printTextInColor(_couleur, _numero);
    }
    TypeTactique getNom() override {
        cout<<"Impossible car c'est une carte clan";
    };
};

class Tactique : public Carte {
    TypeTactique type;

    void (*effet)();

public:
    Tactique(TypeTactique type, void(*e)()) : Carte(), type(type), effet(e) {};

    TypeTactique getNom() const { return type; }


    void jouerJoker(Joueur &j, Borne *b,Tactique* joker);

    void jouerEspion(Joueur &j, Borne *b, Tactique *espion);

    void jouerPorteBouclier(Joueur &j, Borne *b, Tactique* porteBouclier);

    void jouerCombatDeBoue(Borne *b);

    void jouerChasseurDeTete(Joueur& j, Pioche p,Borne* b,string t);

    void jouerStratege(Joueur& j, Pioche p,Manche* m,string t);

    void jouerBanshee(Joueur &j, Manche* m);

    void jouerTraitre(Joueur &j,Manche* m);

    void jouer() override {
        effet();
    }

    std::string getType() override {
        return "Tactique";
    }

    Nombre getNombre() override {
        std::cout<<"Tactique"<<std::endl;
    };

    Couleur getCouleur() override {
        std::cout<<"Tactique"<<std::endl;
    };


    void afficher() override {
        std::cout << "Tactique" << std::endl;
    }
};

#endif //PROJET_CARTE_H
