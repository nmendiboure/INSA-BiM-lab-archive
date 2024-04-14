#include "./noeud.h"
#include <iostream>

//============================================================================
//
//Constructeurs
//
//============================================================================

//============================================================================
//Constructeur par défaut
//============================================================================

//============================================================================
//Constructeur avec deux variables
//============================================================================

noeud::noeud(int op_par, int var1, int var2){
	op_ = op_par;	
	aretes_ = new noeud * [2];
	var_ = new int[2];
    var_[0] = var1;
	var_[1] = var2;
	nb_aretes_ = 0;
	nb_var_ = 2;
	nb_const_ = 0;
	id_ = identifiant;
	identifiant++;
}

//============================================================================
//Constructeur avec deux noeuds
//============================================================================

noeud::noeud(int op_par, noeud* noeud1, noeud* noeud2){
	op_ = op_par;	
	aretes_ = new noeud*[2];
	var_ = new int[2];
	aretes_[0] = noeud1;
	aretes_[1] = noeud2;
	nb_aretes_ = 2;
	nb_var_ = 0;
	nb_const_ = 0;
	id_ = identifiant;
	identifiant++;
}

//============================================================================
//Constructeur avec une variable et un noeud
//============================================================================

noeud::noeud(int op_par, int var1, noeud* noeud1){
	op_ = op_par;	
	aretes_ = new noeud*[2];
	var_ = new int[2];
	aretes_[0] = noeud1;
	var_[0] = var1;
	nb_aretes_ = 1;
	nb_var_ = 1;
	nb_const_ = 0;
	id_ = identifiant;
	identifiant++;
}

//============================================================================
//Constructeur avec deux constantes
//============================================================================

noeud::noeud(int op_par, bool const1, bool const2){
	op_ = op_par;	
	consts_ = new bool[2];
	aretes_ = new noeud * [2];
	var_ = new int[2];
	consts_[0] = const1;
	consts_[1] = const2;
	nb_aretes_ = 0;
	nb_var_ = 0;
	nb_const_ = 2;
	id_ = identifiant;
	identifiant++;
}

//============================================================================
//Constructeur avec une constante et un noeud
//============================================================================

noeud::noeud(int op_par, bool const1, noeud* noeud1){
	op_ = op_par;	
	aretes_ = new noeud * [2];
	var_ = new int[2];
	consts_ = new bool[1];
	aretes_[0] = noeud1;
	consts_[0] = const1;
	nb_aretes_ = 1;
	nb_var_ = 0;
	nb_const_ = 1;
	id_ = identifiant;
	identifiant++;
}

//============================================================================
//Constructeur avec une constante et une variable
//============================================================================

noeud::noeud(int op_par, bool const1, int var1){
	op_ = op_par;	
	aretes_ = new noeud * [2];
	var_ = new int[2];
	consts_ = new bool[1];
	var_[0] = var1;
	consts_[0] = const1;
	nb_aretes_ = 0;
	nb_var_ = 1;
	nb_const_ = 1;
	id_ = identifiant;
	identifiant++;
}

//============================================================================
//Constructeur pour not avec une variable
//============================================================================

noeud::noeud(int var1){
	op_ = 3;	
	aretes_ = new noeud * [2];
	var_ = new int[2];
	var_[0] = var1;
	nb_aretes_ = 0;
	nb_var_ = 1;
	nb_const_ = 0;
	id_ = identifiant;
	identifiant++;
}

//============================================================================
//Constructeur pour not avec un noeud
//============================================================================

noeud::noeud(noeud* noeud1){
	op_ = 3;	
	aretes_ = new noeud * [2];
	var_ = new int[2];
	aretes_[0] = noeud1;
	nb_aretes_ = 1;
	nb_var_ = 0;
	nb_const_ = 0;
	id_ = identifiant;
	identifiant++;
}

//============================================================================
//Constructeur de copie
//============================================================================

noeud::noeud(const noeud &acopier){
	op_ = acopier.op();
	nb_aretes_ = acopier.nb_aretes();
	nb_var_ = acopier.nb_var();
	nb_const_ = acopier.nb_const();
	aretes_ = new noeud * [2];
	var_ = new int[2];

	if (nb_aretes_!=0){
		
		for (int i=0;i<nb_aretes_;i++){
			aretes_[i]= new noeud(*(acopier.aretes()[i])); 
		}
	}

	if (nb_var_!=0){
		
		for (int i=0;i<nb_var_;i++){
			var_[i]=acopier.var()[i]; 
		}
	}

	if (nb_const_!=0){
		consts_=new bool[nb_const_];
		for (int i=0;i<nb_const_;i++){
			consts_[i]=acopier.consts()[i]; 
		}
	}
	id_ = identifiant;
	identifiant++;
}

//============================================================================
//
//Destructeur
//
//============================================================================

noeud::~noeud(){
	if (nb_aretes_ == 2){
		if (aretes_[0] == aretes_[1]){
			delete aretes_[0];
		} else {
			delete aretes_[0];
			delete aretes_[1];
		}
	} else if (nb_aretes_ == 1){
		delete aretes_[0];
	}
	delete[] var_;
	delete[] consts_;
	delete[] aretes_;
}

//============================================================================
//
//Getters
//
//============================================================================

int noeud::op() const{
	return op_;
}

int noeud::nb_aretes() const{
	return nb_aretes_;
}

int noeud::nb_var() const{
	return nb_var_;
}

int noeud::nb_const() const{
	return nb_const_;
}

int* noeud::var() const{
	return var_;
}

bool* noeud::consts() const{
	return consts_;
}

noeud** noeud::aretes() const{
	return aretes_;
}

//============================================================================
//
//Compute
//
//============================================================================

bool noeud::compute(const vector<bool> list){

	//========================================================================
	//Cas pour AND and OR 
	//========================================================================
	
	//Deux noeuds
	if (nb_aretes_ == 2){ 
		switch (op_){
			case 1: return aretes_[0]->compute(list) 
					&& aretes_[1]->compute(list);
			case 2: return aretes_[0]->compute(list) 
					|| aretes_[1]->compute(list);
		}
	} 
	//Un noeud et une variable
	else if (nb_aretes_ == 1 && nb_var_ == 1){
		switch (op_){
			case 1: return aretes_[0]->compute(list)
					&& list[var_[0]];
			case 2: return aretes_[0]->compute(list)
					|| list[var_[0]];
		}
	} 
	//Un noeud et une constante
	else if (nb_aretes_ == 1 && nb_const_ == 1){
		switch (op_){
			case 1: return aretes_[0]->compute(list)
					&& consts_[0];
			case 2: return aretes_[0]->compute(list)
					|| consts_[0];
		}
	} 
    //Deux variables
	else if (nb_var_ == 2){
		switch (op_){
			case 1: return list[var_[0]]
					&& list[var_[1]];
			case 2: return list[var_[0]]
					|| list[var_[1]];
		}
	} 
	//Une variable et une constante
	else if (nb_var_ == 1 && nb_const_ == 1){
		switch (op_){
			case 1: return list[var_[0]]
					&& consts_[0];
			case 2: return list[var_[0]]
					|| consts_[0];
		}
	} 
	//Deux constantes
	else if (nb_const_ == 2){
		switch (op_){
			case 1: return consts_[0]
					&& consts_[1];
			case 2: return consts_[0]
					|| consts_[1];
		}
	}

	//========================================================================
	//Cas pour NOT
	//======================================================================== 
	
	//Un noeud
	else if (op_ == 3 && nb_aretes_ == 1){
		return !(aretes_[0]->compute(list));
	}

	//Une variable
	else if (op_ == 3 && nb_var_ == 1){
		return !(list[var_[0]]);
	}

	else {
		std::cout << "Erreur calcul" << std::endl;
		return 0;
	}

	//return 0; //return par défaut pour éviter les erreurs de compilation,
			  //à modifier
}

//============================================================================
//
//Size
//
//============================================================================

void noeud::size(int &ret){
	ret++;
	if (nb_aretes_ > 0){
		for (int i=0; i<nb_aretes_; i++){
			aretes_[i]->size(ret);
		}
	}
}

//============================================================================
//
//Liste
//
//============================================================================

void noeud::liste(noeud** array, int& i){
	array[i] = this;
	i++;
	for (int j = 0; j<nb_aretes_; j++){
		aretes_[j]->liste(array, i);
	}
}

void noeud ::inventaire_aretes(vector<string> &vecteur){
	for (int i=0; i<nb_aretes_;i++){
		vecteur.push_back( toString(id_) +" "+ toString(aretes_[i]->id_));
		aretes_[i]->inventaire_aretes(vecteur);
	}
	for (int i=0; i<nb_var_;i++){
		vecteur.push_back( toString(id_) +" x"+ toString(var_[i]));
	}
}


string noeud::expr(){

	//========================================================================
	//Cas pour AND and OR 
	//========================================================================
	
	//Deux noeuds
	if (nb_aretes_ == 2){ 
		switch (op_){
			case 1: return "( " + aretes_[0]->expr() + " & " 
					+ aretes_[1]->expr() + " )";
			case 2: return "( " + aretes_[0]->expr() + " | " 
					+ aretes_[1]->expr() + " )";
		}
	} 
	//Un noeud et une variable
	else if (nb_aretes_ == 1 && nb_var_ == 1){
		switch (op_){
			case 1: return "( " + aretes_[0]->expr() + " & x" 
					+ toString(var_[0]) + " )";
			case 2: return "( " + aretes_[0]->expr() + " | x" 
					+ toString(var_[0]) + " )";
		}
	} 
	//Un noeud et une constante
	else if (nb_aretes_ == 1 && nb_const_ == 1){
		switch (op_){
			case 1: return "( " + aretes_[0]->expr() + " & x" 
					+ toString(consts_[0]) +" )";
			case 2: return "( " + aretes_[0]->expr() + " | x" 
					+ toString(consts_[0]) + " )";
		}
	} 
    //Deux variables
	else if (nb_var_ == 2){
		switch (op_){
			case 1: return "( x" + toString(var_[0]) + " & x" 
					+ toString(var_[1]) + " )";
			case 2: return "( x" + toString(var_[0]) + " | x"
					+ toString(var_[1]) + " )";
		}
	} 
	//Une variable et une constante
	else if (nb_var_ == 1 && nb_const_ == 1){
		switch (op_){
			case 1: return "( " + toString(consts_[0]) + " & x"
					+ toString(var_[0]) + " )";
			case 2: return "( " + toString(consts_[0]) + " | x"
					+ toString(var_[0]) + " )";
		}
	} 
	//Deux constantes
	else if (nb_const_ == 2){
		switch (op_){
			case 1: return "( " + toString(consts_[0]) + " & "
					+ toString(consts_[1]) + " )";
			case 2: return "( " + toString(consts_[0]) + " | "
					+ toString(consts_[1]) + " )";
		}
	}

	//========================================================================
	//Cas pour NOT
	//======================================================================== 
	
	//Un noeud
	else if (op_ == 3 && nb_aretes_ == 1){
		return "~" + aretes_[0]->expr();
	}

	//Une variable
	else if (op_ == 3 && nb_var_ == 1){
		return "~x"+ toString(var_[0]);
	}

	else {
		return "Erreur";
	}

}

//============================================================================
//
//Fonction annexe
//
//============================================================================

string toString(int i){
	if (i<10){
		return "00" + to_string(i);
	} else if (i < 100){
		return "0" + to_string(i);
	} else {
		return to_string(i);
	}
}
