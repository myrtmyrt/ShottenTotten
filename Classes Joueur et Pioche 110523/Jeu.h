#ifndef PROJET_JEU_H
#define PROJET_JEU_H

using namespace std;

// classe pour gérer les exceptions
class JeuException {
public:
    JeuException(const string& i) :info(i) {}
    string getInfo() const { return info; }
private:
    string info;
};


class Jeu {
private:
    static Jeu *jeuUnique;
    int _nbManchesGagnantes;
    int _victoireJoueur1;
    int _victoireJoueur2;
    bool _adversaireBot;
    int _modeDeJeu;

    Jeu(int nbManchesGagnantes = 1, bool adversaireBot = true, int modeDeJeu = 1);

public:
    int getNbManchesGagnantes() const { return _nbManchesGagnantes; }
    int getmodeDeJeu() const { return _modeDeJeu; }
    static Jeu &donneInstance(int nbManchesGagnantes, bool adversaireBot,int modeDeJeu);
    static void libereInstance();
    static Jeu &getInstance();
};
#endif //PROJET_JEU_H

