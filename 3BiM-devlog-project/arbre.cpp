#include "arbre.h"
#include <random>
#include <stdlib.h> 
#include <cstring>
#include <iostream>

using namespace std;

///====================================================================
///
///Constructeurs
///
///====================================================================

///====================================================================
///Constructeur aléatoire
///Crée un arbre de de première génération avec 5 noeuds
///====================================================================

arbre::arbre(int nbrvar) {
	nbrvar_=nbrvar;
	cree_arbre_random();
}


///====================================================================
///Dummy constructeur pour les tests
///Constructeur d'arbre fille
///====================================================================

arbre::arbre(int nbrvar, int dummyfactor){
	liste_noeuds_=new noeud*[5];
	liste_noeuds_[0] = new noeud(1,2,3); //Noeud AND entre variable 2 et 3
	liste_noeuds_[1] = new noeud(1,1,5); //Noeud AND entre variable 1 et 5
	liste_noeuds_[2] = new noeud(2,1,liste_noeuds_[0]); //Noeud OR entre variable 1 et noeud 0
	liste_noeuds_[3] = new noeud(liste_noeuds_[1]); //Noeud NOT sur noeud 1
	liste_noeuds_[4] = new noeud(1,liste_noeuds_[2],liste_noeuds_[3]); //Noeud AND entre noeud 2 et 3
	nbr_noeuds_ = 5;
	noeud1_ = liste_noeuds_[4];
	nbrvar_=nbrvar;
}

///====================================================================
///Constructeur à  partir d'une arborescence de noeuds
///Constructeur d'arbre fille
///====================================================================

arbre::arbre(noeud* noeudf,int nbrvar) {
	noeud1_ = noeudf;
	nbrvar_ = nbrvar;
	compter_noeuds();
	lister_noeuds();
	mutation_random();

	delete[] liste_noeuds_;
	liste_noeuds_ = NULL;

	compter_noeuds();
	lister_noeuds();

}

///====================================================================
///Création d'un arbre aléatoire à  5 noeuds
///====================================================================

void arbre::cree_arbre_random() {
    //Création d'un arbre avec un opérateur puis 4 mutations ajout successives

    int operation = rand() %3+1;
    if(operation==3){
        int var = rand() %nbrvar_ ;
        noeud1_ = new noeud(var);
    } else {
        int var1 = rand() %nbrvar_ ;
        int var2 = rand() %nbrvar_ ;
        noeud1_ = new noeud(operation, var1, var2);
    }
    nbr_noeuds_ = 1;
    liste_noeuds_ = new noeud * [5]; //Une liste assez grande pour accueillir tous les noeuds
    liste_noeuds_[0] = noeud1_;

    //Ajouter les une ou deux variables en dessous de l'opérateur dans le tableau
    for (int i = 1; i < 5; ++i) {
        //Sélection d'un noeud random où faire l'ajout
        mutation_ajout(); //Dépend de comment marche les noeuds
        nbr_noeuds_++;
        
    }
    

}

///====================================================================
///Calcul du score (fitness) de l'arbre
///====================================================================

void arbre::calcul_fitness(const vector<vector<bool>> data) {
	int f=0;
	for(unsigned i=1; i<data.size(); i++){ //La première ligne de data est vide donc on commence à 1
		int diff = noeud1_->compute(data[i]) - data[i][data[i].size()-1]; //Conversion implicite de bool à  int
		f = f + diff*diff; //Il faut fournir la liste de donnéees à compute (liste qui correspond à une ligne du tableau)

	}
	fitness_=-f;
}

///====================================================================
///Renvoie de l'expression de l'arbre
///====================================================================

string arbre::expression() {
	return noeud1_->expr();
}

///====================================================================
///Méthode pour créer une fille
///====================================================================

arbre* arbre::creer_fille(){
	noeud* noeudf = new noeud(*noeud1_);
	arbre* arbrette = new arbre(noeudf,nbrvar_);
	
	return arbrette;
}

///====================================================================
///Création de l'attribut liste_noeuds_
///====================================================================

void arbre::lister_noeuds(){
	liste_noeuds_ = new noeud*[nbr_noeuds_+1]; //Place pour une mutation ajout éventuelle
	int i = 0;
	noeud1_->liste(liste_noeuds_,i);
}

///====================================================================
///Mise à  jour de l'attribut nombre_noeuds_
///====================================================================

void arbre::compter_noeuds() {
        nbr_noeuds_ = 1;
        int* ret = new int;
		*ret = 0;
        noeud1_->size(*ret);
        nbr_noeuds_ = *ret;

        delete ret;
        ret = NULL;

}

void arbre::lister_aretes(vector<string> &vecteur){
	noeud1_->inventaire_aretes(vecteur);
}

void arbre::infos_noeuds(vector<string> &vecteur){
	compter_noeuds();
	lister_noeuds(); //Pour être sûr d'être à jour
	for(int i=0;i<nbr_noeuds_;i++){
		vecteur.push_back(to_string(liste_noeuds_[i]->id_) + " " + to_string(liste_noeuds_[i]->op_));
	}
	
}

///====================================================================
///Choix et exécution d'une mutation
///====================================================================

void arbre::mutation_random() {

    random_device rd;  
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 3);
    
    if (dis(gen)==1) {
    	mutation_ajout();
  } else if (dis(gen)==2){
    	mutation_deletion();
    } else{
    	mutation_substitution();
    }

}

///====================================================================
///Mutation d'ajout d'un noeud
///====================================================================

void arbre::mutation_ajout() {
	noeud* raccord=nullptr;
	int raccordvar;
	bool israccordvar=false;
	int numnoeud = rand() % nbr_noeuds_;
	int monrand = rand() % 2;
	int nbrvar=liste_noeuds_[numnoeud]->nb_var();
	int nbrarete=liste_noeuds_[numnoeud]->nb_aretes();
	
	if(liste_noeuds_[numnoeud]->op()==3){ //Si le noeud sélectionné est un NOT
		if (nbrvar!=0){
			raccordvar=liste_noeuds_[numnoeud] -> var_[0];
			israccordvar=true;
		}else{
			raccord=liste_noeuds_[numnoeud] -> aretes_[0];
		}
	}else{ //Si le noeud sélectionné est un AND ou un OR
		if(nbrvar==2){
			raccordvar=liste_noeuds_[numnoeud] -> var_[monrand];
			israccordvar=true;
		} else if (nbrarete==2){
			raccord=liste_noeuds_[numnoeud] -> aretes_[monrand];
		} else {
			if (monrand==0){
				raccordvar=liste_noeuds_[numnoeud] -> var_[0];
				israccordvar=true;
			} else {
				raccord = liste_noeuds_[numnoeud] -> aretes_[0];
			}
		}
	}
	int monrand1 = rand() % 3 + 1;
	noeud* nvnoeud=nullptr;
	if (monrand1==3){ //Si le nouveau noeud est un NOT
		nvnoeud = (israccordvar ? new noeud(raccordvar) : new noeud(raccord));
	} else {
		int varcomp = rand() % nbrvar_;
		nvnoeud = (israccordvar ? new noeud(monrand1,raccordvar,varcomp) : new noeud(monrand1,varcomp,raccord));
	}
 	liste_noeuds_[nbr_noeuds_] = nvnoeud; //On suppose qu'il reste au moins une place dans le tableau liste_noeuds_ (cas normal)
 	
	if(israccordvar){
        liste_noeuds_[numnoeud]->nb_aretes_++;
		if (nbrvar != 1) {
			liste_noeuds_[numnoeud]->var_[0] = liste_noeuds_[numnoeud]->var_[1 - monrand]; //Replace la variable qui reste au début du tableau
		}
		liste_noeuds_[numnoeud]->nb_var_--;
        liste_noeuds_[numnoeud] -> aretes_[nbrarete]=nvnoeud;
    }else if(nbrarete==1){
 	    liste_noeuds_[numnoeud] ->aretes_[0]=nvnoeud;
 	}else {
        liste_noeuds_[numnoeud] ->aretes_[monrand]=nvnoeud;
 	}

}

///====================================================================
///Mutation délétion d'un noeud
///====================================================================

void arbre::mutation_deletion() {
	int numnoeud = rand() % nbr_noeuds_;
	if(liste_noeuds_[numnoeud]->nb_aretes() >= 1){
		if (liste_noeuds_[numnoeud]->nb_aretes_ == 1) {
			delete (liste_noeuds_[numnoeud]->aretes_[0]); //Supression du noeud retiré
			liste_noeuds_[numnoeud]->nb_var_++; //1 ou deux variables selon s'il s'agit d'un NOT ou non
			liste_noeuds_[numnoeud]->nb_aretes_ = 0; //Plus d'arête

		}else{
			int monrand = rand() % 2;
			delete (liste_noeuds_[numnoeud]->aretes_[monrand]); 
			liste_noeuds_[numnoeud]->aretes_[0] = liste_noeuds_[numnoeud]->aretes_[1 - monrand]; //On remet le noeud restant en place

			liste_noeuds_[numnoeud]->nb_var_ = 1; //1 nouvelle variable
			liste_noeuds_[numnoeud]->nb_aretes_ = 1; //Plus qu'une seule arete


		}
		int monrand = rand() % nbrvar_;
		liste_noeuds_[numnoeud]->var_[liste_noeuds_[numnoeud]->nb_var_-1]=monrand; 
	}
}

///====================================================================
///Mutation du type d'un noeud
///====================================================================

void arbre::mutation_substitution() {
	//Choix du noeud ï¿½ modifier
	int numnoeud = rand() % nbr_noeuds_;
	//Choix du nouveau type d'opérateur du noeud
	int monrand = rand() % 100;
	int newop;
	switch (liste_noeuds_[numnoeud]->op())
	{
	case 1:
		if (monrand > 49) {
			newop = 2;
		}
		else {
			newop = 3;
		}
	case 2:
		if (monrand > 49) {
			newop = 1;
		}
		else {
			newop = 3;
		}
	default:
		if (monrand > 49) {
			newop = 1;
		}
		else {
			newop = 2;
		}
		break;
	}
	noeud* noeudm = liste_noeuds_[numnoeud];
	if (noeudm->op_!=3 && newop != 3){ //Si le noeud n'était pas un NOT et ne devient pas un NOT
		noeudm -> op_ = newop;
	}else if (noeudm->op_==3){ //Si le noeud était un NOT
		noeudm->op_=newop;
		
		noeudm->var_[noeudm->nb_var_] = rand() % nbrvar_; //On ajoute une nouvelle variable
		noeudm ->nb_var_=noeudm ->nb_var_+1;

	}else{ //Si le noeud devient un NOT
		monrand = rand() % 2;
		noeudm->op_=newop;
		switch(noeudm->nb_aretes_)
		{
		case 0: //Le noeud était relié à deux variables
			{
			noeudm->var_[0] = noeudm->var_[monrand]; //On remet la variable conservée en place
			noeudm -> nb_var_=1;
			}
			break;
		case 1: //Le noeud était relié à une variable et un noeud
			if (monrand==0){
				noeudm -> nb_var_=0;
			} else {
				delete  noeudm ->aretes_[0];
				noeudm -> nb_aretes_=0;
			}
			break;
		default: //Le noeud était relié à deux noeuds
			{
			noeudm->aretes_[0] = noeudm->aretes_[monrand]; // On remet le noeud conservé en place
			delete noeudm -> aretes_[1-monrand];
			noeudm -> nb_aretes_=1;
			}
			break;
		}
	}
	
}

///====================================================================
///Destructeur
///====================================================================

arbre::~arbre(){

	delete noeud1_;
	delete[] liste_noeuds_;
}
