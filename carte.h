//
// Created by Myrtille Knockaert on 26/04/2023.
//

#ifndef PROJET_CARTE_H
#define PROJET_CARTE_H

using namespace std;

enum class Couleur {Rouge,Bleu, Vert, Violet, Orange, Jaune};
enum class Nombre {Un=1, Deux=2, Trois=3, Quatre=4, Cinq=5, Six=6, Sept=7, Huit=8, Neuf=9};
enum class TypeTactique{Joker,Espion,PorteBouclier,ColinMaillard,CombatBoue,ChasseurTete,Stratege,Banshee,Traitre};

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

// classe pour gérer les exceptions
class CarteException {
public:
    CarteException(const string& i) :info(i) {}
    string getInfo() const { return info; }
private:
    string info;
};

class Carte{
public:
    virtual void afficher();
};

class CarteClan: public Carte{
private:
    // Un attribut par caractéristique
    // On utilise les types enum
    Couleur couleur;
    Nombre nombre;
public:
    // Accesseurs en lecture
    Couleur getCouleur() const { return couleur;}
    Nombre getNombre() const { return nombre; }
    void afficher() override{
       cout<<(couleur)<<endl;
       cout<<(nombre)<<endl;
    }
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
    void afficher() override{
        cout<<("bonjour")<<endl;
    }
};

Carte effetJoker();
Carte effetEspion();


#endif //PROJET_CARTE_H
