#include "borne.h"

void Borne::retirer1(const Joueur_Pioche::Carte& c) {
	// On cherche la carte correspondante
	size_t i = 0;
	while (i < nb_carte1 && liste_carte1[i] != &c) i++;
	if (i == nb_carte1) throw "Carte inexistante";
	// On fait le d¨¦calage pour supprimer la carte
	i++;
	while (i < nb_carte1) {
		liste_carte1[i - 1] = liste_carte1[i];
		i++;
	}
	nb_carte1--;
}

void Borne::retirer2(const Joueur_Pioche::Carte& c) {
	// On cherche la carte correspondante
	size_t i = 0;
	while (i < nb_carte2 && liste_carte2[i] != &c) i++;
	if (i == nb_carte2) throw "Carte inexistante";
	// On fait le d¨¦calage pour supprimer la carte
	i++;
	while (i < nb_carte2) {
		liste_carte2[i - 1] = liste_carte2[i];
		i++;
	}
	nb_carte2--;
}

void Borne::ajouter1(const Joueur_Pioche::Carte& c) {
	// Si le tableau est rempli,on ne pourra plus ajouter une carte 
	if (nb_carte1 == nb_max) throw "Attention : nombre max atteint, vous ne pouvez pas ajouter une carte.";
		//sinon
	const Joueur_Pioche::Carte** newtab = new const Joueur_Pioche::Carte* [nb_carte1+1];
	// On recopie les valeurs dans le nouveau tableau
	for (size_t i = 0; i < nb_carte1; i++) newtab[i] = liste_carte1[i];
	// Le nouveau tableau devient le tableau du Plateau

		// On pense ¨¤ d¨¦sallouer l'ancien tableau
		
		auto old = liste_carte1;
		liste_carte1 = newtab;
		delete[] old;

		// On ajoute la carte
		liste_carte1[nb_carte1++] = &c;

		nb_carte1++;
	}
	

void Borne::ajouter2(const Joueur_Pioche::Carte& c) {
	// Si le tableau est rempli,on ne pourra plus ajouter une carte 
	if (nb_carte2 == nb_max) throw "Attention : nombre max atteint, vous ne pouvez pas ajouter une carte.";
	//sinon
	const Joueur_Pioche::Carte** newtab = new const Joueur_Pioche::Carte * [nb_carte2 + 1];
	// On recopie les valeurs dans le nouveau tableau
	for (size_t i = 0; i < nb_carte2; i++) newtab[i] = liste_carte2[i];
	// Le nouveau tableau devient le tableau du Plateau

		// On pense ¨¤ d¨¦sallouer l'ancien tableau

	auto old = liste_carte2;
	liste_carte2 = newtab;
	delete[] old;

	// On ajoute la carte
	liste_carte2[nb_carte2++] = &c;

	nb_carte2++;
}
