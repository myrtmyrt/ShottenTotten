
#ifndef _JOUEUR_H
#define _JOUEUR_H

#include <iostream>
#include <string>
#include <initializer_list>
#include <array>
#include <cstdlib>
#include <vector>
#include "Carte.h"
#include"Jeu.h"
#include"Pioche.h"






	class Joueur{
        private:
            int numero;
            std::string name;
            bool human;
            size_t nbCartes;
            vector<CarteClan*> cartesJoueurClan;
            vector<CarteTactique*> cartesJoueurTactique;
        public :
            Joueur(int n, std::string na, bool b): numero(n), name(na), human(b){
                nbCartes=6;
                }
            ~Joueur(){}

            //accesseurs en lecture
            int getNumero() const { return numero; }
            std::string getName() const {return name;}
            bool getHuman() const {return human; }
            int getNbCartes() const {return nbCartes;}

            //Méthode Joueur
            void afficherCartesClan(){

                for(unsigned int i = 0; i < cartesJoueurClan.size(); i++){
                    std::cout << cartesJoueurClan[i]<<std::endl;
                    i++;
                }
                }

             void afficherCartesTactique(){

                for(unsigned int i = 0; i < cartesJoueurTactique.size(); i++){
                    std::cout << cartesJoueurTactique[i]<<std::endl;
                    i++;
                }
                }
            void ajouterCarte( CarteClan* c){
            cartesJoueurClan.push_back(c);
            }

	};

#endif


