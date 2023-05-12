#include "borne.h"

void Borne::retirer(const Carte& c) {

	int joueur1;
	cout << "Enregistrer votre numéro pour jouer (1 ou 2)" << endl;
	cin >> joueur1;

	while ((joueur1 != 1) && (joueur1 != 2)) {
		cout << "Votre enregistrement n'est pas valable, enregistrez 1 ou 2 s'il vous plaît" << endl;
		cin >> joueur1;
	}

	size_t i = 0;
	if (joueur1 == 1) {
		// On cherche la carte correspondante
		while (i < nb_carte1 && liste_carte1[i] != &c) i++;
		if (i == nb_carte1) throw "Carte inexistante";
		// On fait le décalage pour supprimer la carte
		i++;
		while (i < nb_carte1) {
			liste_carte1[i - 1] = liste_carte1[i];
			i++;
		}
		nb_carte1--;
	}
	else if (joueur1 == 2) 
		// On cherche la carte correspondante
		while (i < nb_carte2 && liste_carte2[i] != &c) i++;
		if (i == nb_carte2) throw "Carte inexistante";
		// On fait le décalage pour supprimer la carte
		i++;
		while (i < nb_carte2) {
			liste_carte2[i - 1] = liste_carte2[i];
			i++;
		}
		nb_carte2--;
}
		


void Borne::ajouter(const Carte& c) {

	//choix de joueur
	int joueur2;
	cout << "Enregistrer votre numéro pour jouer (1 ou 2)" << endl;
	cin >> joueur2;

	while (joueur2 != 1 && joueur2 != 2) {
		cout << "Votre enregistrement n'est pas valable, enregistrez 1 ou 2 s'il vous plaît" << endl;
		cin >> joueur2;
	}

	if (joueur2 == 1) {
		// Si le tableau est rempli,on ne pourra plus ajouter une carte 
		if (nb_carte1 == nb_max) throw "Attention : nombre max atteint, vous ne pouvez pas ajouter une carte.";
		//sinon
		const Carte** newtab = new const Carte* [nb_carte1+1];
		// On recopie les valeurs dans le nouveau tableau
		for (size_t i = 0; i < nb_carte1; i++) newtab[i] = liste_carte1[i];
		// Le nouveau tableau devient le tableau du Plateau

		// On pense à désallouer l'ancien tableau
		
		auto old = liste_carte1;
		liste_carte1 = newtab;
		delete[] old;

		// On ajoute la carte
		liste_carte1[nb_carte1++] = &c;

		nb_carte1++;
	}

	if (joueur2 == 2) {
		// Si le tableau est rempli,on ne pourra plus ajouter une carte 
		if (nb_carte2 == nb_max) throw "Attention : nombre max atteint, vous ne pouvez pas ajouter une carte.";
		//sinon
		const Carte** newtab = new const Carte * [nb_carte2 + 1];
		// On recopie les valeurs dans le nouveau tableau
		for (size_t i = 0; i < nb_carte2; i++) newtab[i] = liste_carte2[i];
		// Le nouveau tableau devient le tableau du Plateau

			// On pense à désallouer l'ancien tableau

		auto old = liste_carte2;
		liste_carte2 = newtab;
		delete[] old;

		// On ajoute la carte
		liste_carte2[nb_carte2++] = &c;

		nb_carte2++;

	}

}


	
//Erreur de type Borne