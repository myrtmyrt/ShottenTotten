//
// Created by Arman Saint-Marc on 06/05/2023.
//

#ifndef CARTE
#define CARTE

#include <iostream>
#include <unordered_map>
#include <functional>
#include <stdio.h>
#include <string.h>

class Joueur;
class Borne;

enum class Couleur { rouge, bleu, vert, violet, orange, jaune};
enum class Nombre { un=1, deux=2, trois=3, quatre=4, cinq=5, six=6, sept=7, huit=8, neuf=9};
enum class TypeTactique{joker,espion,porteBouclier,colinMaillard,combatBoue,chasseurTete,stratege,banshee,traitre};

// conversion d'une caractéristique en string
std::string toString(Couleur c);
std::string toString(Nombre v);
std::string toString(TypeTactique v);

// écriture d'une caractéristique sur un flux ostream
std::ostream& operator<<(std::ostream& f, Couleur c);
std::ostream& operator<<(std::ostream& f, Nombre v);

void printTextInColor(Couleur color, Nombre numero);

void printTactique(TypeTactique v);

typedef void (*jouerFonction)(Joueur&, Borne*);

// Abstract base class for cards
class Carte {

public:
    virtual void jouer(Joueur& j, Borne* b) = 0;
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
    Clan(Nombre numero, Couleur couleur) : Carte(), _numero(numero), _couleur(couleur) {};
    void jouer(Joueur& j, Borne* b) override {
        std::cout << "Playing an attack card." << std::endl;
    }

    std::string getType() override {
        return "Clan";
    }

    void afficher() override{
        printTextInColor(_couleur, _numero);
    }

    TypeTactique getNom() override {
        std::cout<<"Impossible car c'est une carte clan";
    };

    Nombre getNombre() override {
        return _numero;
    };

    Couleur getCouleur() override {
        return _couleur;
    };


};

class Tactique : public Carte {
    TypeTactique _type;
    jouerFonction _function;
public:
    Tactique(TypeTactique type, jouerFonction function):Carte(),_type(type),_function(function) {};

    static void jouerJoker(Joueur& j, Borne* b){
        std::cout << "Playing a joker defense card." << std::endl;
    }

    static void jouerEspion(Joueur& j, Borne* b){
        std::cout << "Playing a espion defense card." << std::endl;
    }


    void jouer(Joueur& j, Borne* b) override;

    std::string getType() override {
        return "Tactique";
    }

    void afficher() override{
        printTactique(_type);
    }

    TypeTactique getNom() override { return _type; }

    Nombre getNombre() override {
        std::cout<<"Tactique"<<std::endl;
    };

    Couleur getCouleur() override {
        std::cout<<"Tactique"<<std::endl;
    };
};

#endif //CARTE
