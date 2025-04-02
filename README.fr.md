# Ft_traceroute

[![fr](https://img.shields.io/badge/Langue-fr-blue)](README.fr.md)

$$\color{darkgreen}{{\Huge \mathbf {125/100 ✅}}}$$

## L'objectif

Reproduire simplement la commande `traceroute` avec des socket udp

Il faut seulement gérer l'option `--help`

**Ce programme doit utiliser des socket brute pour recevoir des packet ICMP donc vous devez avoir les droits administrateur !**

## Execution

Ce projet contient un `Makefile`.
Il compile tous les fichier présent dans `src/` et produit un exécutable.
Le programme doit être lancer comme suit :
````sh
sudo ./ft_traceroute [options] addresses [packetlen]
````

$\color{red}{\large {\mathbf {⚠⚠\ Vous\ devez\ avoir\ les\ droits\ administrateur\ pour\ executer\ le\ programme\ ⚠⚠}}}$

Vous pouvez mettre soit des adresses ip (`172.217.20.163`), soit des adresses DNS (`google.fr`).
Vous a pouvez également mettre les options des bonus dans l'ordre que vous voulez, tapez `--help` pour plus de détails.

## Bonus

Le programme gère ègalement ces options :
| Options | Description |
| ---- | ----- |
| -p | Numéro du Port number où envoyer le packet udp |
| -m | Nombre maximal de ttl authoriser |
| -f | Premier ttl au début du programme |
| -n | Eviter la resolution DNS pour chaque packet |

