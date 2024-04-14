#script de configuration pour l'utilisation de distulis
#ce module sert à créer et installer un module, donc nos fichiers c++ dans ce cas
#pour compiler,faire : python setup.py build puis python setup.py install

import os
os.environ["CC"] = "c++"
from distutils.core import setup, Extension
module = Extension('Projet_Devlog', ["arbre.cpp","noeud.cpp","main.cpp"],libraries=[])
module.extra_compile_args = []#,'-pg']

setup(name='Projet_Devlog', description="Configuration du module", version='1.0')
	  