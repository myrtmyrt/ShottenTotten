//
// Created by Arman Saint-Marc on 06/05/2023.
//

#ifndef CARTE
#define CARTE

#include <iostream>

enum class Couleur { rouge, bleu, vert, violet, orange, jaune};
enum class Nombre { un=1, deux=2, trois=3, quatre=4, cinq=5, six=6, sept=7, huit=8, neuf=9};
enum class TypeTactique{joker,espion,porteBouclier,colinMaillard,combatBoue,chasseurTete,stratege,banshee,traitre};

// listes contenant les valeurs possibles pour chacune des caractéristiques
extern std::initializer_list<Couleur> Couleurs;
extern std::initializer_list<Nombre> Nombres;


// Abstract base class for cards
class Carte {

public:
    virtual void play() = 0;
};

// Concrete card classes
class Clan : public Carte {
    Nombre _numero;
    Couleur _couleur;
public:
    Clan(Nombre numero, Couleur couleur) : Carte(), _numero(numero), _couleur(couleur) {};
    void play() override {
        std::cout << "Playing an attack card." << std::endl;
    }
};

class Tactique : public Carte {
    TypeTactique type;
    void (*effet)();
public:
    Tactique(TypeTactique type,void(*e)()):Carte(),type(type),effet(e) {};

    static void jouerJoker(){
        std::cout << "Playing a joker defense card." << std::endl;
    }

    static void jouerEspion(){
        std::cout << "Playing a espion defense card." << std::endl;
    }

    void play() override {
        effet();
    }
};




#endif //CARTE
