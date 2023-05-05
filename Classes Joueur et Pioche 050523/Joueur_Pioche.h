
#ifndef _JOUEURPIOCHE_H
#define _JOUEURPIOCHE_H

#include <iostream>
#include <string>
#include <initializer_list>
#include <array>
#include <cstdlib>
using namespace std;

namespace Joueur_Pioche {
	// classe pour g�rer les exceptions dans le set
	class SetException {
	public:
		SetException(const string& i) :info(i) {}
		string getInfo() const { return info; }
	private:
		string info;
	};

	// caract�ristiques
	enum class Couleur { Rouge, Orange,Jaune,Vert,Bleu,Violet};
	enum class Nombre { Un=1, Deux=2, Trois=3, Quatre=4, Cinq=5, Six=6, Sept=7,Huit=8, Neuf=9 };


	// conversion d'une caract�ristique en string
	string toString(Couleur c);
	string toString(Nombre v);


	// �criture d'une caract�ristique sur un flux ostream
	ostream& operator<<(ostream& f, Couleur c);
	ostream& operator<<(ostream& f, Nombre v);


	// listes contenant les valeurs possibles pour chacune des caract�ristiques
	extern std::initializer_list<Couleur> Couleurs;
	extern std::initializer_list<Nombre> Nombres;


	// affichage des valeurs possibles pour chaque caract�ristiques
	void printCouleurs(std::ostream& f = cout);
	void printNombres(std::ostream& f = cout);


	class Carte {
	private:
		// Un attribut par caract�ristique
		// On utilise les types enum
		Couleur couleur;
		Nombre nombre;


		// On veut que seule la classe Jeu puisse cr�er une Carte
		// On passe le constructeur en priv� et on d�clare Jeu comme classe amie
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
		// Op�rateur d'affectation
		Carte& operator=(const Carte& c) = default; // optionnel
	};



	class Jeu {
	private:
		// Tableau de pointeurs sur les cartes du jeu
		// Les cartes doivent �tre cr��es dynamiquement par l'objet Jeu
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

		// La classe Jeu a un attribut statique Handler (unique et partag�) qui g�re l'instance de Jeu
		static Handler handler;

		// Note : il faut initialiser le Handler dans Joueur_Pioche.cpp
		// avec l'instruction : Jeu::Handler Jeu::handler = Handler();

		/* Fin Singleton (partie priv�e) */


		// On passe getCarte() en m�thode priv�e pour ne plus y avoir acc�s hors de la classe
		// except� pour les classes amies
		const Carte& getCarte(size_t i) const {
			if (i >= 54) throw SetException("Carte invalide");
			return *cartes[i];
		}
		friend class Iterator; // La classe Iterator a maintenant acc�s aux m�thodes priv�es de Jeu

	public:

		// La m�thode getInstance() cr�e une instance au sein du Handler si elle n'existe pas
		// La m�thode libererInstance() d�salloue l'instance unique du Handler
		static Jeu& getInstance() {
			if (handler.instance == nullptr) handler.instance = new Jeu;
			return *handler.instance;
		}

		static void libererInstance() {
			delete handler.instance; handler.instance = nullptr;
		}

		// On d�finit une classe Iterator.
		// Son impl�mentation d�pend de l'impl�mentation de la classe Jeu
		// Son utilisation est ind�pendante de l'impl�mentation de la classe Jeu
		// Elle doit d�finir les m�thodes : next(), isDone() et currentItem()
		class Iterator {
		public:
			void next() { // l'it�rateur se d�place sur l'�l�ment suivant
				if(isDone()) throw SetException("Iterateur en fin de s�quence");
				i++;
			}

			bool isDone() const { // indique si toutes les cartes ont �t� parcourues
				return i == Jeu::getInstance().getNbCartes();
			}

			const Carte& currentItem() const { // renvoie une r�f�rence sur l'�l�ment courant
				if (isDone()) throw SetException("Iterateur en fin de s�quence");
				return Jeu::getInstance().getCarte(i);
				// Note : on peut utiliser getCarte() ici bien que ce soit une m�thode priv�e
				// de la classe Jeu, car la classe Iterator est une classe amie de Jeu
			}
		private:
			size_t i = 0;
			// On ne veut pouvoir construire d'it�rateur de Jeu qu'au sein de la classe Jeu
			// On rend donc son constructeur priv� et on d�clare la classe Jeu comme classe amie
			friend class Jeu;
			Iterator() = default;

		};
		// M�thode pour cr�er et retourner un it�rateur sur les cartes du Jeu
		Iterator getIterator() const { return Iterator(); }

		/* Fin Exercice 23 : it�rateur */

		// Accesseurs en lecture
		size_t getNbCartes() const { return 54; }

	};




	class Pioche {
	private:
		// Tableau dynamique contenant les cartes de la pioche
		// La taille d�pend du jeu de cartes utilis�
		const Carte** cartes = nullptr;
		// Nombre de cartes restantes dans la pioche
		size_t nb = 0;
	public:
		// Constructeur d'une pioche � partir d'un jeu de cartes
		// On utilise le mot cl� "explicit" pour interdire la conversion implicite de Jeu en Pioche
		Pioche(); // On acc�de � l'unique instance de Jeu de mani�re statique

		// Destructeur
		~Pioche();

		bool estVide() const { return nb == 0; }
		size_t getNbCartes() const { return nb; }

		// Choisit une Carte de la Pioche, la supprime de la Pioche et la retourne
		const Carte& piocher();

		// Interdiction du constructeur par recopie et de l'op�rateur d'affectation
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
		// Tableau dynamique d�pendant du nombre de cartes sur le plateau
		// On augmentera la taille du tableau en fonction des besoins
		const Carte** cartes = nullptr;
		size_t nbMax = 0; // taille du tableau allou�e
		size_t nb = 0; // taille du tableau utilis�e

	public:
		// Le constructeur par d�faut convient : il n'y a pas de carte initialement
		Plateau() = default;
		// Destructeur : lib�re l'espace m�moire utilis� par le tableau de cartes
		~Plateau() { delete[] cartes;}


		class const_iterator {
		public:
			const_iterator& operator++() { current++; return *this; } // On avance
			const Carte& operator*() const { return **current; } // On retourne la carte courante
			bool operator!=(const_iterator it) { return current != it.current; } // Comparaison de deux it�rateurs
		private:
			const Carte** current = nullptr; // pointeur sur la case du tableau (cartes) courante
			friend class Plateau;
			// On initialise l'it�rateur avec une adresse sur un pointeur de Carte
			// La m�thode begin() initialisera avec l'adresse de d�but du tableau
			// La m�thode end() initialisera avec l'adresse suivant la fin du tableau
			const_iterator(const Carte** c) : current(c) {}
		};

		// It�rateur sur le d�but du tableau
		const_iterator begin() const { return const_iterator(cartes); }
		// It�rateur repr�sentant l'it�rateur en fin de parcours
		const_iterator end() const { return const_iterator(cartes + nb); }


		size_t getNbCartes() const { return nb; }

		// Ajoute une carte au plateau
		void ajouter(const Carte& c);
		// Retire une carte du plateau
		void retirer(const Carte& c);

		// M�thode d'affichage du plateau sur un flux ostream
		void print(ostream& f = cout) const;

		// Surcharge du constructeur par recopie et de l'op�rateur d'affectation
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


	// Surcharge des op�rateurs "<<" pour afficher sur un flux ostream
	ostream& operator<<(ostream& f, const Joueur_Pioche::Carte& c);
	ostream& operator<<(ostream& f, const Joueur_Pioche::Plateau& p);
	ostream& operator<<(ostream& f, const Joueur_Pioche::Combinaison& c);
}


#endif
