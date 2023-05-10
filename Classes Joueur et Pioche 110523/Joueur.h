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
            size_t nbCartesClan;
            vector<CarteClan*> cartesJoueurClan;
            vector<CarteTactique*> cartesJoueurTactique;
        public :
            Joueur(int n, std::string na, bool b): numero(n), name(na), human(b){
                nbCartesClan=0;
                }
            ~Joueur(){}

            //accesseurs en lecture
            int getNumero() const { return numero; }
            std::string getName() const {return name;}
            bool getHuman() const {return human; }
            int getNbCartesClan() const {return nbCartesClan;}

            //Mthode Joueur
            void afficherCartesClan(){

                for(unsigned int i = 0; i < nbCartesClan; i++){
                   cout<<(*cartesJoueurClan[i])<<endl;
                    i++;
                }
                }

        /*     void afficherCartesTactique(){

                for(unsigned int i = 0; i < cartesJoueurTactique.size(); i++){
                    std::cout << cartesJoueurTactique[i]<<std::endl;
                    i++;
                }
                }*/
            void ajouterCarte( CarteClan* c){
            cartesJoueurClan.push_back(c);
            nbCartesClan++;
            }

	};

#endif



