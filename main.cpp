#include <iostream>
#include "jeu.h"
#include "manche.h"

using namespace std;

void afficherTitre(){
    cout<<endl<<endl<<"      __      _           _   _               _____      _   _             "<<endl;
    cout<<"     / _\\ ___| |__   ___ | |_| |_ ___ _ __   /__   \\___ | |_| |_ ___ _ __  "<<endl;
    cout<<"     \\ \\ / __| '_ \\ / _ \\| __| __/ _ \\ '_ \\    / /\\/ _ \\| __| __/ _ \\ '_ \\ "<<endl;
    cout<<"     _\\ \\ (__| | | | (_) | |_| ||  __/ | | |  / / | (_) | |_| ||  __/ | | |"<<endl;
    cout<<"     \\__/\\___|_| |_|\\___/ \\__|\\__\\___|_| |_|  \\/   \\___/ \\__|\\__\\___|_| |_|"<<endl;
    cout<<"                                                                           "<<endl;
    cout<<"     ----------------------------------------------------------------------"<<endl;
}

int main(int argc, char **argv) {

    /*
     * Création des variables nécessaires pour jouer
     */
    bool bot;
    string nomJ1;
    string nomJ2;

    Mode modeDeJeu;

    unsigned int nbManchesGagnantes = 1;


    /*
     * Récupération du/des joueurs
     */
    system("clear");
    afficherTitre();
    cout<<"     1 - Un joueur et une I.A"<<endl;
    cout<<"     2 - Deux joueurs"<<endl;
    cout<<"     3 - Quitter le jeu"<<endl<<endl;

    int action = -1;
    cout<<"     Choisissez le programme : ";
    cin>>action;
    cout<<"     ----------------------------------------------------------------------"<<endl;

    switch (action) {
        case 1:
            bot = true;
            cout<<endl<<"     Votre pseudo : ";
            cin>>nomJ1;
            break;
        case 2:
            bot = false;
            cout<<endl<<"     Pseudo du joueur 1 : ";
            cin>>nomJ1;

            cout<<endl<<"     Pseudo du joueur 2 : ";
            cin>>nomJ2;
            break;
        default:
            return 9;
            break;
    }

    /*
     * Récupération du mode de jeu
     */
    system("clear");
    afficherTitre();
    cout<<"     1 - Normal"<<endl;
    cout<<"     2 - Tactique"<<endl<<endl;

    action = -1;
    cout<<"     Choisissez le programe : ";
    cin>>action;
    cout<<"     ----------------------------------------------------------------------"<<endl;

    switch (action) {
        case 1:
            modeDeJeu = Mode::normal;
            break;
        case 2:
            modeDeJeu = Mode::tactique;
            break;
        default:
            return 9;
            break;
    }

    /*
     * Récupération du nombre de manches gagnantes
     */
    cout<<endl<<"     Nombre de manches gagnantes : ";
    cin>>nbManchesGagnantes;

    system("clear");

    /*
     * Création du jeu
     */
    Jeu jeu = Jeu::donneInstance(nomJ1, bot, nomJ2, modeDeJeu, nbManchesGagnantes);
    while(jeu.getJoueur1().getVictoires() < jeu.getNbManchesGagnantes() && jeu.getJoueur2().getVictoires() < jeu.getNbManchesGagnantes()){
        jeu.jouerManche();
    }

    /*
     * Affichage du gagnant
     */
    if(jeu.getJoueur1().getVictoires() >= jeu.getNbManchesGagnantes()){
        cout<<jeu.getJoueur1().getPseudo()<<" a gagné le jeu !!!!";
    }else{
        cout<<jeu.getJoueur2().getPseudo()<<" a gagné le jeu !!!!";
    }

    return 0;
}
