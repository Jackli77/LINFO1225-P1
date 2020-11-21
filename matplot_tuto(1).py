#!/usr/bin/env python3

# Exemple d'utilisation de la librairie python matplotlib pour LINFO1252

# On importe numpy (pour se faciliter la vie) et matplotlib
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

# On crée une première figure, par défaut toutes les commandes plt qui vont suivre vont s'appliquer sur cette figure (qui est la dernière déclarée).
fig1 = plt.figure()
philo = pd.read_csv("philo.csv")
prodcons = pd.read_csv("prodcons.csv")
read = pd.read_csv("read.csv")
test = pd.read_csv("test.csv")
threads_philo = philo.nb_coeurs.values 
temps_philo = philo.temps.values 
threads_prod = prodcons.nbcoeurs.values 
temps_prod = prodcons.temps.values 
threads_read = read.nbcoeurs.values 
temps_read = read.temps.values
threads_test = test.nbcoeurs.values 
temps_test = test.temps.values 

def philosophe(temps,threads):
    T_b = []
    T_m = [philo.nb_coeurs.values[0]]
    for i in range(1,len(philo.nb_coeurs.values)):
        if philo.nb_coeurs.values[0] == philo.nb_coeurs.values[i]:
            break
        T_m.append(philo.nb_coeurs.values[i])
    for i in range(0,len(T_m)):
        j = i
        arr = []
        while j < len(temps):
            arr.append(temps[j])
            j += len(T_m)
        print(arr)
        T_b.append(np.mean(arr))
    plt.plot(T_m, T_b, color="blue", linewidth=1.0, linestyle="-")
    plt.xlim(1,len(T_m))
    plt.xticks(np.linspace(1,len(T_m),len(T_m)))
    plt.xlabel('Threads')
    plt.ylabel('Temps moyen')
    plt.title('mesure de performance philosophes')
    plt.grid(True)
    plt.savefig("philo.png")
    plt.show()
    plt.close()

def producteurs(temps,threads):
    T_b = []
    T_m = [prodcons.nbcoeurs.values[0]]
    for i in range(1,len(prodcons.nbcoeurs.values)):
        if prodcons.nbcoeurs.values[0] == prodcons.nbcoeurs.values[i]:
            break
        T_m.append(prodcons.nbcoeurs.values[i])
    for i in range(0,len(T_m)):
        j = i
        arr = []
        while j < len(temps):
            arr.append(temps[j])
            j += len(T_m)
        T_b.append(np.mean(arr))
    plt.plot(T_m, T_b, color="blue", linewidth=1.0, linestyle="-")
    plt.xlim(1,len(T_m))
    plt.xticks(np.linspace(1,len(T_m),len(T_m)))
    plt.xlabel('Threads')
    plt.ylabel('Temps moyen')
    plt.title('mesure de performance producteurs consommateurs')
    plt.grid(True)
    plt.savefig("prodcons.png")
    plt.show()
    plt.close()
def reader(temps, threads):
    T_b = []
    T_m = [read.nbcoeurs.values[0]]
    for i in range(1,len(read.nbcoeurs.values)):
        if read.nbcoeurs.values[0] == read.nbcoeurs.values[i]:
            break
        T_m.append(read.nbcoeurs.values[i])
    for i in range(0,len(T_m)):
        j = i
        arr = []
        while j < len(temps):
            arr.append(temps[j])
            j += len(T_m)
        T_b.append(np.mean(arr))
    plt.plot(T_m, T_b, color="blue", linewidth=1.0, linestyle="-")
    plt.xlim(1,len(T_m))
    plt.xticks(np.linspace(1,len(T_m),len(T_m)))
    plt.xlabel('Threads')
    plt.ylabel('Temps moyen')
    plt.title('mesure de performance lecteurs écrivains')
    plt.grid(True)
    plt.savefig("read.png")
    plt.show()
    plt.close()
def testing(temps,threads):
    T_b = []
    T_m = [test.nbcoeurs.values[0]]
    for i in range(1,len(test.nbcoeurs.values)):
        if test.nbcoeurs.values[0] == test.nbcoeurs.values[i]:
            break
        T_m.append(test.nbcoeurs.values[i])
    for i in range(0,len(T_m)):
        j = i
        arr = []
        while j < len(temps):
            arr.append(temps[j])
            j += len(T_m)
        T_b.append(np.mean(arr))
    plt.plot(T_m, T_b, color="blue", linewidth=1.0, linestyle="-")
    plt.xlim(1,len(T_m))
    plt.xticks(np.linspace(1,len(T_m),len(T_m)))
    plt.xlabel('Threads')
    plt.ylabel('Temps moyen')
    plt.title('mesure de performance test and set')
    plt.grid(True)
    plt.savefig("test.png")
    plt.show()
    plt.close()
philosophe(temps_philo,threads_philo)
producteurs(temps_prod,threads_prod)
reader(temps_read,threads_read)
testing(temps_test,threads_test)
