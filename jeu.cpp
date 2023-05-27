//
// Created by Arman Saint-Marc on 24/04/2023.
//

#include "jeu.h"
#include "manche.h"

void afficherJoueur1(){
    system("clear");
    std::cout<<"\t       _                               __ "<<std::endl;
    std::cout<<"\t      | |                             /_ |"<<std::endl;
    std::cout<<"\t      | | ___  _   _  ___ _   _ _ __   | |"<<std::endl;
    std::cout<<"\t  _   | |/ _ \\| | | |/ _ \\ | | | '__|  | |"<<std::endl;
    std::cout<<"\t | |__| | (_) | |_| |  __/ |_| | |     | |"<<std::endl;
    std::cout<<"\t  \\____/ \\___/ \\__,_|\\___|\\__,_|_|     |_|"<<std::endl;
    std::cout<<"\t                                          "<<std::endl;
    std::cout<<"\t------------------------------------------"<<std::endl;
    std::cout<<"\tAppuyez sur entrer pour continuer : ";
    fflush(stdout);
    system("read");
    system("clear");

}

void afficherJoueur2(){
    system("clear");
    std::cout<<"\t       _                               ___  "<<std::endl;
    std::cout<<"\t      | |                             |__ \\ "<<std::endl;
    std::cout<<"\t      | | ___  _   _  ___ _   _ _ __     ) |"<<std::endl;
    std::cout<<"\t  _   | |/ _ \\| | | |/ _ \\ | | | '__|   / / "<<std::endl;
    std::cout<<"\t | |__| | (_) | |_| |  __/ |_| | |     / /_ "<<std::endl;
    std::cout<<"\t  \\____/ \\___/ \\__,_|\\___|\\__,_|_|    |____|"<<std::endl;
    std::cout<<"\t                                          "<<std::endl;
    std::cout<<"\t--------------------------------------------"<<std::endl;
    std::cout<<"\tAppuyez sur entrer pour continuer : ";
    fflush(stdout);
    system("read");
    system("clear");

}

//On initialise le jeu unique à un pointeur null par défaut
Jeu *Jeu::_jeuUnique = nullptr;

//On initialise le constructeur de Jeu
Jeu::Jeu(const std::string nomJ1, bool adversaireBot, const std::string nomJ2, Mode modeDeJeu, unsigned int nbManchesGagnantes) {
    _nbManchesGagnantes = nbManchesGagnantes;
    _modeDeJeu = modeDeJeu;
    _joueur1 = new Joueur(1, false, nomJ1);
    _joueur2 = new Joueur(2, adversaireBot, nomJ2);
}

//On initalise la fonction statique permettant d'avoir qu'un seul jeu en même temps
Jeu& Jeu::donneInstance(const std::string nomJ1, bool adversaireBot, const std::string nomJ2, Mode modeDeJeu, unsigned int nbManchesGagnantes) {
    if (_jeuUnique == nullptr) {
        _jeuUnique = new Jeu(nomJ1, adversaireBot, nomJ2, modeDeJeu, nbManchesGagnantes);
        return *_jeuUnique;
    }
}

//On initialise la fonction statique permettant de supprimer le jeu actuel
void Jeu::libereInstance() {
    delete _jeuUnique;
    _jeuUnique = nullptr;
}

//On initialise la fonction statique permettant de récupérer le jeu
Jeu& Jeu::getInstance() { return *_jeuUnique; }

void Jeu::jouerManche(){
    /*
     * On reset les données du joueur
     */
    _joueur1->resetCartes();
    _joueur2->resetCartes();

    _joueur1->resetTactiquesJouees();
    _joueur2->resetTactiquesJouees();

    /*
     * Création de manche
     */
    Manche* mancheActuelle = new Manche(*_jeuUnique);
    unsigned int gagnant = 0;
    /*
     * Jouer manche
     */
    while(1){
        afficherJoueur1();
        std::cout<<std::endl<<std::endl<<"\tCartes de "<<_joueur1->getPseudo()<<" : ";
        _joueur1->afficherCartes();

        mancheActuelle->afficherBornes();

        unsigned int choiceBorne = 0;
        bool borneVerif = false;


        while(choiceBorne == 0 || borneVerif == false){
            std::cout<<std::endl<<std::endl<<"\t1 - Sélectionnez une borne (n°) : ";
            std::cin>>choiceBorne;
            if(mancheActuelle->getBornes().size() >= choiceBorne && choiceBorne != 0 && mancheActuelle->getBornes()[choiceBorne-1]->estPleine(*_joueur1) == false){
                borneVerif = true;
            }else{
                borneVerif = false;
                std::cout<<std::endl<<"\t\tErreur - La borne n'existe pas ou est pleine !"<<std::endl;
            }
        }

        unsigned int choiceCarte = 0;
        bool carteVerif = false;
        while(choiceCarte == 0 || carteVerif == false){
            std::cout<<std::endl<<"\t2 - Sélectionnez une carte (n°) : ";
            std::cin>>choiceCarte;
            if(_joueur1->getCartes().size() >= choiceCarte && choiceCarte != 0 && (_joueur1->getCartes()[choiceCarte-1]->getType() == "Clan" || (_joueur1->getCartes()[choiceCarte-1]->getType() == "Tactique" && _joueur1->getNbTactiquesJouees() < _joueur2->getNbTactiquesJouees()+1)) ){
                carteVerif = true;
            }else{
                carteVerif = false;
                std::cout<<std::endl<<"\t\tErreur - La carte n'existe pas ou vous n'avez pas le droit de la jouer !"<<std::endl;
            }
        }

        mancheActuelle->getBornes()[choiceBorne-1]->poserCarte(*_joueur1, _joueur1->getCartes()[choiceCarte-1]);

        if(_modeDeJeu == Mode::normal){
            mancheActuelle->getPioche().piocher("Clan", *_joueur1);
        }else{
            int choicePioche = 0;
            while(choicePioche != 1 && choicePioche != 2){
                std::cout<<std::endl<<"\t3 - Piocher carte (1 : Clan, 2 : Tactique) : ";
                std::cin>>choicePioche;
            }
            if(choicePioche == 1){
                mancheActuelle->getPioche().piocher("Clan", *_joueur1);
            }else{
                mancheActuelle->getPioche().piocher("Tactique", *_joueur1);
            }
        }


        if(mancheActuelle->getBornes()[choiceBorne-1]->estPleine(*_joueur1) && mancheActuelle->getBornes()[choiceBorne-1]->estPleine(*_joueur2)){
            if(mancheActuelle->getBornes()[choiceBorne-1]->trouverGagnant(2, *_joueur1, *_joueur2, mancheActuelle) == 1){
                mancheActuelle->getBornes()[choiceBorne-1]->setGagnant(_joueur1);
            }else{
                mancheActuelle->getBornes()[choiceBorne-1]->setGagnant(_joueur2);
            }

            bool isGagnant = mancheActuelle->verifGagnant(*_joueur1);
            if(isGagnant == true){
                gagnant = 1;
                break;
            }
            isGagnant = mancheActuelle->verifGagnant(*_joueur2);
            if(isGagnant == true){
                gagnant = 2;
                break;
            }
        }




        afficherJoueur2();
        std::cout<<std::endl<<std::endl<<"\tCartes de "<<_joueur2->getPseudo()<<" : ";
        _joueur2->afficherCartes();

        mancheActuelle->afficherBornes();

        choiceBorne = 0;
        borneVerif = false;


        while(choiceBorne == 0 || borneVerif == false){
            std::cout<<std::endl<<std::endl<<"\t1 - Sélectionnez une borne (n°) : ";
            std::cin>>choiceBorne;
            if(mancheActuelle->getBornes().size() >= choiceBorne && choiceBorne != 0 && mancheActuelle->getBornes()[choiceBorne-1]->estPleine(*_joueur2) == false){
                borneVerif = true;
            }else{
                borneVerif = false;
                std::cout<<std::endl<<"\t\tErreur - La borne n'existe pas ou est pleine !"<<std::endl;
            }
        }

        choiceCarte = 0;
        carteVerif = false;
        while(choiceCarte == 0 || carteVerif == false){
            std::cout<<std::endl<<"\t2 - Sélectionnez une carte (n°) : ";
            std::cin>>choiceCarte;
            if(_joueur2->getCartes().size() >= choiceCarte && choiceCarte != 0 && (_joueur2->getCartes()[choiceCarte-1]->getType() == "Clan" || (_joueur2->getCartes()[choiceCarte-1]->getType() == "Tactique" && _joueur2->getNbTactiquesJouees() < _joueur1->getNbTactiquesJouees()+1)) ){
                carteVerif = true;
            }else{
                carteVerif = false;
                std::cout<<std::endl<<"\t\tErreur - La carte n'existe pas ou vous n'avez pas le droit de la jouer !"<<std::endl;
            }
        }

        mancheActuelle->getBornes()[choiceBorne-1]->poserCarte(*_joueur2, _joueur2->getCartes()[choiceCarte-1]);

        if(_modeDeJeu == Mode::normal){
            mancheActuelle->getPioche().piocher("Clan", *_joueur2);
        }else{
            int choicePioche = 0;
            while(choicePioche != 1 && choicePioche != 2){
                std::cout<<std::endl<<"\t3 - Piocher carte (1 : Clan, 2 : Tactique) : ";
                std::cin>>choicePioche;
            }
            if(choicePioche == 1){
                mancheActuelle->getPioche().piocher("Clan", *_joueur2);
            }else{
                mancheActuelle->getPioche().piocher("Tactique", *_joueur2);
            }
        }

        if(mancheActuelle->getBornes()[choiceBorne-1]->estPleine(*_joueur1) && mancheActuelle->getBornes()[choiceBorne-1]->estPleine(*_joueur2)){
            if(mancheActuelle->getBornes()[choiceBorne-1]->trouverGagnant(1, *_joueur1, *_joueur2, mancheActuelle) == 1){
                mancheActuelle->getBornes()[choiceBorne-1]->setGagnant(_joueur1);
            }else{
                mancheActuelle->getBornes()[choiceBorne-1]->setGagnant(_joueur2);
            }

            bool isGagnant = mancheActuelle->verifGagnant(*_joueur1);
            if(isGagnant == true){
                gagnant = 1;
                break;
            }
            isGagnant = mancheActuelle->verifGagnant(*_joueur2);
            if(isGagnant == true){
                gagnant = 2;
                break;
            }
        }

    }

    if(gagnant == 1){
        _joueur1->addPoint();
    }else{
        _joueur2->addPoint();
    }

    return;
}
