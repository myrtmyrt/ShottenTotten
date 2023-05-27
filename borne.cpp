//
// Created by Myrtille Knockaert on 26/04/2023.
//

#include "borne.h"

void Borne::poserCarte(Joueur &j, Carte *c) {
    if (j.getId() == 1) {
        if (_cartesJoueur1.size() < _nbCartesMax) {
            _cartesJoueur1.push_back(c);

            j.supprimerCarte(c);

            if (_cartesJoueur1.size() == _nbCartesMax) {
                //revendiquerBorne();
            }
        } else throw "Attention : nombre max atteint, vous ne pouvez pas ajouter une carte.";

    } else {
        if (_cartesJoueur2.size() < _nbCartesMax) {
            _cartesJoueur2.push_back(c);

            j.supprimerCarte(c);

            if (_cartesJoueur2.size() == _nbCartesMax) {
                //revendiquerBorne();
            }
        } else throw "Attention : nombre max atteint, vous ne pouvez pas ajouter une carte.";
    }
}

void Borne::retirerCarte(Joueur &j, Carte *c) {

    if (j.getId() == 1) {
        auto it = find(_cartesJoueur1.begin(), _cartesJoueur1.end(), c);

        if (it != _cartesJoueur1.end()) {
            // La carte a été trouvée, vous pouvez maintenant la supprimer
            _cartesJoueur1.erase(it);
        } else throw "Cette carte n'est pas sur cette borne";
    }
}

void Borne::afficherCartesJ1() const{
    for (Carte* card : _cartesJoueur1) {
        card->afficher();
    }
}

void Borne::afficherCartesJ2() const{
    for (Carte* card : _cartesJoueur2) {
        card->afficher();
    }
}

void Borne::afficher() const {
    std::cout<<"\tJ1 - ";
    afficherCartesJ1();
    if(_gagnant != nullptr){
        std::cout<<"| Borne "<<_numero+1<<" (gagnée par "<<_gagnant->getPseudo()<<") | ";
    }else{
        std::cout<<"| Borne "<<_numero+1<<" | ";
    }
    afficherCartesJ2();
    std::cout<<"- J2"<<std::endl;
}

bool Borne::estPleine(Joueur &j) const {
    size_t taille;
    for (unsigned int i = 0; i < j.getCartes().size(); i++) {
        if (j.getCartes()[i].getType() == "Clan") {
            taille++;
        }
    }
    if(_nbCartesMax >= taille){

    }else{

    }
}

unsigned int Borne::trouverGagnant(unsigned int idPremier){
    bool estSomme = false;

    unsigned int pointsJ1 = calculerPoints(_cartesJoueur1);
    unsigned int pointsJ2 = calculerPoints(_cartesJoueur2);

    std::cout<<pointsJ1<<" points"<<std::endl;
    std::cout<<pointsJ2<<" points"<<std::endl;

    if(pointsJ1 > pointsJ2){
        return 1;
    }else if(pointsJ2 > pointsJ1){
        return 2;
    }else{
        if(idPremier == 1){
            return 1;
        }else{
            return 2;
        }
    }

    //AJOUTER CAS OU EGALITÉ
}

unsigned int Borne::calculerPoints(std::vector<Carte *> _cartesJoueur) {
    bool estSuiteCouleur = false;
    bool estBrelan = true;
    bool estCouleur = true;
    bool estSuite = true;

    size_t taille = _cartesJoueur.size();

    int suiteNombre[taille];
    Couleur suiteCouleur[taille];

    /*
     * Traiter toutes les cartes du J1
     */
    size_t i = 0;
    for (Carte* card : _cartesJoueur) {
        if(card->getType() == "Clan") {
            suiteNombre[i] = toInt(card->getNombre());
            suiteCouleur[i++] = card->getCouleur();
        }else{
            card->jouer();
        }
    }

    /*
     * Mettre ordre croissant les cartes
     */
    for(int i=0; i<taille; i++)
    {
        for(int j=i+1; j<taille; j++) {
            if(suiteNombre[i]>suiteNombre[j])
            {
                int temp = suiteNombre[i];
                suiteNombre[i] = suiteNombre[j];
                suiteNombre[j] = temp;
            }
        }
    }

    /*
     * Verif si nombre est suite
     */
    for(int i=0; i<taille; i++)
    {
        if(i != taille-1){
            if(suiteNombre[i]+1 != suiteNombre[i+1]){
                estSuite = false;
            }
        }
    }

    /*
     * Verif si est brelan
     */
    for(int i=0; i<taille; i++)
    {
        if(i != taille-1){
            if(suiteNombre[i] != suiteNombre[i+1]){
                estBrelan = false;
            }
        }
    }

    /*
     * Verif si couleur
     */
    for(int i=0; i<taille; i++)
    {
        if(i != taille-1){
            if(suiteCouleur[i] != suiteCouleur[i+1]){
                estCouleur = false;
            }
        }
    }

    /*
     * Somme du tableau
     */
    unsigned int somme = 0;
    for(int i=0; i<taille; i++)
    {
        somme += suiteNombre[i];
    }

    /*
     * Verif si suite couleur
     */
    if(estSuite && estCouleur){
        estSuiteCouleur = true;
    }

    if(estSuiteCouleur){
        return somme+50*4;
    }else if(estBrelan){
        return somme+50*3;
    }else if(estCouleur){
        return somme+50*2;
    }else if(estSuite){
        return somme+50;
    }else{
        return somme;
    }
}

int toInt(Nombre n){
    switch (n) {
        case Nombre::Un: return 1;
        case Nombre::Deux: return 2;
        case Nombre::Trois: return 3;
        case Nombre::Quatre: return 4;
        case Nombre::Cinq: return 5;
        case Nombre::Six: return 6;
        case Nombre::Sept: return 7;
        case Nombre::Huit: return 8;
        case Nombre::Neuf: return 9;
        default: std::cout<<"erreur";
    }
}

