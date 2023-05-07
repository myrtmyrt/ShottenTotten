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

    //méthodes
    bool estVide() const { return CartesCl.size() == 0; }

    // Mélanger
    void Melange(){
    int size = CartesCl.size();
    for (int i = 0; i < size - 1; i++) {
      int j = i + rand() % (size - i);
      swap(CartesCl[i], CartesCl[j]);
    }
    }
    //Piocher : retourne la dernière carte du vecteur CartesCl sans l'effacer
        CarteClan* Piocher(){
            nbCartesRestantes-=1;
        return CartesCl[CartesCl.size()-1];
    }
    //Effacer dernier élément
    void Effacer () {
    CartesCl.pop_back();
    }


    // Interdiction du constructeur par recopie et de l'opérateur d'affectation
    PiocheClan(const PiocheClan&) = delete;
    PiocheClan& operator=(const PiocheClan&) = delete;



};



class PiocheTactique{
};

#endif //PROJET_PIOCHE_H







/*
    const Carte& piocher(Joueur j){
        int randNum = rand()%(nbCartesRestantes) + nbCartesRestantes;
        nbCartesRestantes-=1;
        j.nbCartes+=1;
        auto* newCarte = new CarteClan(CartesCl[i].getcouleur(),CartesCl[i].getnombre() );
        j.cartesJoueurClan.push_back(newCarte);
        CartesCl.pop_back(CartesCl[i]);
    };

*/

