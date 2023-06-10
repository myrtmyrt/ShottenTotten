//
// Created by Arman Saint-Marc on 09/06/2023.
//

#include "utils.h"


void clearScreen()
{
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void waitForEnter()
{
#ifdef _WIN32
    std::system("pause");
#else
    std::system("read");
#endif
}

void clearCin(){
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void afficherJoueur1(){
    clearScreen();
    std::cout<<std::endl<<"\t       _                               __ "<<std::endl;
    std::cout<<"\t      | |                             /_ |"<<std::endl;
    std::cout<<"\t      | | ___  _   _  ___ _   _ _ __   | |"<<std::endl;
    std::cout<<"\t  _   | |/ _ \\| | | |/ _ \\ | | | '__|  | |"<<std::endl;
    std::cout<<"\t | |__| | (_) | |_| |  __/ |_| | |     | |"<<std::endl;
    std::cout<<"\t  \\____/ \\___/ \\__,_|\\___|\\__,_|_|     |_|"<<std::endl;
    std::cout<<"\t                                          "<<std::endl;
    std::cout<<"\t------------------------------------------"<<std::endl;
    std::cout<<"\tAppuyez sur entrer pour continuer : ";
    fflush(stdout);
    waitForEnter();
    clearScreen();

}

void afficherJoueur2(){
    clearScreen();
    std::cout<<std::endl<<"\t       _                               ___  "<<std::endl;
    std::cout<<"\t      | |                             |__ \\ "<<std::endl;
    std::cout<<"\t      | | ___  _   _  ___ _   _ _ __     ) |"<<std::endl;
    std::cout<<"\t  _   | |/ _ \\| | | |/ _ \\ | | | '__|   / / "<<std::endl;
    std::cout<<"\t | |__| | (_) | |_| |  __/ |_| | |     / /_ "<<std::endl;
    std::cout<<"\t  \\____/ \\___/ \\__,_|\\___|\\__,_|_|    |____|"<<std::endl;
    std::cout<<"\t                                          "<<std::endl;
    std::cout<<"\t--------------------------------------------"<<std::endl;
    std::cout<<"\tAppuyez sur entrer pour continuer : ";
    fflush(stdout);
    waitForEnter();
    clearScreen();

}

Carte& askForCard(Joueur* joueur, Manche* mancheActuelle, Jeu* jeuActuel){
    unsigned int choiceCarte = 0;
    bool carteVerif = false;
    while(choiceCarte == 0 || carteVerif == false){
        std::cout<<std::endl<<"\t- Sélectionnez la carte (n°) : ";
        if(joueur->getIsBot() == true){
            choiceCarte = joueur->jouerCarteIA();
            std::cout<<choiceCarte<<std::endl;
        }else{
            std::cin>>choiceCarte;
            clearCin();
        }
        if(joueur->getCartes().size() >= choiceCarte && choiceCarte != 0){
            return *joueur->getCartes()[choiceCarte-1];
        }else{
            carteVerif = false;
            std::cout<<std::endl<<"\t\tErreur - La carte n'existe pas !"<<std::endl;
        }
    }
}

unsigned int askForBorne(Joueur& joueur, Manche* mancheActuelle, Jeu* jeuActuel, bool jouerSurBorne){
    unsigned int choiceBorne = 0;

    std::cout<<std::endl<<"\t- Sélectionnez une borne (n°) : ";
    if(joueur.getIsBot() == true){
        choiceBorne = joueur.jouerBorneIA(*mancheActuelle);
        std::cout<<choiceBorne<<std::endl;
    }else{
        std::cin>>choiceBorne;
        clearCin();
    }
    if(mancheActuelle->getBornes().size() >= choiceBorne && choiceBorne != 0){
        if((jouerSurBorne == false || (jouerSurBorne == true && mancheActuelle->getBornes()[choiceBorne-1]->estPleine(joueur) == false)) && mancheActuelle->getBornes()[choiceBorne - 1]->getGagnant() == nullptr){
            return choiceBorne;
        }else{
            std::cout<<std::endl<<"\t\tErreur - La borne est pleine !"<<std::endl;
            return 0;
        }
    }else{
        std::cout<<std::endl<<"\t\tErreur - La borne n'existe pas !"<<std::endl;
        return 0;
    }
}

void pickACardInDeck(Joueur& joueur, Manche* mancheActuelle, Jeu* jeuActuel){
    if(jeuActuel->getModeDeJeu() == Mode::normal){
        mancheActuelle->getPioche().piocher("Clan", joueur);
    }else{
        int choicePioche = 0;
        while(choicePioche != 1 && choicePioche != 2){
            std::cout<<std::endl<<"\t- Piocher carte (1 : Clan, 2 : Tactique) : ";
            if(joueur.getIsBot() == true){
                choicePioche = joueur.jouerPiocheIA();
                std::cout<<choicePioche<<std::endl;
            }else{
                std::cin>>choicePioche;
                clearCin();
            }

        }
        if(choicePioche == 1){
            mancheActuelle->getPioche().piocher("Clan", joueur);
        }else{
            mancheActuelle->getPioche().piocher("Tactique", joueur);
        }
    }
}

unsigned int askForCardToDelete(Joueur& joueur, Manche* mancheActuelle, Jeu* jeuActuel){
    unsigned int choiceCarte = 0;
    bool carteVerif = false;
    while(choiceCarte == 0 || carteVerif == false){
        std::cout<<std::endl<<"\t- Sélectionnez la carte à jetter (n°) : ";
        if(joueur.getIsBot() == true){
            choiceCarte = joueur.jouerCarteIA();
            std::cout<<choiceCarte<<std::endl;
        }else{
            std::cin>>choiceCarte;
            clearCin();
        }
        if(joueur.getCartes().size() >= choiceCarte && choiceCarte != 0){
            return choiceCarte;
        }else{
            carteVerif = false;
            std::cout<<std::endl<<"\t\tErreur - La carte n'existe pas !"<<std::endl;
        }
    }
}

unsigned int askForCardToChange(Joueur& joueur, Manche* mancheActuelle, Jeu* jeuActuel, unsigned int borneNum){
    unsigned int choiceCarte = 0;
    bool carteVerif = false;
    while(choiceCarte == 0 || carteVerif == false){
        std::cout<<std::endl<<"\t- Sélectionnez la carte à déplacer (n°) : ";
        if(joueur.getIsBot() == true){
            if(joueur.getId() == 1){
                choiceCarte = joueur.jouerAutreIA(1, mancheActuelle->getBornes()[borneNum - 1]->getCartesJoueur1().size());
                std::cout<<choiceCarte<<std::endl;
            }else{
                choiceCarte = joueur.jouerAutreIA(1, mancheActuelle->getBornes()[borneNum - 1]->getCartesJoueur2().size());
                std::cout<<choiceCarte<<std::endl;
            }

        }else{
            std::cin>>choiceCarte;
            clearCin();
        }
        if(joueur.getId() == 1){
            if(mancheActuelle->getBornes()[borneNum - 1]->getCartesJoueur1().size() < choiceCarte || choiceCarte == 0){
                std::cout<<std::endl<<"\t\tErreur - La carte n'existe pas !"<<std::endl;
                return 0;
            }
        }else{
            if(mancheActuelle->getBornes()[borneNum - 1]->getCartesJoueur2().size() < choiceCarte || choiceCarte == 0){
                std::cout<<std::endl<<"\t\tErreur - La carte n'existe pas !"<<std::endl;
                return 0;
            }
        }

        return choiceCarte;
    }
}

unsigned int askForCardToChangeOtherPlayer(Joueur& joueur, Manche* mancheActuelle, Jeu* jeuActuel, unsigned int borneNum){
    unsigned int choiceCarte = 0;
    bool carteVerif = false;
    while(choiceCarte == 0 || carteVerif == false){
        std::cout<<std::endl<<"\t- Sélectionnez la carte à déplacer (n°) : ";
        if(joueur.getIsBot() == true){
            if(joueur.getId() == 1){
                choiceCarte = joueur.jouerAutreIA(1, mancheActuelle->getBornes()[borneNum - 1]->getCartesJoueur2().size());
                std::cout<<choiceCarte<<std::endl;
            }else{
                choiceCarte = joueur.jouerAutreIA(1, mancheActuelle->getBornes()[borneNum - 1]->getCartesJoueur1().size());
                std::cout<<choiceCarte<<std::endl;
            }

        }else{
            std::cin>>choiceCarte;
            clearCin();
        }
        if(joueur.getId() == 1){
            if(mancheActuelle->getBornes()[borneNum - 1]->getCartesJoueur2().size() < choiceCarte || choiceCarte == 0){
                std::cout<<std::endl<<"\t\tErreur - La carte n'existe pas !"<<std::endl;
                return 0;
            }
        }else{
            if(mancheActuelle->getBornes()[borneNum - 1]->getCartesJoueur1().size() < choiceCarte || choiceCarte == 0){
                std::cout<<std::endl<<"\t\tErreur - La carte n'existe pas !"<<std::endl;
                return 0;
            }
        }

        return choiceCarte;
    }
}

Couleur pickAColor(Joueur& joueur){
    unsigned int choiceColor = 0;
    bool colorVerif = false;
    while(choiceColor == 0 || colorVerif == false){
        std::cout << "\tRouge(1),Bleu(2), Vert(3), Violet(4), Orange(5), Jaune(6)" <<std::endl;
        std::cout<<"\t- Sélectionnez la couleur à déplacer (n°) : ";
        if(joueur.getIsBot() == true){
            choiceColor = joueur.jouerAutreIA(1,9);
            std::cout<<choiceColor<<std::endl;
        }else{
            std::cin>>choiceColor;
            clearCin();
        }

        switch (choiceColor) {
            case 1:
                return Couleur::rouge;
                break;
            case 2:
                return Couleur::bleu;
                break;
            case 3:
                return Couleur::vert;
                break;
            case 4:
                return Couleur::violet;
                break;
            case 5:
                return Couleur::orange;
                break;
            case 6:
                return Couleur::jaune;
                break;
            default:
                colorVerif == false;
        }

    }
}

Nombre pickANumber(Joueur& joueur, unsigned int min, unsigned int max){
    unsigned int choiceNumber = 0;
    bool numberVerif = false;
    while(choiceNumber == 0 || numberVerif == false){
        std::cout<<std::endl<<"\t- Donnez le nombre de votre carte entre "<<min<<" et "<<max<<" : ";
        if(joueur.getIsBot() == true){
            choiceNumber = joueur.jouerAutreIA(min,max);
            std::cout<<choiceNumber<<std::endl;
        }else{
            std::cin>>choiceNumber;
            clearCin();
        }

        if(choiceNumber >= min && choiceNumber <= max) {
            switch (choiceNumber) {
                case 1:
                    return Nombre::un;
                    break;
                case 2:
                    return Nombre::deux;
                    break;
                case 3:
                    return Nombre::trois;
                    break;
                case 4:
                    return Nombre::quatre;
                    break;
                case 5:
                    return Nombre::cinq;
                    break;
                case 6:
                    return Nombre::six;
                    break;
                case 7:
                    return Nombre::sept;
                    break;
                case 8:
                    return Nombre::huit;
                    break;
                case 9:
                    return Nombre::neuf;
                    break;
                default:
                    numberVerif = false;
            }
        }

    }
}

unsigned int askForBorneId(Joueur& joueur, Manche* mancheActuelle, Jeu* jeuActuel){
    unsigned int choiceBorne = 0;

    std::cout<<std::endl<<"\t- Quelle borne souhaitez-vous revendiquer ? (0 pour aucune) :";
    if(joueur.getIsBot() == true){
        choiceBorne = joueur.jouerBorneIA(*mancheActuelle);
        std::cout<<choiceBorne<<std::endl;
    }else{
        std::cin>>choiceBorne;
        clearCin();
    }
    if(choiceBorne != 0) {
        if (mancheActuelle->getBornes().size() >= choiceBorne) {
            return choiceBorne;
        } else {
            std::cout << std::endl << "\t\tErreur - La borne n'existe pas !" << std::endl;
            return 0;
        }
    }else{
        return 0;
    }
}

std::vector<std::vector<Carte *>> creerPossibilites(std::vector<Carte *> cartesPosees, std::vector<Carte *> cartesNonPosees) {
    std::vector<std::vector<Carte *>> possibilites;

    int tailleMax = 3;
    for (auto &carte: cartesPosees) {
        if(carte->getType() == "Tactique") {
            if (carte->getNom() == TypeTactique::combatBoue) {
                tailleMax = 4;
            }
        }
    }

    possibilites.push_back(cartesPosees);

    while (possibilites[possibilites.size()-1].size() < tailleMax) {
        std::vector<std::vector<Carte *>> nouvellesPossibilites = possibilites;
        for (auto &possibilite: possibilites) {
            for (auto &carte: cartesNonPosees) {
                auto nouvellePossibilite = possibilite;
                nouvellePossibilite.push_back(carte);
                nouvellesPossibilites.push_back(nouvellePossibilite);
            }
        }
        possibilites = nouvellesPossibilites;
    }

    return possibilites;
}