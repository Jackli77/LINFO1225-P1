#!/usr/bin/env python3

# Exemple d'utilisation de la librairie python matplotlib pour LINFO1252

# On importe numpy (pour se faciliter la vie) et matplotlib
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

# On crée une première figure, par défaut toutes les commandes plt qui vont suivre vont s'appliquer sur cette figure (qui est la dernière déclarée).
fig1 = plt.figure()
fd = pd.read_csv("script.csv")
threads = fd.nb_coeurs.values 
temps = fd.temps.values 

# température moyenne l'année passée à Bruxelles
T_b = []
# température moyenne l'année passée à Marseille
T_m = [fd.nb_coeurs.values[0]]
for i in range(1,len(fd.nb_coeurs.values)):
    if fd.nb_coeurs.values[0] == fd.nb_coeurs.values[i]:
        break
    T_m.append(fd.nb_coeurs.values[i])
# Les mois correspondant
for i in range(0,len(T_m)):
    j = i
    arr = []
    while j < len(temps):
        arr.append(temps[j])
        j += len(T_m)
    T_b.append(np.mean(arr))
        
        
        

# On trace la température moyenne en fonction du mois en bleu avec un trait plein de 1 pixel d'épaisseur
plt.plot(T_m, T_b, color="blue", linewidth=1.0, linestyle="-")

# Possibles linestyles pour le plot : [ '-' | '--' | '-.' | ':' | ...]
# Pour vous amusez avec les couleurs disponibles : https://matplotlib.org/3.1.0/gallery/color/named_colors.html
# idem avec les températures de Marseille

# Limiter le range de valeurs affichées pour l'axe des x
plt.xlim(1,len(T_m))

# Forcer la graduation en y. np.linspace découpe l'intervalle [1,12] en parties égales
# Il renvoie 12 graduations [1,2,3...12]. (peut aussi être fait manuellement)
plt.xticks(np.linspace(1,len(T_m),len(T_m)))

# Donner un label à l'axe x
plt.xlabel('Threads')

# Limiter le range de valeur affiché pour y


# Forcer la graduation en y. np.linspace découpe l'intervalle [0,30] en parties égales et renvoie 7 graduations (5 graduations + 2 pour '0' et '30')


# Donner un label à l'axe y
plt.ylabel('Temps moyen')

# Donner un titre à votre graphe.
plt.title('mesure de performance')

# Permet d'ajouter une grille au graphe, rendant la lecture de vos données plus facile.
plt.grid(True)

# Ajouter une légende, loc peut prendre différentes valeurs (https://matplotlib.org/3.1.1/api/_as_gen/matplotlib.pyplot.legend.html)

# on enregistre le graphique. L'extension est directement déduite du nom donné en argument (png par défault).
plt.savefig("Exemple.png")
plt.savefig("Exemple.pdf")

# Optionnel : on affiche le graphe à l'écran (note: show est un appel bloquant, tant que le graphe n'est pas fermé, on est bloqué)
plt.show()

# On ferme proprement le plot.
plt.close()
