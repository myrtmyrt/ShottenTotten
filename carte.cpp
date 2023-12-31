//
// Created by Myrtille Knockaert on 26/04/2023.
//

#include "carte.h"
#include "joueur.h"
#include "borne.h"
#include "pioche.h"
#include "manche.h"

using namespace std;


std::string toString(Couleur c) {
    switch (c) {
        case Couleur::Rouge: return "R";
        case Couleur::Vert: return "E";
        case Couleur::Jaune: return "J";
        case Couleur::Orange: return "O";
        case Couleur::Violet: return "V";
        case Couleur::Bleu: return "B";
        default: std::cout<<"erreur";
    }
}

std::string toString(Nombre v) {
    switch (v) {
        case Nombre::Un: return "1";
        case Nombre::Deux: return "2";
        case Nombre::Trois: return "3";
        case Nombre::Quatre: return "4";
        case Nombre::Cinq: return "5";
        case Nombre::Six: return "6";
        case Nombre::Sept: return "7";
        case Nombre::Huit: return "8";
        case Nombre::Neuf: return "9";
        default: std::cout<<"erreur";
    }
}

std::ostream& operator<<(std::ostream& f, Couleur c) { f << toString(c); return f; }
std::ostream& operator<<(std::ostream& f, Nombre v) {	f << toString(v); return f; }

void printTextInColor(Couleur color, Nombre numero) {
    switch (color) {
        case Couleur::Rouge:
            std::cout << "\033[31m"; // Mettre texte en rouge
            break;
        case Couleur::Vert:
            std::cout << "\033[32m"; // Mettre texte en vert
            break;
        case Couleur::Bleu:
            std::cout << "\033[34m"; // Mettre texte en bleu
            break;
        case Couleur::Violet:
            std::cout << "\033[35m"; // Mettre texte en violet
            break;
        case Couleur::Orange:
            std::cout << "\033[38;5;208m"; // Mettre texte en orange
            break;
        case Couleur::Jaune:
            std::cout << "\033[93m"; // Mettre texte en jaune
            break;
        default:
            break;
    }

    std::cout << "["<<numero<<"]" << "\033[m "; // Reset text color to default
}

void Tactique::jouerJoker(Joueur &j, Borne *b,Tactique* joker) {
    Couleur c;
    Nombre n;
    cout << "Donne la couleur de la carte désirée : " << endl;
    cout << "Rouge(1),Bleu(2), Vert(3), Violet(4), Orange(5), Jaune(6)" << endl;
    int couleurInput;
    cin >> couleurInput;

    // on convertit le nombre en la couleur correspondante dans l'enum
    switch (couleurInput) {
        case 1:
            c = Couleur::Rouge;
            break;
        case 2:
            c = Couleur::Bleu;
            break;
        case 3:
            c = Couleur::Vert;
            break;
        case 4:
            c = Couleur::Violet;
            break;
        case 5:
            c = Couleur::Orange;
            break;
        case 6:
            c = Couleur::Jaune;
            break;
        default:
            cout << "Couleur invalide !" << endl;
    }
    cout << "Donne la nombre en chiffre de la carte désirée (allant de 1 à 9): " << endl;
    int nombreInput;
    cin >> nombreInput;

    // on convertit le nombre avec le nombre correspondant dans l'enum
    switch (nombreInput) {
        case 1:
            n = Nombre::Un;
            break;
        case 2:
            n = Nombre::Deux;
            break;
        case 3:
            n = Nombre::Trois;
            break;
        case 4:
            n = Nombre::Quatre;
            break;
        case 5:
            n = Nombre::Cinq;
            break;
        case 6:
            n = Nombre::Six;
            break;
        case 7:
            n = Nombre::Sept;
            break;
        case 8:
            n = Nombre::Huit;
            break;
        case 9:
            n = Nombre::Neuf;
            break;
        default:
            cout << "Nombre invalide !" << endl;
    }
    if (j.getId() == 1) {
        auto posJoker = find(b->getCartesJoueur1().begin(), b->getCartesJoueur1().end(), joker);
        b->getCartesJoueur1().erase(posJoker);
    } else {
        auto posJoker= find(b->getCartesJoueur2().begin(), b->getCartesJoueur2().end(), joker);
        b->getCartesJoueur2().erase(posJoker);
    }
    Clan *newCarte = new Clan(n, c);
    b->poserCarte(j, newCarte);
}


void Tactique::jouerEspion(Joueur &j, Borne *b, Tactique *espion) {
    Couleur c;
    Nombre n = Nombre::Sept;
    // On récupère la couleur de la carte que le joueur choisi
    cout << "Donne la couleur de la carte désirée : " << endl;
    cout << "Rouge(1),Bleu(2), Vert(3), Violet(4), Orange(5), Jaune(6)" << endl;
    int couleurInput;
    cin >> couleurInput;

    // on convertit le nombre en la couleur correspondante dans l'enum
    switch (couleurInput) {
        case 1:
            c = Couleur::Rouge;
            break;
        case 2:
            c = Couleur::Bleu;
            break;
        case 3:
            c = Couleur::Vert;
            break;
        case 4:
            c = Couleur::Violet;
            break;
        case 5:
            c = Couleur::Orange;
            break;
        case 6:
            c = Couleur::Jaune;
            break;
        default:
            cout << "Couleur invalide !" << endl;
    }
    //On récupère le chiffre désiré par le joueur pour la carte

    cout << "Donne la nombre en chiffre de la carte désirée (allant de 1 à 9): " << endl;
    int nombreInput;
    cin >> nombreInput;
    if (j.getId() == 1) {
        auto posJoker = find(b->getCartesJoueur1().begin(), b->getCartesJoueur1().end(),espion);
        b->getCartesJoueur1().erase(posJoker);
    } else {
        auto posJoker= find(b->getCartesJoueur2().begin(), b->getCartesJoueur2().end(), espion);
        b->getCartesJoueur2().erase(posJoker);
    }
    Clan *newCarte = new Clan(n, c);
    b->poserCarte(j, newCarte);

};

void Tactique::jouerPorteBouclier(Joueur &j, Borne *b, Tactique* porteBouclier) {
    Couleur c;
    Nombre n;
    cout << "Donne la couleur de la carte désirée : " << endl;
    cout << "Rouge(1),Bleu(2), Vert(3), Violet(4), Orange(5), Jaune(6)" << endl;
    int couleurInput;
    cin >> couleurInput;

    // on convertit le nombre en la couleur correspondante dans l'enum
    switch (couleurInput) {
        case 1:
            c = Couleur::Rouge;
            break;
        case 2:
            c = Couleur::Bleu;
            break;
        case 3:
            c = Couleur::Vert;
            break;
        case 4:
            c = Couleur::Violet;
            break;
        case 5:
            c = Couleur::Orange;
            break;
        case 6:
            c = Couleur::Jaune;
            break;
        default:
            cout << "Couleur invalide !" << endl;
    }
    cout << "Donne la nombre en chiffre de la carte désirée (allant de 1 à 3): " << endl;
    int nombreInput;
    cin >> nombreInput;

    // on convertit le nombre avec le nombre correspondant dans l'enum
    switch (nombreInput) {
        case 1:
            n = Nombre::Un;
            break;
        case 2:
            n = Nombre::Deux;
            break;
        case 3:
            n = Nombre::Trois;
            break;
        default:
            cout << "Nombre invalide !" << endl;
    }

    if (j.getId() == 1) {
        auto posJoker = find(b->getCartesJoueur1().begin(), b->getCartesJoueur1().end(),porteBouclier);
        b->getCartesJoueur1().erase(posJoker);
    } else {
        auto posJoker= find(b->getCartesJoueur2().begin(), b->getCartesJoueur2().end(), porteBouclier);
        b->getCartesJoueur2().erase(posJoker);
    }

    Clan* newCarte = new Clan(n, c);
    b->poserCarte(j, newCarte);
}


void Tactique::jouerCombatBoue(Borne *b) {
    b->setNbCartesMax(4);
}

void Tactique::jouerChasseurTete(Joueur& j, Pioche p,Borne* b,string t) {
    for (int i = 0; i < 2; i++) {
        if (j.getId()==1){
            p.piocher(t,j);
        }else{
            p.piocher(t,j);
        }

    }
    cout << "il faut choisir une carte à supprimer"<<endl;
    cout<<"Tapez le numéro de la premiere carte à supprimer "<<endl;
    unsigned int c1;
    cin>>c1;
    cout<<"Tapez le numéro de la premiere carte à supprimer "<<endl;
    unsigned int c2;
    cin>>c2;
    b->retirerCarte(j,j.getCartes()[c1]);
    b->retirerCarte(j,j.getCartes()[c2]);

}

void Tactique::jouerStratege(Joueur& j, Pioche p,Manche* m,string t) {
    //choisissez une carte Clan ou Tactique de votre côté de la frontière sur une Borne non revendiquée.
    cout<<"Tapez le numéro de la borne sur laquelle vous souhaitez déplacer ou défausser une carte"<<endl;
    unsigned int indexBorne;
    cout<<"Tapez le numéro de la carte que vous souhaitez déplacer ou défausser sur la borne n°"<<indexBorne<<endl;
    unsigned int indexCarte;
    cout<<"Souhaitez vous la défausser (tapez 0) ou la place sur une autre borne(tapez le numero de la borne laquelle vous souhaitez placer la carte)";
    unsigned int action;
    if(action>0 and action<10){
        if (j.getId()==1){
            m->getBornes()[action]->poserCarte(j, m->getBornes()[indexBorne]->getCartesJoueur1()[indexCarte]);
        }else{
            m->getBornes()[action]->poserCarte(j, m->getBornes()[indexBorne]->getCartesJoueur2()[indexCarte]);
        }
    }
    if (j.getId()==1){
        m->getBornes()[indexBorne]->retirerCarte(j, m->getBornes()[indexBorne]->getCartesJoueur1()[indexCarte]);
    }else{
        m->getBornes()[indexBorne]->retirerCarte(j, m->getBornes()[indexBorne]->getCartesJoueur2()[indexCarte]);
    }
}

void Tactique::jouerBanshee(Joueur &j, Manche* m) {
    //choisissez une carte Clan ou Tactique du côté adverse de la frontière sur une Borne non revendiquée et défaussez-la face
    //visible à côté de la pioche.
    cout<<"Tapez le numéro de la borne sur laquelle vous souhaitez déplacer ou défausser une carte"<<endl;
    unsigned int indexBorne;
    cout<<"Tapez le numéro de la carte que vous souhaitez déplacer ou défausser sur la borne n°"<<indexBorne<<endl;
    unsigned int indexCarte;
    if (j.getId()==1){
        m->getBornes()[indexBorne]->retirerCarte(j,m->getBornes()[indexBorne]->getCartesJoueur1()[indexCarte]);
    }else{
        m->getBornes()[indexBorne]->retirerCarte(j, m->getBornes()[indexBorne]->getCartesJoueur2()[indexCarte]);
    }
}

void Tactique::jouerTraitre(Joueur &j,Manche* m) {
    unsigned int indexBorne;
    cout<<"Tapez le numéro de la borne de votre adversaire ou se situe la carte que vous souhaitez déplacer de votre côté"<<endl;
    cin>>indexBorne;
    unsigned int indexCarte;
    cout<<"Tapez le numéro de la carte que vous souhaitez déplacer de votre côté "<<endl;
    cin>>indexCarte;
    unsigned int index2;
    cout<<"Tapez le numéro de la borne sur laquelle vous souhaitez poser la carte "<<endl;
    cin>>index2;
    //on vérifie que la carte est bien une carte clan
    if (m->getBornes()[indexBorne]->getCartesJoueur1()[indexCarte]->getType()=="Clan"){
        if (j.getId()==1){
            m->getBornes()[index2]->poserCarte(j,m->getBornes()[indexBorne]->getCartesJoueur1()[indexCarte]);
        }else{
            m->getBornes()[index2]->poserCarte(j,m->getBornes()[indexBorne]->getCartesJoueur1()[indexCarte]);
        }
        if (j.getId()==1){
            m->getBornes()[indexBorne]->retirerCarte(j,m->getBornes()[indexBorne]->getCartesJoueur1()[indexCarte]);
        }else{
            m->getBornes()[indexBorne]->retirerCarte(j,m->getBornes()[indexBorne]->getCartesJoueur1()[indexCarte]);
        }
    } else throw "La carte choisie n'est pas une carte clan";


}




