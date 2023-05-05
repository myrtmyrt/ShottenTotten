
#ifndef _JOUEURPIOCHE_H
#define _JOUEURPIOCHE_H

#include <iostream>
#include <string>
#include <initializer_list>
#include <array>
#include <cstdlib>
using namespace std;

namespace Joueur_Pioche {
	// classe pour gérer les exceptions dans le set
	class SetException {
	public:
		SetException(const string& i) :info(i) {}
		string getInfo() const { return info; }
	private:
		string info;
	};

	// caractéristiques
	enum class Couleur { Rouge, Orange,Jaune,Vert,Bleu,Violet};
	enum class Nombre { Un=1, Deux=2, Trois=3, Quatre=4, Cinq=5, Six=6, Sept=7,Huit=8, Neuf=9 };


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


	class Carte {
	private:
		// Un attribut par caractéristique
		// On utilise les types enum
		Couleur couleur;
		Nombre nombre;


		// On veut que seule la classe Jeu puisse créer une Carte
		// On passe le constructeur en privé et on déclare Jeu comme classe amie
		Carte(Couleur c, Nombre n) : couleur(c), nombre(n) {};
		friend class Jeu;
	public:
		// Accesseurs en lecture
		Couleur getCouleur() const { return couleur; }
		Nombre getNombre() const { return nombre; }


		// Destructeur
		~Carte() = default; // optionnel
		// Constructeur par recopie
		Carte(const Carte& c) = default; // optionnel
		// Opérateur d'affectation
		Carte& operator=(const Carte& c) = default; // optionnel
	};



	class Jeu {
	private:
		// Tableau de pointeurs sur les cartes du jeu
		// Les cartes doivent être créées dynamiquement par l'objet Jeu
		const Carte* cartes[81];

		Jeu();
		~Jeu();
		Jeu(const Jeu&) = delete;
		Jeu& operator=(const Jeu& j) = delete;


		// Structure Handler
		// Cet objet encapsule une instance de Jeu
		struct Handler {
			Jeu* instance;
			Handler() : instance(nullptr) {}
			~Handler() { delete instance; }
		};

		// La classe Jeu a un attribut statique Handler (unique et partagé) qui gère l'instance de Jeu
		static Handler handler;

		// Note : il faut initialiser le Handler dans Joueur_Pioche.cpp
		// avec l'instruction : Jeu::Handler Jeu::handler = Handler();

		/* Fin Singleton (partie privée) */


		// On passe getCarte() en méthode privée pour ne plus y avoir accès hors de la classe
		// excepté pour les classes amies
		const Carte& getCarte(size_t i) const {
			if (i >= 54) throw SetException("Carte invalide");
			return *cartes[i];
		}
		friend class Iterator; // La classe Iterator a maintenant accès aux méthodes privées de Jeu

	public:

		// La méthode getInstance() crée une instance au sein du Handler si elle n'existe pas
		// La méthode libererInstance() désalloue l'instance unique du Handler
		static Jeu& getInstance() {
			if (handler.instance == nullptr) handler.instance = new Jeu;
			return *handler.instance;
		}

		static void libererInstance() {
			delete handler.instance; handler.instance = nullptr;
		}

		// On définit une classe Iterator.
		// Son implémentation dépend de l'implémentation de la classe Jeu
		// Son utilisation est indépendante de l'implémentation de la classe Jeu
		// Elle doit définir les méthodes : next(), isDone() et currentItem()
		class Iterator {
		public:
			void next() { // l'itérateur se déplace sur l'élément suivant
				if(isDone()) throw SetException("Iterateur en fin de séquence");
				i++;
			}

			bool isDone() const { // indique si toutes les cartes ont été parcourues
				return i == Jeu::getInstance().getNbCartes();
			}

			const Carte& currentItem() const { // renvoie une référence sur l'élément courant
				if (isDone()) throw SetException("Iterateur en fin de séquence");
				return Jeu::getInstance().getCarte(i);
				// Note : on peut utiliser getCarte() ici bien que ce soit une méthode privée
				// de la classe Jeu, car la classe Iterator est une classe amie de Jeu
			}
		private:
			size_t i = 0;
			// On ne veut pouvoir construire d'itérateur de Jeu qu'au sein de la classe Jeu
			// On rend donc son constructeur privé et on déclare la classe Jeu comme classe amie
			friend class Jeu;
			Iterator() = default;

		};
		// Méthode pour créer et retourner un itérateur sur les cartes du Jeu
		Iterator getIterator() const { return Iterator(); }

		/* Fin Exercice 23 : itérateur */

		// Accesseurs en lecture
		size_t getNbCartes() const { return 54; }

	};




	class Pioche {
	private:
		// Tableau dynamique contenant les cartes de la pioche
		// La taille dépend du jeu de cartes utilisé
		const Carte** cartes = nullptr;
		// Nombre de cartes restantes dans la pioche
		size_t nb = 0;
	public:
		// Constructeur d'une pioche à partir d'un jeu de cartes
		// On utilise le mot clé "explicit" pour interdire la conversion implicite de Jeu en Pioche
		Pioche(); // On accède à l'unique instance de Jeu de manière statique

		// Destructeur
		~Pioche();

		bool estVide() const { return nb == 0; }
		size_t getNbCartes() const { return nb; }

		// Choisit une Carte de la Pioche, la supprime de la Pioche et la retourne
		const Carte& piocher();

		// Interdiction du constructeur par recopie et de l'opérateur d'affectation
		//Pioche(const Pioche&) = delete;
		Pioche& operator=(const Pioche&) = delete;
	};


	class Joueur{
        private:
            int numero;
            std::string name;
            bool human;
            int nbCartes;
            const Joueur_Pioche::Carte* cartesJoueur[10];
        public :
            Joueur(int n, std::string na, bool b) :  numero(n), name(na), human (b){nbCartes=0;}
            ~Joueur(){}
            int getNumero() const { return numero; }
            std::string getName() const {return name;}
            bool getHuman() const {return human; }
            int getNbCartes() const {return nbCartes;}
            void distribution(Joueur_Pioche::Pioche p){
                for (int i=0; i<=6; i++){
                    cartesJoueur[i]=&p.piocher();
                }
            }
            void afficherCartes(){
                int i=0;
                while (cartesJoueur[i]!=nullptr){
                    std::cout << cartesJoueur[i]<<std::endl;
                    i++;
                }
                }



        };


































	class Plateau {
	private:
		// Tableau dynamique dépendant du nombre de cartes sur le plateau
		// On augmentera la taille du tableau en fonction des besoins
		const Carte** cartes = nullptr;
		size_t nbMax = 0; // taille du tableau allouée
		size_t nb = 0; // taille du tableau utilisée

	public:
		// Le constructeur par défaut convient : il n'y a pas de carte initialement
		Plateau() = default;
		// Destructeur : libère l'espace mémoire utilisé par le tableau de cartes
		~Plateau() { delete[] cartes;}


		class const_iterator {
		public:
			const_iterator& operator++() { current++; return *this; } // On avance
			const Carte& operator*() const { return **current; } // On retourne la carte courante
			bool operator!=(const_iterator it) { return current != it.current; } // Comparaison de deux itérateurs
		private:
			const Carte** current = nullptr; // pointeur sur la case du tableau (cartes) courante
			friend class Plateau;
			// On initialise l'itérateur avec une adresse sur un pointeur de Carte
			// La méthode begin() initialisera avec l'adresse de début du tableau
			// La méthode end() initialisera avec l'adresse suivant la fin du tableau
			const_iterator(const Carte** c) : current(c) {}
		};

		// Itérateur sur le début du tableau
		const_iterator begin() const { return const_iterator(cartes); }
		// Itérateur représentant l'itérateur en fin de parcours
		const_iterator end() const { return const_iterator(cartes + nb); }


		size_t getNbCartes() const { return nb; }

		// Ajoute une carte au plateau
		void ajouter(const Carte& c);
		// Retire une carte du plateau
		void retirer(const Carte& c);

		// Méthode d'affichage du plateau sur un flux ostream
		void print(ostream& f = cout) const;

		// Surcharge du constructeur par recopie et de l'opérateur d'affectation
		Plateau(const Plateau&);
		Plateau& operator=(const Plateau& p);
	};


	class Combinaison {
	private:
		const Carte* c1;
		const Carte* c2;
		const Carte* c3;
	public:
		Combinaison(const Carte& u, const Carte& d, const Carte& t) : c1(&u), c2(&d), c3(&t) {}
		const Carte& getCarte1() const { return *c1; }
		const Carte& getCarte2() const { return *c2; }
		const Carte& getCarte3() const { return *c3; }

		bool estUnSet() const;

		~Combinaison() = default;
		Combinaison(const Combinaison& c) = default;
		Combinaison& operator=(const Combinaison& c) = default;
	};


	class Controleur {
	private:

		Pioche* pioche;
		Plateau plateau;
	public:
		Controleur();
		~Controleur() { delete pioche; }

		void distribuer();
		const Plateau& getPlateau() const { return plateau; }
	};


	// Surcharge des opérateurs "<<" pour afficher sur un flux ostream
	ostream& operator<<(ostream& f, const Joueur_Pioche::Carte& c);
	ostream& operator<<(ostream& f, const Joueur_Pioche::Plateau& p);
	ostream& operator<<(ostream& f, const Joueur_Pioche::Combinaison& c);
}


#endif
