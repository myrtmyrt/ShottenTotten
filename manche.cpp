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

void Manche::afficherBornes() const {
    std::cout<<std::endl<<std::endl;
    for (Borne* borne : _bornes) {
        borne->afficher();
    }
}

bool Manche::verifGagnant(Joueur& jou) const{
    unsigned int bornesWin = 0;
    unsigned int bornesMaxSuiteWin = 0;
    unsigned int bornesSuiteWin = 0;
    unsigned int idLastWin = jou.getId();

    for (Borne* borne : _bornes) {
        if(borne->getGagnant() != nullptr) {
            if (borne->getGagnant()->getId() == jou.getId()) {
                bornesWin++;
                if (idLastWin == jou.getId()) {
                    bornesSuiteWin++;
                    if (bornesSuiteWin > bornesMaxSuiteWin) {
                        bornesMaxSuiteWin = bornesSuiteWin;
                    }
                } else {
                    bornesSuiteWin = 1;
                }
            }
            idLastWin = jou.getId();
        }
    }

    if(bornesMaxSuiteWin >= 3 || bornesWin >= 5){
        return true;
    }else{
        return false;
    }
}