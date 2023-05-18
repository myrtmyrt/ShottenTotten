#include "Carte.h"
#include <iostream>
#include <string>

using namespace std;


class ErreurBorne {
public:
	ErreurBorne(const string& i) :info(i) {}
	string getErreurBorne() const { return info; }
private:
	string info;
};

class Borne {
private:
    bool _gagne;
    size_t _nb_cartesMax=3;
    size_t _nb_cartes1=0;
    size_t _nb_cartes2=0;
	const Carte** liste_carte1 = nullptr;
	const Carte** liste_carte2 = nullptr;

public:
	int getGagne() const { return _gagne; }
	int getNbMax() const { return _nb_cartes; }

	//On pourrait avoir 0 cartes au d��but
	Borne() :_gagne(0){};
	~Borne() {
		delete[] liste_carte1;
		delete[] liste_carte2;
	}
	Borne(const Borne&) = delete;
	Borne& operator=(const Borne& p) = delete;

	void poser (const Carte& c);
	void retirer(const Carte& c);
};

string toString(Nombre v);
ostream& operator<<(ostream& f, Nombre v);