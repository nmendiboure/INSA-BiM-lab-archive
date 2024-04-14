# A faire : 
#installer pip. Si sur MSYS : pacman -S python3-pip puis pip3 install --upgrade pip
#installer sympy : pip install sympy

import sympy as sp

#fonction qui importe le contenu du fichier texte contenant la formule

def import_txt(nomFichier):
	mon_fichier=open(nomFichier,"r")
	contenu=mon_fichier.read()
	mon_fichier.close()
	return contenu 


"""
sp.init_printing() #pour que les expressions soient print de façon jolie

#simplification de la formule
print(sp.simplify(contenu))


#exemple avec des chiffres
x=sp.symbols('x') #définir x sinon il connait pas
print(sp.simplify(1*x*2+1)) # simplifier l'expression pour qu'elle soit plus lisible et simple
a=12*x**3
f=sp.lambdify(x,a)#traduit une expression Sympy en Python
print(f(3)) #retourne la valeur de cette fonction


#exemple avec des booléens 
x1, x2, x3 =sp.symbols('x1, x2, x3')
f1= (x1 & x2 & x3) | (~x1 & ~x3)
print(sp.simplify(f1))

"""

def simplification_formule(nomFichier):
    contenu=import_txt(nomFichier)
    x=sp.symbols('x')
    b=sp.simplify(contenu)
    mon_fichier=open("stockage_txt_formule_simplifié.txt","w")
    mon_fichier.write(str(b))
    mon_fichier.close()
    return b    

    
                                
    
