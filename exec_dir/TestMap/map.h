/*#include "son.h"
#include "moteurs.h"
#include "del.h"
#include "minuterie.h"
#include "can.h"
#include "memoire_24.h"
#include "usart.cpp"
#include "detecteurLigne.h"*/
#include <stdint.h>
#include <cstdint>
#include <iostream>

#define point0	0x00
#define point1	0x01
#define point2	0x02
#define point3	0x03
#define point4	0x04
#define point5	0x05
#define point6	0x06
#define point7	0x07
#define point8	0x08
#define pointA	0x0A
#define pointB	0x0B
#define pointC	0x0C
#define pointD	0x0D
#define pointE	0x0E
#define pointF	0x0F
#define pointG	0x10
#define pointH	0x11
#define pointN	0xFF

#define MAX_LONGUEUR_CHEMIN 0x20
#define MAX_NVOISINS        0x4
#define NPOINTS             0x18
#define Nobjectif           0x5

#define SORTIE_LONGUE   0x13
#define SORTIE_DROITE   0x14
#define SORTIE_OBLIQUE  0x15
#define SORTIE_T        0x16
#define SORTIE_DEMI_T   0x17



//algorithme de Dijkstra, retourne le chemin dans un tableau en paramètre
//passé par référence et la distance directement
uint8_t algo1S(const uint8_t& depart, const uint8_t& fin, uint8_t(&chemin)[MAX_LONGUEUR_CHEMIN]);

//retourne les points qui sont voisins de celui en paramètre dans un 
//tableau de 4 points passé en référence
void retournerPointsVoisins(const uint8_t& point, uint8_t(&tableau)[MAX_NVOISINS]);

//retourne index du tableau VOISINS selon deux points en paramètres
uint8_t retourneIndexVoisin(const uint8_t& premierPoint, const uint8_t& deuxiemePoint);

//permet déplacement du robot selon le chemin final et le tableau contenant les chemins Dijkstra
void deplacementRobot(uint8_t (&chemin)[MAX_LONGUEUR_CHEMIN], const uint8_t (&points)[Nobjectif]);

//retourne distance entre deux points
uint8_t retournerDistancePoints(const uint8_t& premierPoint, const uint8_t& deuxiemePoint);

//retour distance du chemin total (peu importe les points) 
uint8_t retournerDistanceChemin(const uint8_t (&chemin)[MAX_LONGUEUR_CHEMIN]);

//application de l'algorithme de Dijkstra entre les points.
//actualise le tableau de distances entre les points.
void simplifier(uint8_t(&distances)[Nobjectif][Nobjectif], 
				const uint8_t(&points)[Nobjectif], 
				uint8_t(&chemins)[Nobjectif][Nobjectif][MAX_LONGUEUR_CHEMIN]);

//fonction nearest_neighbor 
//la longueur d'un chemin ne peux pas etre plus longue que le nombre de points.
void nearest_neighbor(const uint8_t (&distances)[Nobjectif][Nobjectif],
					const uint8_t (&points)[Nobjectif],
					uint8_t (&chemins)[Nobjectif][Nobjectif],
					uint8_t (&distancesTotales)[Nobjectif]);

// fonction qui trouve le chemin pour passer sur les 5 points. 
//uint8_t trouverChemin(uint8_t(&objectifs)[Nobjectif], uint8_t(&chemin)[MAX_LONGUEUR_CHEMIN]);
