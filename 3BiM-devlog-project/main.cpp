#include <string>

#include <sstream>

#include <iostream>

#include <vector>

#include <fstream>

#include "arbre.h"

using namespace std;
unsigned long noeud::identifiant=0;
/**

 * Fonction qui sert a supprimer le premier element d'un vecteur

 * Pour pouvoir enlever le nom de la ligne

 * 

 */

template<typename T>

void pop_front(vector<T> &v){

    if (v.size() > 0) {

        v.erase(v.begin());

    }

}


vector<vector<string>> CreerTableau(string data){

    //Upload du fichier

    ifstream in(data);

    string line, field;

    //On va stocker les donnees dans des vecteurs

    vector<vector<string>> tab;  //un vecteur de vecteurs pour le tableau

    vector<string> ligne;          //un vecteur pour la ligne

    //On lit la ligne du fichier tant qu'il reste des lignes

    while (getline(in,line)){

        //Nettoyage du buffer (ligne)

        ligne.clear();

        //On cree un stream de la ligne pour pouvoir lire la ligne

        stringstream ss(line);

        //On lit la ligne

         while (getline(ss,field,',')) {
            //on ajoute le contenu de la ligne au vecteur

            ligne.push_back(field); 

        }

        //on supprime la colonne de nom du CSV

        pop_front(ligne);
        //On ajoute toute la ligne au tableau 2D

         tab.push_back(ligne); 
    }
    return tab;

}



vector<vector<bool>> ConversionTableau(vector<vector<string>> tab){

    vector<vector<bool>> tab2;

    for (size_t i=0; i<tab.size(); ++i) {

        vector<bool> tab_ligne;

        for (size_t j=0; j<tab[i].size(); ++j){

            if (tab.at(i).at(j)=="0") {

                tab_ligne.push_back(0); // tab.at(i).at(j) = tab[i][j]

            }

            else if (tab.at(i).at(j)=="1") tab_ligne.push_back(1);

        }

        tab2.push_back(tab_ligne);


    }

    return tab2; 

}


void AffichageString(vector<vector<string>> tab){

    //Affichage du tableau de booléens 

    for (size_t i=0; i<tab.size(); ++i) {

        for (size_t j=0; j<tab[i].size(); ++j) {

            cout << tab.at(i).at(j) << "|"; 

        }

        cout << "\n";
    }

}

void Affichage(vector<vector<bool>> tab){

    //Affichage du tableau de booléens 
    for (size_t i=1; i<tab.size(); ++i){

        for (size_t j=0; j<tab[i].size(); ++j){

            cout << tab.at(i).at(j) << "|"; 

        }

        cout << "\n";
    }

}

void stockage_formule(arbre* arbre, string nomfichier){
	ofstream f(nomfichier);
	if (f){
		f << arbre->expression() << "\n";
	}else {
		std:: cout << "Impossible d'ouvrir le fichier en écriture" 
			<< std::endl;
	}
	f.close();
}

void stockage_fit(int* histo, int nb_gen){
	ofstream f("fitness");
	if (f){
		for (int i = 0; i < nb_gen - 1; i++){
			f << histo[i] << "\n";
		}
	}else {
		std:: cout << "Impossible d'ouvrir le fichier en écriture" 
			<< std::endl;
	}
	f.close();
}

void stockage_aretes(arbre* candidat){
	ofstream f("aretes");
	if (f){
		vector<string> list_aretes;
		candidat->lister_aretes(list_aretes);
		for (unsigned int i = 0; i < list_aretes.size(); i++){
			f << list_aretes[i] << "\n";
		}
	}else {
		std:: cout << "Impossible d'ouvrir le fichier en écriture" 
			<< std::endl;
	}
	f.close();
}

void stockage_infos_noeuds(arbre* candidat){
	ofstream f("infos_noeuds");
	if (f){
		vector<string> infos_noeuds;
		candidat->infos_noeuds(infos_noeuds);
		for (unsigned int i = 0; i < infos_noeuds.size(); i++){
			f << infos_noeuds[i] << "\n";
		}
	}else {
		std:: cout << "Impossible d'ouvrir le fichier en écriture" 
			<< std::endl;
	}
	f.close();
}

int main(int argc, char* argv[]) {
    

    int nb_generationsmax = atoi(argv[1]);
    int seuil_fitness = atoi(argv[2]);
    int nbr_filles = atoi(argv[3]);
	string nomfichier=argv[4];
	string datafile = argv[5];
    //int nb_generationsmax = 1000;
    //int seuil_fitness = -50;
    //int nbr_filles = 20;
    cout << nb_generationsmax << endl;
    cout << nbr_filles << endl;
    cout << seuil_fitness << endl;
    int nbgeneration = 1;

    vector<vector<string>> tab;

    vector<vector<bool>> tab2;

    tab =CreerTableau(datafile);

    //AffichageString(tab);

    tab2= ConversionTableau(tab);
    
    arbre** arbres_acomparer = new arbre*[nbr_filles];
    arbre* candidat;
    int indexCandidat=0;
    int* historiquefit = new int[nb_generationsmax];
	int nbvar = tab2[3].size()-1;
    bool fille_meilleure=false;
    
    for(int i=0; i<5;i++){
    	arbres_acomparer[i] = new arbre(nbvar);
    	arbres_acomparer[i]->calcul_fitness(tab2);
    	if (arbres_acomparer[indexCandidat]->fitness_ < arbres_acomparer[i]->fitness_){
    	    indexCandidat=i;
    	}
    }
    for(int i=0;i<5;i++){
        if (i != indexCandidat) {
            delete arbres_acomparer[i];
        }
    }
    cout << indexCandidat << endl;

    candidat = arbres_acomparer[indexCandidat];
    historiquefit[nbgeneration-1]=candidat->fitness_;
    nbgeneration++;
    
    while (nb_generationsmax > nbgeneration&& seuil_fitness > candidat->fitness_) {
        indexCandidat = 0;
        for (int i = 0; i < nbr_filles; i++) {
            arbres_acomparer[i] = candidat->creer_fille();
            arbres_acomparer[i]->calcul_fitness(tab2);
            if (candidat->fitness_ < arbres_acomparer[i]->fitness_ && arbres_acomparer[indexCandidat]->fitness_ <= arbres_acomparer[i]->fitness_) {
                indexCandidat = i;
                fille_meilleure = true;
            }
        }
        
        if (fille_meilleure) {
            delete candidat;
            candidat = arbres_acomparer[indexCandidat];
        }
        historiquefit[nbgeneration-1]=candidat->fitness_;

        for (int i = 0; i < nbr_filles; i++) {
            if (i != indexCandidat || ! fille_meilleure) {
                delete arbres_acomparer[i];
            }
        }
        nbgeneration++;
    }
    cout << candidat->fitness_ << endl;
    cout << nbgeneration << endl;
    //cout << candidat->expression() << endl;
    
    vector<string> aretes;
    candidat->lister_aretes(aretes);
    
    vector<string> noeuds;
    candidat->infos_noeuds(noeuds);
    
    /*for (size_t i=1; i<noeuds.size(); ++i){
    	cout << noeuds.at(i) <<endl;
    }*/
	
	stockage_formule(candidat, nomfichier);
	stockage_fit(historiquefit, nb_generationsmax);
	stockage_aretes(candidat);
	stockage_infos_noeuds(candidat);

    return 0;
}
