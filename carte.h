//
// Created by Myrtille Knockaert on 26/04/2023.
//

#ifndef PROJET_CARTE_H
#define PROJET_CARTE_H

using namespace std;

// classe pour gérer les exceptions
class CarteException {
public:
    CarteException(const string& i) :info(i) {}
    string getInfo() const { return info; }
private:
    string info;
};

enum class Couleur { rouge, bleu, vert, violet, orange, jaune};
enum class Nombre { un=1, deux=2, trois=3, quatre=4, cinq=5, six=6, sept=7, huit=8, neuf=9};
enum class TypeTactique{joker,espion,porteBouclier,colinMaillard,combatBoue,chasseurTete,stratege,banshee,traitre};

class Carte{

};

class CarteClan: Carte{
private:
    // Un attribut par caractéristique
    // On utilise les types enum
    Couleur couleur;
    Nombre nombre;
public:
    // Accesseurs en lecture
    Couleur getCouleur() const { return couleur;}
    Nombre getNombre() const { return nombre; }

    // Constructeur à 2 paramètres
    CarteClan(Couleur c, Nombre n) : couleur(c), nombre(n){};
    // Destructeur
    ~CarteClan() = default; // optionnel
    // Constructeur par recopie
    CarteClan(const CarteClan& c) = default; // optionnel
    // Opérateur d'affectation
    CarteClan& operator=(const CarteClan& c) = default; // optionnel
};

class CarteTactique: Carte{
private:
    TypeTactique type;
    void (*effet)();
public:
    CarteTactique(TypeTactique t,void(*e)()):type(t),effet(e){};
    void execEffet(){effet();};
};


// conversion d'une caractéristique en string
string toString(Couleur c);
string toString(Nombre v);

// écriture d'une caractéristique sur un flux ostream
ostream& operator<<(ostream& f, Couleur c);
ostream& operator<<(ostream& f, Nombre v);

// listes contenant les valeurs possibles pour chacune des caractéristiques
extern std::initializer_list<Couleur> Couleurs;
extern std::initializer_list<Nombre> Nombres;

// affichage des valeurs possibles pour chaque caractéristiques
void printCouleurs(std::ostream& f = cout);
void printNombres(std::ostream& f = cout);

#endif //PROJET_CARTE_H
