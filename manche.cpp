//
// Created by Arman Saint-Marc on 24/04/2023.
//

#include "jeu.h"
#include "carte.h"
#include "manche.h"
#include "pioche.h"
#include "joueur.h"
#include <unordered_map>
#include <functional>


#define BORNES 9

using namespace std;

initializer_list<Nombre> Nombres = {Nombre::Un, Nombre::Deux, Nombre::Trois, Nombre::Quatre, Nombre::Cinq, Nombre::Six,
                                    Nombre::Sept, Nombre::Huit, Nombre::Neuf};

unordered_map<TypeTactique, function<void()>> TypeTactiques = {
        {TypeTactique::Joker, []() { Tactique::jouerJoker((Joueur &j, Borne *b, Tactique *joker); }},
        {TypeTactique::Espion, []() { Tactique::jouerEspion(); }},
        {TypeTactique::PorteBouclier, []() { Tactique::jouerPorteBouclier(); }},
        {TypeTactique::ColinMaillard, []() { Tactique::jouerColinMaillard(); }},
        {TypeTactique::CombatBoue, []() { Tactique::jouerCombatDeBoue(); }},
        {TypeTactique::ChasseurTete, []() { Tactique::jouerChasseurDeTete(); }},
        {TypeTactique::Stratege, []() { Tactique::jouerStratege(); }},
        {TypeTactique::Banshee, []() { Tactique::jouerBanshee(); }},
        {TypeTactique::Traitre, []() { Tactique::jouerTraitre(); }}
};


Manche::Manche(Jeu &jeu) {

    /*
     * CRÉATION DES BORNES
     */
    std::vector<Borne *> bornes;
    for (size_t i = 0; i < BORNES; ++i) bornes.push_back(new Borne(i));
    _bornes = bornes;


    /*
     * CRÉATION DES CARTES CLAN ET TACTIQUES
     */
    Mode modeDeJeu = jeu.getModeDeJeu();
    std::vector<Carte *> cartes;

    size_t i = 0;
    for (auto c: Couleurs) {
        for (auto n: Nombres) {
            cartes.push_back(new Clan(n, c));
        }
    }

    if (modeDeJeu == Mode::tactique) {
        for (auto t: TypeTactiques) {
            cartes.push_back(new Tactique(t.first, t.second));
        }
    }

    _cartes = cartes;


    /*
     * CRÉATION DE LA PIOCHE À PARTIR DES CARTES
     */
    _pioche = new Pioche(cartes);


    /*
     * DISTRIBUTION DES CARTES AUX JOUEURS EN FONCTION DU TYPE
     */
    for (size_t j = 0; j < 7; ++j) {
        if (j == 6) {
            if (modeDeJeu == Mode::tactique) {
                _pioche->piocher("Tactique", jeu.getJoueur1());
                _pioche->piocher("Tactique", jeu.getJoueur2());
            }
        } else {
            _pioche->piocher("Clan", jeu.getJoueur1());
            _pioche->piocher("Clan", jeu.getJoueur2());
        }
    }

}