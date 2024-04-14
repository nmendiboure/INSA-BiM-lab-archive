import matplotlib.pyplot as plt

def import_txt():
	with open("fitness","r") as mon_fichier :
		liste_fitness=mon_fichier.readlines()

	return liste_fitness
def conversion(liste_fitness):
	for i in range(len(liste_fitness)):
		liste_fitness[i].strip()

	for i in range(0,len(liste_fitness)):
		liste_fitness[i]=int(liste_fitness[i])
	return liste_fitness


def affichage_fitness():
    liste_fitness= import_txt()
    liste_fitness_int=conversion(liste_fitness)
    n=len(liste_fitness)
    index=[]
    for i in range(n):
	    index.append(i)
    plt.plot(top=0.980,bottom=0.160)
    plt.subplots_adjust(left=0.13, right=0.96, top=0.98, bottom=0.19)
    plt.plot(index,liste_fitness)
    plt.xlabel('nombre de générations')
    plt.ylabel('fitness')
    plt.show()
    



