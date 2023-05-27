//
// Created by Myrtille Knockaert on 26/04/2023.
//

#ifndef PROJET_CARTE_H
#define PROJET_CARTE_H

#include <iostream>
#include <cstdio>
#include <string>
//#include "borne.h"

using namespace std;

class Manche;
class Pioche;
class Borne;
class Joueur;

enum class Couleur {
    Rouge, Bleu, Vert, Violet, Orange, Jaune
};
enum class Nombre {
    Un = 1, Deux = 2, Trois = 3, Quatre = 4, Cinq = 5, Six = 6, Sept = 7, Huit = 8, Neuf = 9
};
enum class TypeTactique {
    Joker, Espion, PorteBouclier, ColinMaillard, CombatBoue, ChasseurTete, Stratege, Banshee, Traitre
};

// conversion d'une caractéristique en string
std::string toString(Couleur c);
std::string toString(Nombre v);

// écriture d'une caractéristique sur un flux ostream
std::ostream& operator<<(std::ostream& f, Couleur c);
std::ostream& operator<<(std::ostream& f, Nombre v);

void printTextInColor(Couleur color, Nombre numero);

// listes contenant les valeurs possibles pour chacune des caractéristiques
extern std::initializer_list<Couleur> Couleurs;
extern std::initializer_list<Nombre> Nombres;

// classe pour gérer les exceptions
class CarteException {
public:
    CarteException(const string &i) : info(i) {}

    string getInfo() const { return info; }

private:
    string info;
};

class Carte {
public:
    // Opérateur d'affectation
    Carte &operator=(const Carte &c) = default; // optionnel
    virtual void jouer() = 0;

    virtual void afficher() = 0;

    virtual std::string getType() = 0;

    virtual TypeTactique getNom() = 0;

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
        cout << "Impossible car c'est une carte clan";
    };
};

class Tactique : public Carte {
    TypeTactique type;

    void (*effet)();

public:
    Tactique(TypeTactique type, void(*e)()) : Carte(), type(type), effet(e) {};

    TypeTactique getNom() const { return type; }

    static void jouerJoker(Joueur &j, Borne *b,Tactique* joker);

    static void jouerEspion(Joueur &j, Borne *b, Tactique *espion);

    static void jouerPorteBouclier(Joueur &j, Borne *b, Tactique *porteBouclier);

    static void jouerColinMaillard(){};

    static void jouerCombatBoue(Borne *b);

    static void jouerChasseurTete(Joueur &j, Pioche p, Borne *b, string t);

    static void jouerStratege(Joueur &j, Pioche p, Manche *m, string t);

    static void jouerBanshee(Joueur &j, Manche *m);

    static void jouerTraitre(Joueur &j,Manche* m);

    void jouer() override {
        effet();
    }

    std::string getType() override {
        return "Tactique";
    }

    Nombre getNombre() override {
        std::cout << "Tactique" << std::endl;
    };

    Couleur getCouleur() override {
        std::cout << "Tactique" << std::endl;
    };


    void afficher() override {
        std::cout << "Tactique" << std::endl;
    }
};

#endif //PROJET_CARTE_H
