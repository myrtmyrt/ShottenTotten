//
// Created by Arman Saint-Marc on 24/04/2023.
//

#include "manche.h"

#define BORNES 9

std::initializer_list<Couleur> Couleurs = { Couleur::rouge, Couleur::bleu, Couleur::vert, Couleur::violet, Couleur::orange, Couleur::jaune };
std::initializer_list<Nombre> Nombres = { Nombre::un, Nombre::deux, Nombre::trois, Nombre::quatre, Nombre::cinq, Nombre::six, Nombre::sept, Nombre::huit, Nombre::neuf };

std::unordered_map<TypeTactique, void(*)()> TypeTactiques = {
        { TypeTactique::joker, Tactique::jouerJoker },
        { TypeTactique::espion, Tactique::jouerEspion },
        { TypeTactique::porteBouclier, Tactique::jouerPorteBouclier },
        { TypeTactique::colinMaillard, Tactique::jouerColinMaillard },
        { TypeTactique::combatBoue, Tactique::jouerCombatBoue },
        { TypeTactique::chasseurTete, Tactique::jouerChasseurTete},
        { TypeTactique::stratege, Tactique::jouerStratege },
        { TypeTactique::banshee, Tactique::jouerBanshee },
        { TypeTactique::traitre, Tactique::jouerTraitre }
};


Manche::Manche(Jeu &jeu) {

    /*
     * CRÉATION DES BORNES
     */
    std::vector<Borne*> bornes;
    for (size_t i = 0; i < BORNES; ++i) bornes.push_back(new Borne(i));
    _bornes = bornes;


    /*
     * CRÉATION DES CARTES CLAN ET TACTIQUES
     */
    Mode modeDeJeu = jeu.getModeDeJeu();
    std::vector<Carte*> cartes;

    size_t i = 0;
    for (auto c : Couleurs) {
        for (auto n: Nombres) {
            cartes.push_back(new Clan(n, c));
        }
    }

    if(modeDeJeu == Mode::tactique) {
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
        if(j == 6){
            if(modeDeJeu == Mode::tactique) {
                _pioche->piocher("Clan", jeu.getJoueur1());
                _pioche->piocher("Clan", jeu.getJoueur2());
            }
        }else{
            _pioche->piocher("Clan", jeu.getJoueur1());
            _pioche->piocher("Clan", jeu.getJoueur2());
        }
    }

}