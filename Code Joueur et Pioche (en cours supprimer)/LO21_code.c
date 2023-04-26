Pioche::~Pioche() {
		delete[] cartes;
	}

const Carte& Pioche::piocher() 
    {
        f (estVide()) throw SetException("Pioche vide");
        // On choisit une carte aléatoire
        size_t x = rand() % nb;
        conist Carte* c = cartes[x];
        // On décale les cartes restantes
        for (size_t i = x + 1; i < nb; ++i) cartes[i - 1] = cartes[i];
        nb--;
        // On retourne la carte piochée
        return *c;
	}




 void Joueur::setMain(){}
        
void getMain(){}
        
        
Joueur::~Joueur(){
    delete[] cartes;
}