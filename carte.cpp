//
// Created by Arman Saint-Marc on 06/05/2023.
//

#include "carte.h"
#include "joueur.h"
#include "borne.h"
#include "manche.h"

using namespace std;

std::string toString(Couleur c) {
    switch (c) {
        case Couleur::rouge: return "R";
        case Couleur::vert: return "E";
        case Couleur::jaune: return "J";
        case Couleur::orange: return "O";
        case Couleur::violet: return "V";
        case Couleur::bleu: return "B";
        default: std::cout<<"erreur";
    }
}

std::string toString(Nombre v) {
    switch (v) {
        case Nombre::un: return "1";
        case Nombre::deux: return "2";
        case Nombre::trois: return "3";
        case Nombre::quatre: return "4";
        case Nombre::cinq: return "5";
        case Nombre::six: return "6";
        case Nombre::sept: return "7";
        case Nombre::huit: return "8";
        case Nombre::neuf: return "9";
        default: std::cout<<"erreur";
    }
}

std::string toString(TypeTactique v) {
    switch (v) {
        case TypeTactique::porteBouclier: return "Porte bouclier";
        case TypeTactique::espion: return "Espion";
        case TypeTactique::joker: return "Joker";
        case TypeTactique::colinMaillard: return "Colin maillard";
        case TypeTactique::combatBoue: return "Combat boue";
        case TypeTactique::chasseurTete: return "Chasseur tête";
        case TypeTactique::stratege: return "Stratege";
        case TypeTactique::banshee: return "Banshee";
        case TypeTactique::traitre: return "Traitre";
        default: std::cout<<"erreur";
    }
}

std::ostream& operator<<(std::ostream& f, Couleur c) { f << toString(c); return f; }
std::ostream& operator<<(std::ostream& f, Nombre v) {	f << toString(v); return f; }
std::ostream& operator<<(std::ostream& f, TypeTactique v) {	f << toString(v); return f; }

void printTextInColor(Couleur color, Nombre numero) {
    switch (color) {
        case Couleur::rouge:
            std::cout << "\033[31m"; // Mettre texte en rouge
            break;
        case Couleur::vert:
            std::cout << "\033[32m"; // Mettre texte en vert
            break;
        case Couleur::bleu:
            std::cout << "\033[34m"; // Mettre texte en bleu
            break;
        case Couleur::violet:
            std::cout << "\033[35m"; // Mettre texte en violet
            break;
        case Couleur::orange:
            std::cout << "\033[38;5;208m"; // Mettre texte en orange
            break;
        case Couleur::jaune:
            std::cout << "\033[93m"; // Mettre texte en jaune
            break;
        default:
            break;
    }

    std::cout << "["<<numero<<"]" << "\033[m "; // Reset text color to default
}

void printTactique(TypeTactique v) {
    std::cout << "["<<v<<"] ";
}

void Tactique::jouer(Joueur &j, Borne *b, Manche* m) {
    _function(j, b, m);
}

void Tactique::jouerJoker(Joueur &j, Borne *b, Manche* m) {
    Couleur c;
    Nombre n;
    cout << "Donne la couleur de la carte désirée : " << endl;
    cout << "Rouge(1),Bleu(2), Vert(3), Violet(4), Orange(5), Jaune(6)" << endl;
    int couleurInput;
    cin >> couleurInput;

    // on convertit le nombre en la couleur correspondante dans l'enum
    switch (couleurInput) {
        case 1:
            c = Couleur::rouge;
            break;
        case 2:
            c = Couleur::bleu;
            break;
        case 3:
            c = Couleur::vert;
            break;
        case 4:
            c = Couleur::violet;
            break;
        case 5:
            c = Couleur::orange;
            break;
        case 6:
            c = Couleur::jaune;
            break;
        default:
            cout << "Couleur invalide !" << endl;
    }
    cout << "Donne la nombre en chiffre de la carte désirée (allant de 1 à 9): ";
    int nombreInput;
    cin >> nombreInput;

    // on convertit le nombre avec le nombre correspondant dans l'enum
    switch (nombreInput) {
        case 1:
            n = Nombre::un;
            break;
        case 2:
            n = Nombre::deux;
            break;
        case 3:
            n = Nombre::trois;
            break;
        case 4:
            n = Nombre::quatre;
            break;
        case 5:
            n = Nombre::cinq;
            break;
        case 6:
            n = Nombre::six;
            break;
        case 7:
            n = Nombre::sept;
            break;
        case 8:
            n = Nombre::huit;
            break;
        case 9:
            n = Nombre::neuf;
            break;
        default:
            cout << "Nombre invalide !" << endl;
    }

    vector<Carte*> cartes;
    if (j.getId() == 1) {
        cartes = b->getCartesJoueur1();
    } else {
        cartes = b->getCartesJoueur2();
    }


    size_t index = 0;
    for (Carte* card : cartes) {
        if(card->getType() == "Tactique") {
            if(card->getNom() == TypeTactique::joker){
                break;
            }
        }
        index++;
    }


    b->retirerCarte(j, cartes[index]);

    Carte* newCarte = new Clan(n, c);
    b->changerCarte(j, newCarte);

}

void Tactique::jouerEspion(Joueur &j, Borne *b, Manche* m) {
    Couleur c;
    Nombre n = Nombre::sept;

    cout << "Donne la couleur de la carte désirée : " << endl;
    cout << "Rouge(1),Bleu(2), Vert(3), Violet(4), Orange(5), Jaune(6)" << endl;
    int couleurInput;
    cin >> couleurInput;

    // on convertit le nombre en la couleur correspondante dans l'enum
    switch (couleurInput) {
        case 1:
            c = Couleur::rouge;
            break;
        case 2:
            c = Couleur::bleu;
            break;
        case 3:
            c = Couleur::vert;
            break;
        case 4:
            c = Couleur::violet;
            break;
        case 5:
            c = Couleur::orange;
            break;
        case 6:
            c = Couleur::jaune;
            break;
        default:
            cout << "Couleur invalide !" << endl;
    }

    vector<Carte*> cartes;
    if (j.getId() == 1) {
        cartes = b->getCartesJoueur1();
    } else {
        cartes = b->getCartesJoueur2();
    }


    size_t index = 0;
    for (Carte* card : cartes) {
        if(card->getType() == "Tactique") {
            if(card->getNom() == TypeTactique::espion){
                break;
            }
        }
        index++;
    }


    b->retirerCarte(j, cartes[index]);

    Carte* newCarte = new Clan(n, c);
    b->changerCarte(j, newCarte);

};

void Tactique::jouerPorteBouclier(Joueur &j, Borne *b, Manche* m) {
    Couleur c;
    Nombre n;
    cout << "Donne la couleur de la carte désirée : " << endl;
    cout << "Rouge(1),Bleu(2), Vert(3), Violet(4), Orange(5), Jaune(6)" << endl;
    int couleurInput;
    cin >> couleurInput;

    // on convertit le nombre en la couleur correspondante dans l'enum
    switch (couleurInput) {
        case 1:
            c = Couleur::rouge;
            break;
        case 2:
            c = Couleur::bleu;
            break;
        case 3:
            c = Couleur::vert;
            break;
        case 4:
            c = Couleur::violet;
            break;
        case 5:
            c = Couleur::orange;
            break;
        case 6:
            c = Couleur::jaune;
            break;
        default:
            cout << "Couleur invalide !" << endl;
    }
    cout << "Donne la nombre en chiffre de la carte désirée (allant de 1 à 3): ";
    int nombreInput;
    cin >> nombreInput;

    // on convertit le nombre avec le nombre correspondant dans l'enum
    switch (nombreInput) {
        case 1:
            n = Nombre::un;
            break;
        case 2:
            n = Nombre::deux;
            break;
        case 3:
            n = Nombre::trois;
            break;
        default:
            cout << "Nombre invalide !" << endl;
    }

    vector<Carte*> cartes;
    if (j.getId() == 1) {
        cartes = b->getCartesJoueur1();
    } else {
        cartes = b->getCartesJoueur2();
    }


    size_t index = 0;
    for (Carte* card : cartes) {
        if(card->getType() == "Tactique") {
            if(card->getNom() == TypeTactique::porteBouclier){
                break;
            }
        }
        index++;
    }


    b->retirerCarte(j, cartes[index]);

    Carte* newCarte = new Clan(n, c);
    b->changerCarte(j, newCarte);

}

void Tactique::jouerColinMaillard(Joueur &j, Borne *b, Manche* m) {}

void Tactique::jouerCombatBoue(Joueur &j, Borne *b, Manche* m) {
        b->setNbCartesMax(4);
}

void Tactique::jouerChasseurTete(Joueur &j, Borne *b, Manche *m) {
    for (int i = 0; i < 3; ++i) {
        int choicePioche = 0;
        while(choicePioche != 1 && choicePioche != 2){
            std::cout<<std::endl<<"\t"<<i<<" - Piocher carte (1 : Clan, 2 : Tactique) : ";
            std::cin>>choicePioche;
        }
        if(choicePioche == 1){
            m->getPioche().piocher("Clan", j);
        }else{
            m->getPioche().piocher("Tactique", j);
        }
    }


    for (int i = 0; i < 2; ++i) {
        j.afficherCartes();
        unsigned int choiceCarte = 0;
        bool carteVerif = false;
        while (choiceCarte == 0 || carteVerif == false) {
            std::cout << std::endl << "\t" << i << " - Sélectionnez une carte (n°) : ";
            std::cin >> choiceCarte;
            if (j.getCartes().size() >= choiceCarte && choiceCarte != 0) {
                carteVerif = true;
            } else {
                carteVerif = false;
                std::cout << std::endl << "\t\tErreur - La carte n'existe pas ou vous n'avez pas le droit de la jouer !"
                          << std::endl;
            }
        }

        j.supprimerCarte(j.getCartes()[choiceCarte-1]);
    }
}

void Tactique::jouerStratege(Joueur &j, Borne *b, Manche *m) {
    unsigned int choiceBorne = 0;
    bool borneVerif = false;

    m->afficherBornes();

    while(choiceBorne == 0 || borneVerif == false){
        std::cout<<std::endl<<std::endl<<"\t1 - Sélectionnez la borne (n°) : ";
        std::cin>>choiceBorne;
        if(m->getBornes().size() >= choiceBorne && choiceBorne != 0 && m->getBornes()[choiceBorne-1]->getGagnant() == nullptr){
            borneVerif = true;
        }else{
            borneVerif = false;
            std::cout<<std::endl<<"\t\tErreur - La borne ne peut pas être choisie !"<<std::endl;
        }
    }

    Carte* carteChoisie;
    unsigned int choiceCarte = 0;
    bool carteVerif = false;
    while(choiceCarte == 0 || carteVerif == false){
        std::cout<<std::endl<<"\t2 - Sélectionnez la carte (n°) : ";
        std::cin>>choiceCarte;
        if(j.getId() == 1){
            if(m->getBornes()[choiceBorne-1]->getCartesJoueur1().size() >= choiceCarte && choiceCarte != 0 ){
                carteVerif = true;
                carteChoisie = m->getBornes()[choiceBorne-1]->getCartesJoueur1()[choiceCarte];
            }else{
                carteVerif = false;
                std::cout<<std::endl<<"\t\tErreur - La carte n'existe pas ou vous n'avez pas le droit de la prendre !"<<std::endl;
            }
        }else{
            if(m->getBornes()[choiceBorne-1]->getCartesJoueur2().size() >= choiceCarte && choiceCarte != 0 ){
                carteVerif = true;
                carteChoisie = m->getBornes()[choiceBorne-1]->getCartesJoueur2()[choiceCarte];
            }else{
                carteVerif = false;
                std::cout<<std::endl<<"\t\tErreur - La carte n'existe pas ou vous n'avez pas le droit de la prendre !"<<std::endl;
            }
        }

    }

    //Possibilité supprimer carte

    unsigned int choiceBorneNew = 0;
    bool borneVerifNew = false;

    while(choiceBorneNew == 0 || borneVerifNew == false){
        std::cout<<std::endl<<std::endl<<"\t3 - Sélectionnez la borne de destination (n°) : ";
        std::cin>>choiceBorneNew;
        if(m->getBornes().size() >= choiceBorne && choiceBorne != 0 && m->getBornes()[choiceBorne-1]->estPleine(j) == false){
            borneVerif = true;
        }else{
            borneVerif = false;
            std::cout<<std::endl<<"\t\tErreur - La borne n'existe pas ou est pleine !"<<std::endl;
        }
    }

    m->getBornes()[choiceBorne-1]->retirerCarte(j, carteChoisie);

    m->getBornes()[choiceBorneNew-1]->changerCarte(j, carteChoisie);

}

void Tactique::jouerBanshee(Joueur &j, Borne *b, Manche *m) {
    unsigned int choiceBorne = 0;
    bool borneVerif = false;

    m->afficherBornes();

    while(choiceBorne == 0 || borneVerif == false){
        std::cout<<std::endl<<std::endl<<"\t1 - Sélectionnez la borne adverse (n°) : ";
        std::cin>>choiceBorne;
        if(m->getBornes().size() >= choiceBorne && choiceBorne != 0 && m->getBornes()[choiceBorne-1]->getGagnant() == nullptr){
            borneVerif = true;
        }else{
            borneVerif = false;
            std::cout<<std::endl<<"\t\tErreur - La borne ne peut pas être choisie !"<<std::endl;
        }
    }

    Carte* carteChoisie;
    unsigned int choiceCarte = 0;
    bool carteVerif = false;
    while(choiceCarte == 0 || carteVerif == false){
        std::cout<<std::endl<<"\t2 - Sélectionnez la carte (n°) : ";
        std::cin>>choiceCarte;
        if(j.getId() == 1){
            if(m->getBornes()[choiceBorne-1]->getCartesJoueur2().size() >= choiceCarte && choiceCarte != 0 ){
                carteVerif = true;
                carteChoisie = m->getBornes()[choiceBorne-1]->getCartesJoueur2()[choiceCarte];
            }else{
                carteVerif = false;
                std::cout<<std::endl<<"\t\tErreur - La carte n'existe pas ou vous n'avez pas le droit de la prendre !"<<std::endl;
            }
        }else{
            if(m->getBornes()[choiceBorne-1]->getCartesJoueur1().size() >= choiceCarte && choiceCarte != 0 ){
                carteVerif = true;
                carteChoisie = m->getBornes()[choiceBorne-1]->getCartesJoueur1()[choiceCarte];
            }else{
                carteVerif = false;
                std::cout<<std::endl<<"\t\tErreur - La carte n'existe pas ou vous n'avez pas le droit de la prendre !"<<std::endl;
            }
        }

    }

    m->getBornes()[choiceBorne-1]->retirerCarte(j, carteChoisie);

}

void Tactique::jouerTraitre(Joueur &j, Borne *b, Manche *m) {
    unsigned int choiceBorne = 0;
    bool borneVerif = false;

    m->afficherBornes();

    while(choiceBorne == 0 || borneVerif == false){
        std::cout<<std::endl<<std::endl<<"\t1 - Sélectionnez la borne adverse (n°) : ";
        std::cin>>choiceBorne;
        if(m->getBornes().size() >= choiceBorne && choiceBorne != 0 && m->getBornes()[choiceBorne-1]->getGagnant() == nullptr){
            borneVerif = true;
        }else{
            borneVerif = false;
            std::cout<<std::endl<<"\t\tErreur - La borne ne peut pas être choisie !"<<std::endl;
        }
    }

    Carte* carteChoisie;
    unsigned int choiceCarte = 0;
    bool carteVerif = false;
    while(choiceCarte == 0 || carteVerif == false){
        std::cout<<std::endl<<"\t2 - Sélectionnez la carte (n°) : ";
        std::cin>>choiceCarte;
        if(j.getId() == 1){
            if(m->getBornes()[choiceBorne-1]->getCartesJoueur2().size() >= choiceCarte && choiceCarte != 0 && m->getBornes()[choiceBorne-1]->getCartesJoueur2()[choiceCarte]->getType() == "Clan"){
                carteVerif = true;
                carteChoisie = m->getBornes()[choiceBorne-1]->getCartesJoueur2()[choiceCarte];
            }else{
                carteVerif = false;
                std::cout<<std::endl<<"\t\tErreur - La carte n'existe pas ou vous n'avez pas le droit de la prendre !"<<std::endl;
            }
        }else{
            if(m->getBornes()[choiceBorne-1]->getCartesJoueur1().size() >= choiceCarte && choiceCarte != 0 && m->getBornes()[choiceBorne-1]->getCartesJoueur1()[choiceCarte]->getType() == "Clan"){
                carteVerif = true;
                carteChoisie = m->getBornes()[choiceBorne-1]->getCartesJoueur1()[choiceCarte];
            }else{
                carteVerif = false;
                std::cout<<std::endl<<"\t\tErreur - La carte n'existe pas ou vous n'avez pas le droit de la prendre !"<<std::endl;
            }
        }

    }

    unsigned int choiceBorneNew = 0;
    bool borneVerifNew = false;

    while(choiceBorneNew == 0 || borneVerifNew == false){
        std::cout<<std::endl<<std::endl<<"\t3 - Sélectionnez la borne de destination (n°) : ";
        std::cin>>choiceBorneNew;
        if(m->getBornes().size() >= choiceBorne && choiceBorne != 0 && m->getBornes()[choiceBorne-1]->estPleine(j) == false){
            borneVerif = true;
        }else{
            borneVerif = false;
            std::cout<<std::endl<<"\t\tErreur - La borne n'existe pas ou est pleine !"<<std::endl;
        }
    }

    m->getBornes()[choiceBorne-1]->retirerCarte(j, carteChoisie);

    m->getBornes()[choiceBorneNew-1]->changerCarte(j, carteChoisie);

}