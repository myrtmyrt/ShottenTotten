#include "carte.h"
#include "joueur.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class ErreurBorne {
public:
    ErreurBorne(const string &i) : info(i) {}

    string getErreurBorne() const { return info; }

private:
    string info;
};

class Borne {
private:
    size_t _numero;
    Joueur *_gagnant;
    size_t _nbCartesMax = 3;
    vector<Carte *> _cartesJoueur1;
    vector<Carte *> _cartesJoueur2;

public:
    //GETTERS
    vector<Carte*> getCartesJoueur1() const { return _cartesJoueur1; }

    vector<Carte*> getCartesJoueur2() const { return _cartesJoueur2; }

    Joueur &getGagnant() const { return *_gagnant; }

    //SETTERS
    void setGagnant(Joueur *j) { _gagnant = j; }
    void setNbCartesMax(unsigned int n){_nbCartesMax=n;};

    //Contructeur, destructeur, recopie par défaut
    Borne(size_t numero) : _gagnant(nullptr), _numero(numero) {}

    ~Borne() { delete _gagnant; }
    //ICI CONSTRUCTEUR RECOPIE...

    //Ajouter/Retirer une carte
    void poserCarte(Joueur &j, Carte *c);

    void retirerCarte(Joueur &j, Carte *c);

    //Afficher une borne
    void afficherBorne() const;

    void revendiquer();
};


string toString(Nombre v);

ostream &operator<<(ostream &f, Nombre v);