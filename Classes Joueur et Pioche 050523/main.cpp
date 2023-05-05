#include "Joueur_Pioche.h"
using namespace Joueur_Pioche;

int main() {

	printCouleurs();
	printNombres();
	Pioche p;
	string na;

    cout << "Enter You Name Please: " << endl;
    cin >> na;
	Joueur j(2,na,true );
	std::cout<<"Numero : "<<j.getNumero()<<std::endl;
	std::cout<<"Nom : "<< j.getName()<<std::endl;
	bool b=j.getHuman();
	if (b==1){
        std::cout<<"Humain"<<std::endl;
	}
	else{
        std::cout<<"Machine"<<std::endl;
	}
	std::cout<<"Nombre de cartes : "<<j.getNbCartes()<<std::endl;
	j.distribution(p);
	j.afficherCartes();

	system("pause");
	return 1;
}
