#include "Joueur_Pioche.h"

namespace Joueur_Pioche {

	std::initializer_list<Couleur> Couleurs = { Couleur::Rouge, Couleur::Orange, Couleur::Jaune, Couleur::Vert, Couleur::Bleu, Couleur::Violet };
	std::initializer_list<Nombre> Nombres = { Nombre::Un, Nombre::Deux, Nombre::Trois, Nombre::Quatre, Nombre::Cinq, Nombre::Six, Nombre::Sept, Nombre::Huit, Nombre::Neuf };

	string toString(Couleur c) {
		switch (c) {
		case Couleur::Rouge: return "Rouge";
		case Couleur::Orange: return "Orange";
		case Couleur::Jaune: return "Jaune";
		case Couleur::Vert: return "Vert";
		case Couleur::Bleu: return "Bleu";
		case Couleur::Violet: return "Violet";
		default: throw SetException("Couleur inconnue");
		}
	}

	string toString(Nombre v) {
		switch (v) {
		case Nombre::Un: return "1";
		case Nombre::Deux: return "2";
		case Nombre::Trois: return "3";
		case Nombre::Quatre: return "4";
		case Nombre::Cinq: return "5";
		case Nombre::Six: return "6";
		case Nombre::Sept: return "7";
		case Nombre::Huit: return "8";
		case Nombre::Neuf: return "9";
		default: throw SetException("Nombre inconnue");
		}
	}

	std::ostream& operator<<(std::ostream& f, Couleur c) { f << toString(c); return f; }
	std::ostream& operator<<(std::ostream& f, Nombre v) {	f << toString(v); return f; }

	void printCouleurs(std::ostream& f) {
		for (auto c : Couleurs) f << c << " ";
		f << "\n";
	}

	void printNombres(std::ostream& f) {
		for (auto v : Nombres) f << v << " ";
		f << "\n";
	}

	Jeu::Jeu() {
		// On crée dynamiquement l'ensemble des cartes
		size_t i = 0;
		for (auto c : Couleurs)
			for (auto n : Nombres) cartes[i++] = new Carte(c, n);
	}

	Jeu::~Jeu() {
		// Jeu gère le cycle de vie des cartes, il doit les désallouer
		for (size_t i = 0; i < getNbCartes(); i++) delete cartes[i];
	}

	Jeu::Handler Jeu::handler = Handler();


	// On accède à l'unique instance de Jeu par la méthode statique Jeu::getInstance()
	Pioche::Pioche() : cartes(new const Carte* [Jeu::getInstance().getNbCartes()]), nb(Jeu::getInstance().getNbCartes()) {
		// On remplit la pioche avec les cartes du jeu de cartes
		// On ne peut plus utiliser la méthode "getCarte(i)" pour parcourir les cartes d'un jeu
		// On utilise donc l'itérateur défini dans Jeu::Iterator et les méthodes associées
		size_t i = 0;
		for (auto it = Jeu::getInstance().getIterator(); !it.isDone(); it.next(), i++)
			cartes[i] = &it.currentItem();
	}

	Pioche::~Pioche() {
		delete[] cartes;
	}

	const Carte& Pioche::piocher() {
		if (estVide()) throw SetException("Pioche vide");
		// On choisit une carte aléatoire
		size_t x = rand() % nb;
		const Carte* c = cartes[x];
		// On décale les cartes restantes
		for (size_t i = x + 1; i < nb; ++i) cartes[i - 1] = cartes[i];
		nb--;
		// On retourne la carte piochée
		return *c;
	}

	void Plateau::ajouter(const Carte& c) {
		// Si le tableau est rempli
		if (nb == nbMax) {
			// Augmenter la taille du tableau cartes
			// On crée un tableau plus grand
			const Carte** newtab = new const Carte * [(nbMax + 1) * 2];
			// On recopie les valeurs dans le nouveau tableau
			for (size_t i = 0; i < nb; i++) newtab[i] = cartes[i];
			// Le nouveau tableau devient le tableau du Plateau
			// On pense à désallouer l'ancien tableau
			auto old = cartes;
			cartes = newtab;
			delete[] old;
			nbMax = (nbMax + 1) * 2;
		}
		// On ajoute la carte
		cartes[nb++] = &c;
	}

	void Plateau::retirer(const Carte& c) {
		// On cherche la carte correspondante sur le plateau
		size_t i = 0;
		while (i < nb && cartes[i] != &c) i++;
		if (i == nb) throw SetException("Carte inexistante");
		// On fait le décalage pour supprimer la carte du plateau
		i++;
		while (i < nb) {
			cartes[i - 1] = cartes[i];
			i++;
		}
		nb--;
	}

	void Plateau::print(ostream& f) const {
		// On souhaite afficher quatre cartes par ligne
		for (size_t i = 0; i < nb; i++) {
			if (i % 4 == 0) f << "\n";
			f << *cartes[i] << " ";
		}
		f << "\n";
	}

	Plateau::Plateau(const Plateau& p) : cartes(new const Carte* [p.nb]), nb(p.getNbCartes()), nbMax(p.getNbCartes()) {
		// La recopie par défaut ne fonctionne pas ici : on partagerait le même tableau de cartes
		// Il faut donc allouer un tableau propre à cette instance de plateau, et copier les cartes
		for (size_t i = 0; i < nb; ++i) cartes[i] = p.cartes[i];
	}

	Plateau& Plateau::operator=(const Plateau& p) {
		// Si on essaie d'affecter un plateau à lui même, ne rien faire
		if (this != &p) {
			// Si le tableau du plateau est trop petit pour recevoir
			// les cartes affectées, on alloue un nouveau tableau
			// Sinon, on utilise le tableau déjà alloué
			if (p.nb > this->nbMax) {
				// On alloue un nouveau tableau
				const Carte** newtab = new const Carte * [p.nb];
				// On copie les valeurs
				for (size_t i = 0; i < p.nb; ++i) newtab[i] = p.cartes[i];
				// On remplace l'ancien tableau par le nouveau
				// Sans oublier de désallouer l'ancien tableau !
				auto old = this->cartes;
				this->cartes = newtab; // le "this->" est optionnel
				this->nb = p.nb;
				this->nbMax = p.nb;
				delete[] old;
			}
			else {
				// On copie les valeurs dans le tableau déjà existant
				for (size_t i = 0; i < p.nb; ++i) this->cartes[i] = p.cartes[i];
				this->nb = p.nb;
			}
		}
		// On renvoie une référence sur le plateau
		return *this;
	}

	bool Combinaison::estUnSet() const {
		bool c = (c1->getCouleur() == c2->getCouleur() && c2->getCouleur() == c3->getCouleur())
			|| (c1->getCouleur() != c2->getCouleur()
				&& c2->getCouleur() != c3->getCouleur()
				&& c1->getCouleur() != c3->getCouleur());
		bool f = true; // faire pareil que pour couleur
		bool r = true; // faire pareil que pour couleur
		bool n = true; // faire pareil que pour couleur
		return c && f && r && n;
	}


	Controleur::Controleur() {

		// Nouveau constructeur de Pioche sans argument
		pioche = new Pioche;
	}

	void Controleur::distribuer() {
		if (plateau.getNbCartes() < 12) {
			while (!pioche->estVide() && plateau.getNbCartes() < 12)
				plateau.ajouter(pioche->piocher());
		}
		else
			if (!pioche->estVide()) plateau.ajouter(pioche->piocher());
	}


	ostream& operator<<(ostream& f, const Joueur_Pioche::Carte& c) {
		// On affiche les quatre caractéristiques de la carte
		f << "(" << c.getNombre() << "," << c.getCouleur() <<  ")";
		// On retourne le flux pour pouvoir enchainer les affichages
		return f;
	}
	ostream& operator<<(ostream& f, const Joueur_Pioche::Plateau& p) {
		// On affiche le plateau en appelant la méthode print
		// La méthode print doit être déclarée comme méthode const !
		p.print(f);
		// On retourne le flux... blablabla on connait la chanson mais c'est important
		return f;
	}

	ostream& operator<<(ostream& f, const Joueur_Pioche::Combinaison& c) {
		f << "[" << c.getCarte1() << "," << c.getCarte2() << "," << c.getCarte3() << "]";
		return f;
	}

}
