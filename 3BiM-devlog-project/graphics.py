# A faire :
# installer pip. Si sur MSYS : pacman -S python3-pip puis pip3 install --upgrade pip
# installer graphviz : pip3 install graphviz

from graphviz import Digraph
import matplotlib.pyplot as plt


def plot_adjacency_list(list_edges,file_name):
    """
    Plot a network from  a list of edges

    Args:
        edges_list (list): list of edges, each edge is a tuple with two elements
            each element represents a node and each node is represented itself
            by a tuple, containing its id (str), its label (str) and its color (str)
            check the list of colors at https://www.graphviz.org/doc/info/colors.html
        file_name (str): name of the output file
	
    Example:

    node1 = ('1','+', 'deepskyblue4')
    node2 = ('2','+', 'firebrick1')
    node3 = ("x2", 'x2', 'firebrick1')
    node4 = ("x3", 'x3',  'firebrick1')
    node5 = ("x4", 'x4', 'firebrick1')
    node6 = ("x5", 'x4', 'firebrick1')
    node7 = ("x6", 'x4', 'firebrick1')
    list_edges = [(node1, node2),(node1,node3),(node2,node4),(node2,node5),(node3,node6),(node3,node7)]
"""
    # get nodes
    nodes = []
    for edge in list_edges:
        nodes.append(edge[0])
        nodes.append(edge[1])
    nodes = list(set(nodes))
    # Build a graph
    g = Digraph('G', filename=file_name)
    # add nodes to graph
    for node in nodes:
        g.node(name=node[0], label=node[1], color=node[2], style='filled')
    # add edges
    for edge in list_edges:
        g.edge(edge[0][0], edge[1][0])
    # to pdf
    g.render()

     
def cree_tuples_aretes():
    with open("aretes","r") as mon_fichier :
        liste_aretes=mon_fichier.readlines()
        converted_list=[]
        for element in liste_aretes :
            converted_list.append(element.strip())
        for i in range(len(converted_list)):
            converted_list[i]=tuple(converted_list[i].split(" ") )
        
    return converted_list

def aretes_ordonnees_horizontalement(converted_list):
    list_ordo=[]
#accrochage du noeud principal
    list_ordo.append(converted_list[0])
    for doublon in converted_list:
        if(doublon[0]==list_ordo[0][0] and doublon[1]!=list_ordo[0][1]):
                list_ordo.append(doublon)
                break
#parcourscomplet
    for i, doublon in enumerate(converted_list) :
        for j,duo in enumerate(converted_list) :
            if('x' in doublon[1]) :
                break
            elif(doublon[1]==duo[0]) :
                list_ordo.append(duo)
    return list_ordo
#on a une liste de tuples comme avec un parcours horizontal


#création d'un dico qui associe à chaque identifiant de noeud son numéro d'opérateur
def cree_dico():
    dico={}
    mon_fichier = open("infos_noeuds", "r")
    #lecture=mon_fichier.readline
    for line in mon_fichier:
        lune = line[:len(line)-1]
        lune = lune.split(" ")
        a = lune[0]
        b = lune[1]
        dico[a] = b
        
    return dico

#création d'un dictionnaire qui associe à chaque noeud un tuple avec 3 éléments
def parcours_liste_aretes(liste_ordo,dico):
    dic_comp = {}
    compt=0
    for val in liste_ordo:
        for ident in val:
            if 'x' in ident:
#chaque noeud variable a un identifiant unique compt qui pourra lui être restitué lors du parcours suivant
                dic_comp[(ident, compt)] = (str(compt),ident,'firebrick')
                compt+=1
            else:
                if (dico[ident] == '1'):
                    dic_comp[ident] = (ident,'AND','deepskyblue4')
                elif (dico[ident] == '2'):
                    dic_comp[ident] = (ident,'OR','deepskyblue4')
                elif(dico[ident]=='3'):
                    dic_comp[ident] = (ident,'NOT','deepskyblue4')
                                                
    return dic_comp;

#création de la liste d'arêtes qui associe à chaque noeud du tuple de deux noeuds, le tuple avec les trois éléments du noeud spécifique
def aretes_definitif(dic_comp , liste_ordo):
    edges = []
    compt=0
    for val in liste_ordo:
#seul le deuxième élément du tuple peut contenir une variable car un "noeud variable" ne peut être père
        if 'x' in val[1]:
            node1 = dic_comp[val[0]]
            node2 = dic_comp[(val[1],compt)]
            compt+=1
            nodes = (node1,node2)
            edges.append(nodes)            
        else:
            node1 = dic_comp[val[0]]
            node2 = dic_comp[val[1]]
            nodes = (node1,node2)
            edges.append(nodes)
        
    return edges
   

#méthode finale qui appelle toutes les précédentes méthodes et renvoie le graphe de l'arbre
def encapsulation():
    liste_aretes = cree_tuples_aretes()
    liste_ordonnee = aretes_ordonnees_horizontalement(liste_aretes)
    dico_trituples = parcours_liste_aretes(liste_ordonnee,cree_dico())
    listedef = aretes_definitif(dico_trituples, liste_ordonnee)
    plot_adjacency_list(listedef,'essai')
    







