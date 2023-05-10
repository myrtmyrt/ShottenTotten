#ifndef PROJET_PIOCHE_H
#define PROJET_PIOCHE_H

#include <iostream>
#include <vector>
#include <random>
#include "Carte.h"
#include "Joueur.h"

using namespace std;

class PiocheClan{
private:
    const size_t nbCartesMax=54;
    size_t nbCartesRestantes=54;
    vector<CarteClan*> CartesCl;
public:
    //constructeur
    PiocheClan(){
        Couleur CouleursPossibles[6]={Couleur::rouge, Couleur::bleu, Couleur::vert, Couleur::violet,Couleur::orange, Couleur::jaune};
        Nombre NombresPossibles[9]={Nombre::un,Nombre::deux,Nombre::trois,Nombre::quatre,Nombre::cinq,Nombre::six,Nombre::sept,Nombre::huit,Nombre::neuf};
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 9; j++) {
                auto* newCarte = new CarteClan(CouleursPossibles[i],NombresPossibles[j]);
                CartesCl.push_back(newCarte);

            }
        }
    }



    ~PiocheClan(){
        CartesCl.clear();
        }
    //Accesseurs en lecture
    size_t getNbcarte() const { return CartesCl.size();}
    size_t getNbMax()const { return nbCartesMax;}

    //mthodes
    bool estVide() const { return CartesCl.size() == 0; }

    // Mlanger
    void Melange(){
    int s = CartesCl.size();
    for (int i = 0; i < s - 1; i++) {
      int j = i + rand() % (s - i);
      swap(CartesCl[i], CartesCl[j]);
    }
    }


//Piocher : retourne la dernire carte du vecteur CartesCl sans l'effacer
     CarteClan* Piocher() {
		if (nbCartesRestantes!=0) {
		// On choisit une carte aléatoire
		size_t x = rand() % nbCartesRestantes-1;
		 CarteClan* c=CartesCl[x];
		// On décale les cartes restantes
		for (size_t i = x + 1; i < nbCartesRestantes; ++i) CartesCl[i - 1] = CartesCl[i];
		nbCartesRestantes--;
		// On retourne la carte piochée
		return c;
	}
     }

         //Piocher : retourne la dernire carte du vecteur CartesCl sans l'effacer
   /*     CarteClan* Piocher(){
            if (nbCartesRestantes!=0){
            nbCartesRestantes-=1;
        return CartesCl[CartesCl.size()-1];
            }
    }*/





    //Effacer dernier lment
    void Effacer () {
    CartesCl.pop_back();
    }


    // Interdiction du constructeur par recopie et de l'oprateur d'affectation
    PiocheClan(const PiocheClan&) = delete;
    PiocheClan& operator=(const PiocheClan&) = delete;



};



class PiocheTactique{
};

#endif //PROJET_PIOCHE_H


