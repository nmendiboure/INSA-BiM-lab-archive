#include "gtest/gtest.h"
#include "arbre.h"
#include <vector>
#include <iostream>

TEST(GTestTests, ExampleTest){

	std::vector<bool> list(2);
	list[0] = 1;
	list[1] = 0;

	bool F = 0;
	bool T = 1;

	noeud** liste_noeud = new noeud*[5];

	liste_noeud[0] = new noeud(1);
	liste_noeud[1] = new noeud(1, F, T);
	liste_noeud[2] = new noeud(1, true, 0);
	liste_noeud[3] = new noeud(2, liste_noeud[0], liste_noeud[1]);
	liste_noeud[4] = new noeud(1, liste_noeud[2], liste_noeud[3]);

	EXPECT_EQ(liste_noeud[4]->compute(list), 1);

	delete liste_noeud[4];
	delete[] liste_noeud;
};

TEST(GTestTests, TestComputeConst){

	std::vector<bool> list(1);
	
	noeud noeud1(1, true, true);
	noeud noeud2(1, true, false);
	noeud noeud3(1, false, true);
	noeud noeud4(1, false, false);

	EXPECT_EQ(noeud1.compute(list), 1);
	EXPECT_EQ(noeud2.compute(list), 0);
	EXPECT_EQ(noeud3.compute(list), 0);
	EXPECT_EQ(noeud4.compute(list), 0);

	noeud noeud5(2, true, true);
	noeud noeud6(2, true, false);
	noeud noeud7(2, false, true);
	noeud noeud8(2, false, false);

	EXPECT_EQ(noeud5.compute(list), 1);
	EXPECT_EQ(noeud6.compute(list), 1);
	EXPECT_EQ(noeud7.compute(list), 1);
	EXPECT_EQ(noeud8.compute(list), 0);
};

TEST(GTestTests, TestComputeVar){

	std::vector<bool> list(2);
	list[0] = true;
	list[1] = false;
	
	noeud noeud1(1, 0, 0);
	noeud noeud2(1, 0, 1);
	noeud noeud3(1, 1, 0);
	noeud noeud4(1, 1, 1);

	EXPECT_EQ(noeud1.compute(list), true);
	EXPECT_EQ(noeud2.compute(list), false);
	EXPECT_EQ(noeud3.compute(list), false);
	EXPECT_EQ(noeud4.compute(list), false);

	noeud noeud5(2, 0, 0);
	noeud noeud6(2, 0, 1);
	noeud noeud7(2, 1, 0);
	noeud noeud8(2, 1, 1);

	EXPECT_EQ(noeud5.compute(list), true);
	EXPECT_EQ(noeud6.compute(list), true);
	EXPECT_EQ(noeud7.compute(list), true);
	EXPECT_EQ(noeud8.compute(list), false);

	noeud noeud9(0);
	noeud noeud10(1);

	EXPECT_EQ(noeud9.compute(list), false);
	EXPECT_EQ(noeud10.compute(list), true);
};

TEST(GTestTests, TestSize){

	bool F = 0;
	bool T = 1;

	noeud** liste_noeud = new noeud*[5];

	liste_noeud[0] = new noeud(1);
	liste_noeud[1] = new noeud(1, F, T);
	liste_noeud[2] = new noeud(1, true, 0);
	liste_noeud[3] = new noeud(2, liste_noeud[0], liste_noeud[1]);
	liste_noeud[4] = new noeud(1, liste_noeud[2], liste_noeud[3]);

	int s=0;
	liste_noeud[4]->size(s);

	EXPECT_EQ(s, 5);

	delete liste_noeud[4];
	delete[] liste_noeud;
};

TEST(GTestTests, TestListe){

	bool F = 0;
	bool T = 1;
	
	noeud** liste_noeud = new noeud*[5];

	liste_noeud[0] = new noeud(1);
	liste_noeud[1] = new noeud(1, F, T);
	liste_noeud[2] = new noeud(1, true, 0);
	liste_noeud[3] = new noeud(2, liste_noeud[0], liste_noeud[1]);
	liste_noeud[4] = new noeud(1, liste_noeud[2], liste_noeud[3]);

	int s=0;
	liste_noeud[4]->size(s);
	noeud* arr2[s];

	int count = 0;
	
	liste_noeud[4]->liste(arr2, count);			
	
	EXPECT_EQ(arr2[0],liste_noeud[4]);
	EXPECT_EQ(arr2[1],liste_noeud[2]);
	EXPECT_EQ(arr2[2],liste_noeud[3]);
	EXPECT_EQ(arr2[3],liste_noeud[0]);
	EXPECT_EQ(arr2[4],liste_noeud[1]);
	
	delete liste_noeud[4];
	delete[] liste_noeud;
};



TEST(GTestTests, TestCopie){

	std::vector<bool> list(2);
	list[0] = 1;
	list[1] = 0;

	bool F = 0;
	bool T = 1;

	noeud** liste_noeud = new noeud*[5];

	liste_noeud[0] = new noeud(1);
	liste_noeud[1] = new noeud(1, F, T);
	liste_noeud[2] = new noeud(1, true, 0);
	liste_noeud[3] = new noeud(2, liste_noeud[0], liste_noeud[1]);
	liste_noeud[4] = new noeud(1, liste_noeud[2], liste_noeud[3]);

	noeud* copie = new noeud(*liste_noeud[4]);
	//std::cout << copie->compute(list) << std::endl;
	EXPECT_EQ(copie->compute(list), 1);
	//std::cout << copie->aretes()[0] << std::endl;
	//std::cout << liste_noeud[4]->aretes()[0] << std::endl; //Pas les mêmes adresses
	EXPECT_FALSE(copie->aretes()[0] == liste_noeud[4]->aretes()[0]);

	delete liste_noeud[4];
	delete[] liste_noeud;
	delete copie;
};


TEST(GTestTests, TestFitness){
	std::vector<bool> l1{0,0,0,0,1,0,0};

	std::vector<bool> l2{0,1,1,1,0,1,1};

	std::vector<bool> l3{1,1,0,1,0,0,1};

	std::vector<vector<bool>> test{l1, l2, l3};
		
	arbre* tree = new arbre(1,5);

	tree->calcul_fitness(test);

	EXPECT_EQ(tree->fitness_,-1);

	delete tree;

};

TEST(GTestTests, TestExpr){

	std::vector<bool> list(2);
	list[0] = 1;
	list[1] = 0;

	bool F = 0;
	bool T = 1;

	noeud** liste_noeud = new noeud*[5];

	liste_noeud[0] = new noeud(1);
	liste_noeud[1] = new noeud(1, F, T);
	liste_noeud[2] = new noeud(1, true, 0);
	liste_noeud[3] = new noeud(2, liste_noeud[0], liste_noeud[1]);
	liste_noeud[4] = new noeud(1, liste_noeud[2], liste_noeud[3]);

	EXPECT_EQ(liste_noeud[4]->expr(), "( ( 1 & x0 ) & ( ~x1 | ( 0 & 1 ) ) )");

	delete liste_noeud[4];
	delete[] liste_noeud;
};


TEST(GTestTests, TestMutAjout){

	arbre* arbretest=new arbre(5);
	EXPECT_EQ(arbretest->nbr_noeuds_,5);
	arbretest->lister_noeuds();  //ajout d'une case au tableau stockant les noeuds.
	arbretest->mutation_ajout();
	arbretest->compter_noeuds();
	EXPECT_EQ(arbretest->nbr_noeuds_,6);
	delete arbretest;

};
TEST(GTestTests, TestMutationDeletion){
	
	arbre* brebre=new arbre(5);
	EXPECT_EQ(brebre->nbr_noeuds_,5);
	brebre->mutation_deletion();
	brebre->compter_noeuds();
	EXPECT_LT(brebre->nbr_noeuds_,5);
	delete brebre;


};









