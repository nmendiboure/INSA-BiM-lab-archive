/// \class noeud
///
/// La classe noeud consiste en un unique noeud de l'arbre
///
/// La classe noeud peut soit être reliée à d'autres noeuds,
/// soit contenir des variables ou des constantes. 
/// En raison de cette structure, toute la structure de l'arbre est accessible
/// depuis le premier noeud de ce dernier.

#include <vector>
#include <string>
class arbre;
using namespace std;
#if ! defined(NOEUD_H)
#define NOEUD_H

string toString(int);

class noeud
{

	friend class arbre;

	private: 

		int op_ = 0; /*!< Opération réalisée par le noeud:
					   * 1 pour AND
					   * 2 pour OR
					   * 3 pour NOT */
		int nb_aretes_ = 0; /*!< Nombre d'autre noeuds auquel le noeud est relié
							  */
		int nb_var_ = 0; /*!< Nombre de variables que contient le noeud */
		int nb_const_ = 0; /*!< Nombre de constantes que contient le noeud */
		int* var_ = nullptr; /*!< tableau des variables contenus par le noeud */
		bool* consts_ = nullptr; /*!< tableau des constantes contenues par le 
								   * noeud */
		noeud** aretes_ = nullptr; /*!< tableau de pointeurs vers les noeuds
									 * auxquels le noeud est relié */
		unsigned long id_;
	
	public: 
		static unsigned long identifiant;
		//====================================================================
		//Constructeurs
		//====================================================================

		
		///
		/// Constructeur par défaut: inutilisé
		///
		
		noeud(); 

		//ctor pour AND et OR 

		//ctor avec deux variables
		
		/// Constructeurs de la classe noeud avec deux variables,
		/// pour les opération AND et OR
		///
		/// \param op_par l'opération réalisée par le noeud:
		/// 1 pour AND, 2 pour OR
		/// \param var1 un entier indiquant la position de la variable dans
		/// une liste de booléens
		/// \param var2 id.
		
		noeud(int op_par, int var1, int var2);

		//ctor avec deux noeuds

		/**
		 * Constructeur de la classe noeud avec deux noeuds,
		 * pour les opération AND et OR
		 *
		 * @param op_par l'opération réalisée par le noeud:
		 * 1 pour AND, 2 pour OR
		 * @param noeud1 un pointeur vers un noeud
		 * @param noeud2 id.
		 */

		noeud(int op_par, noeud* noeud1, noeud* noeud2);

		//ctor avec une variable et un noeud

		/**
		 * Constructeur de la classe noeud avec une variable et un noeud,
		 * pour les opération AND et OR
		 *
		 * @param op_par l'opération réalisée par le noeud:
		 * 1 pour AND, 2 pour OR
		 * @param var1 un entier indiquant la position de la variable dans
		 * une liste de booléens
		 * @param noeud1 un pointeur vers un noeud
		 */

		noeud(int op_par, int var1, noeud* noeud1);

		//ctor avec deux constantes

		/**
		 * Constructeur de la classe noeud avec deux constantes,
		 * pour les opération AND et OR
		 *
		 * @param op_par l'opération réalisée par le noeud:
		 * 1 pour AND, 2 pour OR
		 * @param const1 une constante booléenne
		 * @param const2 id.
		 */

		noeud(int op_par, bool const1, bool const2);

		//ctor avec une constante et un noeud

		/**
		 * Constructeur de la classe noeud avec une constante et un noeud
		 * pour les opération AND et OR
		 *
		 * @param op_par l'opération réalisée par le noeud:
		 * 1 pour AND, 2 pour OR
		 * @param const1 une constante booléenne
		 * @param noeud1 un pointeur vers un noeud
		 */

		noeud(int op_par, bool const1, noeud* noeud1);

		//ctor avec une constante et une variable

		/**
		 * Constructeur de la classe noeud avec une constante et une variable,
		 * pour les opération AND et OR
		 *
		 * @param op_par l'opération réalisée par le noeud:
		 * 1 pour AND, 2 pour OR
		 * @param const1 une constante booléenne
		 * @param var1 un entier indiquant la position de la variable dans une
		 * liste de booléens
		 */

		noeud(int op_par, bool const1, int var1);

		//Constructeurs pour NOT
		
		//ctor pour not avec une variable
		
		/**
		 * Constructeur de la classe noeud avec une variable
		 * pour l'opération NOT
		 *
		 * @param var1 un entier indiquant la position de la variable dans une
		 * liste de booléens
		 */

		noeud(int var1);

		//ctor pour not avec un noeud

		/**
		 * Constructeur de la classe noeud avec un noeud
		 * pour l'opération NOT
		 *
		 * @param noeud1 un pointeur vers un noeud
		 */

		noeud(noeud* noeud1);
		
		//Constructeur de copie

		/**
		 * Constructeur de copie, réalise une copie profonde
		 *
		 * @param acopier un noeud passé par référence constante
		 */
		
		noeud(const noeud&);

		//====================================================================
		//Destructeur
		//====================================================================
		
		/**
		 * Destructeur de la classe noeud
		 *
		 *
		 * Ce destructeur est récursif: il détruit le noeud sur lequel il est
		 * appelé, ainsi que tous les noeuds en dessous de celui-ci.
		 * Attention: ce destructeur entre en conflit avec le destructeur 
		 * automatique du C++ si les noeuds ne se trouvent pas dans le heap
		 */
		
		~noeud(); 

		//====================================================================
		//Getters
		//====================================================================

		int op() const; /*!< Renvoie l'opération réalisée par le noeud:
							 * 1 pour AND,
							 * 2 pour OR,
							 * 3 pour NOT */

		int nb_aretes() const; /*!< Renvoie le nombre de noeuds auquel le noeud
								 est relié */

		int nb_var() const; /*!< Renvoie le nombre de variables que contient le
							  noeud */

		int nb_const() const; /*!< Renvoie le nombre de constantes que contient
								le noeud */

		int* var() const; /*!< Renvoie un pointeur vers le tableau des
							   * variables du noeud
							   * 
							   * Renvoie un pointeur nul si le tableau n'existe
							   * pas */

		bool* consts() const; /*!< Renvoie un pointeur vers le tableau des
							   * constantes du noeud
							   * 
							   * Renvoie un pointeur nul si le tableau n'existe
							   * pas */

		noeud** aretes() const; /*!< Renvoie un pointeur vers le tableau des
							   * noeuds
							   * 
							   * Renvoie un pointeur nul si le tableau n'existe
							   * pas */


		//====================================================================
		//Compute
		//====================================================================

		//Calcule la valeur du noeud à partir d'une liste de valeurs

		/**
		 * Calcule le résultat de l'opération réalisé par le noeud
		 * 
		 * Recursif: prend en compte le résultats des noeuds situés en dessous
		 *
		 * @param list une liste de booléens correspondant aux valeurs
		 * prises par les variables contenues dans les noeuds
		 */

		bool compute(const vector<bool> list);

		//====================================================================
		//Size
		//====================================================================

		//donne le nombre de noeuds dans le tableau

		/**
		 * Permet de connaître le nombre de noeud situé en dessous du noeud sur 
		 * lequel cette méthode est appelée
		 *
		 * @param ret un entier nul incrémenté par la méthode : 
		 * sa valeur finale correspond au nombre de noeuds en dessous
		 */

		void size(int &ret);

		//====================================================================
		//Liste
		//====================================================================

		//Renvoie une liste de pointeurs vers les noeuds

		/**
		 * Permet d'obtenir une liste de pointeurs vers les noeuds situés en
		 * dessous du noeud sur lequel cette méthode est appelée
		 *
		 * @param array une liste de taille suffisante (à determiner avec size)
		 * qui contiendra à la fin les pointeurs vers les noeuds
		 * @param i un entier qui permet à la fonction de connaître l'index
		 * de la liste à modifier, ne pas changer la valeur par défaut
		 */

		void liste(noeud** array,int&); //attend en paramètre une liste 
						 //de la bonne taille
		/**
		 * Ajoute dans le vecteur fournit les aretes du noeud sous forme de String
		 *
		 * @param vecteur un vecteur de string qui contient dans chaque string une
		 * arete entre deux noeuds identifiés par leur identifiant
		 * exemple : "1 4"
		*/
										  
		void inventaire_aretes(vector<string> &vecteur);
		string expr();

};



#endif
