#pragma once
#include "Joueur_Pioche.h"
#include <iostream>
#include <string>

using namespace std;

enum class Nombre { Un = 1, Deux = 2, Trois = 3, Quatre = 4, Cinq = 5, Six = 6, Sept = 7, Huit = 8, Neuf = 9 };

class Borne {
private:
	Nombre numero;
	string image;
	const Joueur_Pioche::Carte** liste_carte1 = nullptr;
	const Joueur_Pioche::Carte** liste_carte2 = nullptr;
	int gagnant;
	int nb_carte1;
	int nb_carte2;
	//bool CombatBoue;
	int nb_max = 4;

public:
	Nombre getNumero() const { return numero; }
	int getGagnant() const { return gagnant; }
	//On pourrait avoir 0 cartes au d¨¦but
	Borne() = default;
	~Borne() {
		delete[] liste_carte1;
		delete[] liste_carte2;
	}
	Borne(const Borne&) = delete;
	Borne& operator=(const Borne& p) = delete;
	void ajouter1(const Joueur_Pioche::Carte& c);
	void ajouter2(const Joueur_Pioche::Carte& c);
	void retirer1(const Joueur_Pioche::Carte& c);
	void retirer2(const Joueur_Pioche::Carte& c);
};