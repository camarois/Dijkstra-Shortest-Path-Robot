#ifndef CONSTANTES_H
#define CONSTANTES_H

#define F_CPU   8000000UL 	//la vitesse du processeur
#define SORTIE  0xff		//pour definir un port entier en sortie
#define ENTREE  0x00		//pour definir un port entier en entree
#define DELAI   1000		//valeur par defaut d'un delai


#include <util/twi.h>
#include <avr/interrupt.h>
#include <avr/io.h> 
#include <util/delay.h>	//bibliotheque contenant les methodes relatives aux delais
#include <avr/interrupt.h> //Interrupts
#include <stdbool.h>

//Constantes pour le port et les distances
#define port 7

#define THRESHHOLD_PROCHE_PERP 70
#define THRESHHOLD_LOIN_PERP  45

#define THRESHHOLD_PROCHE_DIAG  60
#define THRESHHOLD_LOIN_DIAG    30

//Constantes pour le detecteur de ligne
#define R2 0x08
#define R1 0x10
#define M  0x20
#define L1 0x40
#define L2 0x80

//Constantes pour les points map
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
#define pointD 	0x0D
#define pointE	0x0E
#define pointF	0x0F
#define pointG  0x10
#define pointH  0x11
#define pointN  0xFF

//Constantes pour la map
#define MAX_LONGUEUR_CHEMIN 		0x15
#define MAX_LONGUEUR_CHEMIN_COURT 	0x06
#define MAX_NVOISINS        		0x04
#define NPOINTS             		0x12
#define Nobjectif           		0x05

//Constantes pour les longueurs de chemins
#define DEVANT 			0x00
#define OBLIQUE_1 		0x01
#define DROITE 	        0x02
#define OBLIQUE_2 		0x03
#define DERRIERE 		0x04
#define OBLIQUE_3 		0x05
#define GAUCHE 			0x06
#define OBLIQUE_4 		0x07

//Constantes pour les couleurs de la DEL
#define ROUGE   0x01		//pour afficher la couleur rouge
#define VERT    0x02		//pour afficher la couleur vert
#define ETEINT	0x00		//pour afficher la couleur noir

//Constantes pour lire la musique et mettre en mémoire
#define ATT 0x02
#define DAL	0x44
#define DET	0x45
#define SGO	0x48
#define SAR	0x09
#define FIN	0xFF

#include "setup.h"
#include "son.h"
#include "moteurs.h"
#include "del.h"
#include "minuterie.h"
#include "can.h"
#include "memoire_24.h"
#include "detecteurLigne.h"
#include "detecteurDistance.h"
#include "map.h"
#endif
