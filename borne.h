#pragma once
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
	Nombre numero;
	string image;
	const Carte** liste_carte1 = nullptr;
	const Carte** liste_carte2 = nullptr;
	int gagnant = -1;
	int nb_carte1 = 0;
	int nb_carte2 = 0;
	bool CombatDeBoue = 0;
	int nb_max = 3;

public:
	Nombre getNumero() const { return numero; }
	string getImage() const { return image; }
	int getGagnant() const { return gagnant; }
	int getNbCarte1() const { return nb_carte1; }
	int getNbCarte2() const { return nb_carte2; }
	int getCombatDeBoue() const { return CombatDeBoue; }
	int getNbMax() const { return nb_max; }

	//On pourrait avoir 0 cartes au d¨¦but
	Borne(Nombre num, string img) : numero(num),image(img){}
	~Borne() {
		delete[] liste_carte1;
		delete[] liste_carte2;
	}
	Borne(const Borne&) = delete;
	Borne& operator=(const Borne& p) = delete;


	void modeCombatdeBout(){ 
		CombatDeBoue = 1; 
		nb_max = 4;
	}

	void ajouter(const Carte& c);
	void retirer(const Carte& c);

	
	
};

string toString(Nombre v);
ostream& operator<<(ostream& f, Nombre v);