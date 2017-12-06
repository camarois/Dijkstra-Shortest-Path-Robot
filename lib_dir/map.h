#ifndef MAP_H
#define MAP_H

#include "constantes.h"

//algorithme de Dijkstra, retourne le chemin dans un tableau en paramètre
//passé par référence et la distance directement
uint8_t algoDijsktra(const uint8_t& depart, const uint8_t& fin, uint8_t(&chemin)[MAX_LONGUEUR_CHEMIN]);

//retourne les points qui sont voisins de celui en paramètre dans un 
//tableau de 4 points passé en référence
void retournerPointsVoisins(const uint8_t& point, uint8_t(&tableau)[MAX_NVOISINS]);

//retourne direction du robot selon les points du chemin
uint8_t retournerDirection(uint8_t(&orientation)[NPOINTS][NPOINTS],const uint8_t& premierPoint, const uint8_t& deuxiemePoint);

//permet déplacement du robot selon le chemin le plus court
void deplacementRobot(uint8_t (&chemin)[MAX_LONGUEUR_CHEMIN], uint8_t (&points)[Nobjectif]);

//retourne distance entre deux points
uint8_t retournerDistancePoints(const uint8_t& premierPoint, const uint8_t& deuxiemePoint);

//retour distance du chemin total (peu importe les points) 
uint8_t retournerDistanceChemin(const uint8_t(&chemin)[MAX_LONGUEUR_CHEMIN]);

//application de l'algorithme de Dijkstra entre les points.
//actualise le tableau de distances entre les points.
void simplifier(uint8_t(&distances)[Nobjectif][Nobjectif],
	const uint8_t(&points)[Nobjectif],
	uint8_t(&chemin)[MAX_LONGUEUR_CHEMIN]);

//fonction nearest_neighbor 
//la longueur d'un chemin ne peux pas etre plus longue que le nombre de points.
void nearest_neighbor(const uint8_t(&distances)[Nobjectif][Nobjectif],
	const uint8_t(&points)[Nobjectif],
	uint8_t(&chemins)[Nobjectif][Nobjectif],
	uint8_t(&distancesTotales)[Nobjectif]);

// fonction qui trouve le chemin pour passer sur les 5 points. 
uint8_t trouverChemin(uint8_t(&objectifs)[Nobjectif], uint8_t(&chemin)[MAX_LONGUEUR_CHEMIN]);

//Fonction pour trouver les objectifs au depart
void analyseObjectifs(uint8_t(&points)[Nobjectif]);

//Methode qui place les objectifs aux bons endroits dans la map
void placerObjet(uint8_t quadran, uint8_t distance, uint8_t(&points)[Nobjectif], uint8_t& compteurBebitte);

#endif
