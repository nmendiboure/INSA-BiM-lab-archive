/// \class arbre
///
/// Un objet de la classe arbre contient une formule de booléens qui peut être mutée selon trois mutations (délétion, insertion ou modification)
///
/// Chaque arbre est obtenu à partir d'un parent dont l'on obtient une copie à laquelle on applique une mutation
/// La fitness de l'arbre obtenue peut être calculée en lui fournissant un tableau contenant des observations et leurs résultats

#include "noeud.h"
#include <vector>
#include <string>
using namespace std;
#if ! defined(ARBRE_H)
#define ARBRE_H



class arbre{

public :
    /**
     * constructeur aléatoire pour générer un arbre de première génération avec 5 noeuds
     * @param nbrvar le nombre de variables observées
     */
	arbre(int nbrvar);
	/**
	 * constructeur de copie non utilisé
	 * @param arbre_copie
	 */
	arbre(const arbre& arbre_copie); //Constructeur à partir d'un arbre
	/**
	 * constructeur d'un arbre à partir d'un autre sans random utilisé dans les tests
	 * @param nbrvar le nombre de variables observées
	 * @param dummyfacor variable inutile pour différencier les constructeurs
	 */
	arbre(int nbrvar,int dummyfacor); //Dummy constructor
	/**
	 * constructeur d'arbre fille
	 * @param noeudf premier noeud de l'arborescence donnée au nouvel arbre
	 * @param nbrvar le nombre de variables observées
	 */
	arbre(noeud* noeudf, int nbrvar); // Constructeur de l'arbre fille
	/**
	 * Destructeur de la classe
	 * Détruit tous les noeuds de l'arbre
	 */
	~arbre(); //destructeur
	/**
	 * Calcul de la fitness de l'arbre
	 * @param data Vecteur de vecteurs de bool contenant les observations (une par ligne) et le résultat (dernière colonne)
	 */
	void calcul_fitness(const vector<vector<bool>> data);
	/**
	 * Fonction qui crée une fille, fait une copie des noeuds de l'arbre et les fournit au constructeur de l'arbre fille
	 *
	 * @return le nouvel arbre créé
	 */
	arbre* creer_fille();
	/**
	 * Définit après le 1er appel de calcul fitness
	 * Plus elle est grande (proche de 0), meilleure est la formule de l'arbre
	 */
	int fitness_=-1000;

	/**
	* Renvoie l'expression de l'arbre dans une String
	*/
	string expression();

	/**
	* Ajoute les aretes de l'arbre dans le vecteur fournit
	* @param vecteur vecteur de string, une arete par string ex : "1 4"
	*/
	void lister_aretes(vector<string> &vecteur);
	
	/**
	* Ajoute des informations (id et op_)sur les noeuds de l'arbre dans le vecteur fournit
	* @param vecteur vecteur de string, un noeud par string ex : "90 1"
	*/
	void infos_noeuds(vector<string> &vecteur);

private :

	noeud* noeud1_; /*!< 1er noeud de l'arbre
                    */
	noeud** liste_noeuds_ ; // une liste des pointeurs des noeuds de l'arbre sans ordre précis
	int nbr_noeuds_; //Nombre de noeuds dans l'arbre
	/**
	 * Génère un nouveau noeud inséré dans un endroit aléatoire de l'abre
	 */
	void mutation_ajout();
	/**
	 * Supprime un noeud aléatoirement et les branches qui en dépendent
	 */
	void mutation_deletion();
	/**
	 * Change le type d'un noeud et ajuste si besoin les variables et aretes du dit noeud
	 */
	void mutation_substitution();
	/**
	 * Choisit aléatoirement un des trois types de mutations et l'applique
	 */
	void mutation_random();
	/**
	 * Compte le nombre de noeuds dans l'arbre, met à jour nbr_noeuds_
	 */
	void compter_noeuds();
	/**
	 * Liste les noeuds de l'arbre et met à jour liste_noeuds_
	 */
	void lister_noeuds();
	/**
	 * Crée un arbre alétoire avec 5 noeuds
	 */
	void cree_arbre_random();
	int nbrvar_;

};
#endif
