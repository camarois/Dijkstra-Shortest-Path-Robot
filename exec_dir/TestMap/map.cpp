#include "map.h"


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

using namespace std;
//#include "detecteurLigne.h"
//#include "detecteurDistance.h"

//algorithme de Dijkstra, retourne le chemin dans un tableau en paramètre
//passé par référence et la distance directement
uint8_t algo1S(const uint8_t& depart, const uint8_t& fin, uint8_t(&chemin)[MAX_LONGUEUR_CHEMIN])
{
	//initialisation
	uint8_t chemins[NPOINTS][MAX_LONGUEUR_CHEMIN];
	uint8_t distances[NPOINTS];

	bool actif[NPOINTS];

	for (uint8_t i = 0; i < NPOINTS; i++)
	{
		distances[i] = pointN;
		actif[i] = true;
		chemins[i][0] = depart;
		for (uint8_t j = 1; j < MAX_LONGUEUR_CHEMIN; j++)
			chemins[i][j] = pointN;
	}

	//distance du point de depart est null
	distances[depart] = 0;

	//boucle jusqu'a ce que la fin soit le point actif le plus proche
	while (actif[fin])
	{
		//regarder point actif le plus proche
		uint8_t	point = fin;
		uint8_t i;
		for (i = 1; i < NPOINTS; i++)
		{
			if (actif[i] && (distances[i] < distances[point]))
				point = i;
		}

		//si c'est la fin, fin = true;
		if (point == fin)
			actif[fin] = false;

		//sinon:
		else
		{
			//regarder voisins
			uint8_t voisins[MAX_NVOISINS];
			retournerPointsVoisins(point, voisins);
			//pour chaque voisins:
			i = 0;
			while (voisins[i] != pointN && i < MAX_NVOISINS)
			{
				//regarder distance avec nouveau chemin
				uint8_t nouveauChemin[MAX_LONGUEUR_CHEMIN];

				//operateur ou fonction copie?
				for (uint8_t i = 0; i < MAX_LONGUEUR_CHEMIN; i++)
				{
					nouveauChemin[i] = chemins[point][i];
				}

				uint8_t j = 0;
				while (nouveauChemin[j] != pointN) j++;
				nouveauChemin[j] = voisins[i];


				uint8_t nouvelleDistance = retournerDistanceChemin(nouveauChemin);


				//si ce chemin est plus court:
				if (nouvelleDistance < distances[voisins[i]])
				{
					//utilise ce chemin
					//operateur ou fonction copie?
					for (j = 0; j < MAX_LONGUEUR_CHEMIN; j++)
					{
						chemins[voisins[i]][j] = nouveauChemin[j];
					}
					distances[voisins[i]] = nouvelleDistance;
				}
				i++;
			}
			//point devient inactif
			actif[point] = false;

		}
	}
	for (uint8_t i = 0; i < MAX_LONGUEUR_CHEMIN; i++)
	{
		chemin[i] = chemins[fin][i];
	}
	return distances[fin];
}

//retourne les points qui sont voisins de celui en paramètre dans un 
//tableau de 4 points passé en référence
void retournerPointsVoisins(const uint8_t& point, uint8_t(&tableau)[MAX_NVOISINS]) {

	// 0xff représantant un point non existant, tout les points on minimum 3 points voisins.

	tableau[3] = pointN;
	switch (point)
	{
    case point0:
		tableau[0] = point7;
		tableau[1] = point1;
		tableau[2] = point3;
		tableau[3] = point5;
		break;
	case point1:
		tableau[0] = point8;
		tableau[1] = pointA;
		tableau[2] = point2;
		tableau[3] = point0;
		break;
	case point2:
		tableau[0] = point1;
		tableau[1] = pointB;
		tableau[2] = point3;
		tableau[3] = pointB;	//vérifier
		break;
	case point3:
		tableau[0] = point0;
		tableau[1] = point2;
		tableau[2] = pointC;
		tableau[3] = point4;
		break;
	case point4:
		tableau[0] = point5;
		tableau[1] = pointD;
		tableau[2] = point3;
		tableau[3] = pointD;	//vérifier
		break;
	case point5:
		tableau[0] = point6;
		tableau[1] = point0;
		tableau[2] = point4;
		tableau[3] = pointE;
		break;
	case point6:
		tableau[0] = point7;
		tableau[1] = pointF;
		tableau[2] = point5;
		tableau[3] = pointF;	//vérifier
		break;
	case point7:
		tableau[0] = pointG;
		tableau[1] = point8;
		tableau[2] = point0;
		tableau[3] = point6;
		break;
	case point8:
		tableau[0] = point7;
		tableau[1] = pointH;
        tableau[2] = point1;
		tableau[3] = pointH;	//vérifier
		break;
	case pointA:
		tableau[0] = pointH;
		tableau[1] = SORTIE_DROITE;
		tableau[2] = pointB;
        tableau[3] = point1;
		break;
	case pointB:
		tableau[0] = pointA;
		tableau[1] = SORTIE_OBLIQUE;
		tableau[2] = pointC;
        tableau[3] = point2;
		break;
	case pointC:
		tableau[0] = point3;
		tableau[1] = pointB;
		tableau[2] = SORTIE_T;
        tableau[3] = pointD;
		break;
	case pointD:
		tableau[0] = pointC;
		tableau[1] = point4;
		tableau[2] = pointE;
        tableau[3] = SORTIE_OBLIQUE;
		break;
	case pointE:
		tableau[0] = pointF;
		tableau[1] = point5;
		tableau[2] = pointD;
        tableau[3] = SORTIE_LONGUE;
		break;
	case pointF:
		tableau[0] = pointG;
		tableau[1] = point6;
		tableau[2] = pointE;
        tableau[3] = SORTIE_OBLIQUE;
		break;
	case pointG:
		tableau[0] = SORTIE_DEMI_T;
		tableau[1] = pointH;
		tableau[2] = point7;
        tableau[3] = pointF;
		break;
	case pointH:
		tableau[0] = pointG;
		tableau[1] = SORTIE_OBLIQUE;
		tableau[2] = pointA;
        tableau[3] = point8;
		break;
	}
}
//retourne index des points voisins
uint8_t retourneIndexVoisin(const uint8_t& premierPoint, const uint8_t& deuxiemePoint) {
    uint8_t i = 0;
    uint8_t voisins[MAX_NVOISINS];
    retournerPointsVoisins(premierPoint, voisins);
    
    while (voisins[i] != deuxiemePoint && i < MAX_NVOISINS)
         i++; 
    
    return i;
}

//permet déplacement du robot selon le chemin final et le tableau contenant les chemins Dijkstra
void deplacementRobot(uint8_t(&chemin)[MAX_LONGUEUR_CHEMIN],const uint8_t(&points)[Nobjectif]){
    uint8_t i = 0, j = 0, index;
    
    while(i < Nobjectif){                   //itère sur les points du chemin final
    
		if (points[i] > points[(i + 1)])    //change d'orientation 
			//FUNCTION 180 DEGREES;
			cout << "180 DEGRES" << endl;
    
        while ( chemin[j] =! points[i]){       //itère sur les points intermédiaires entre les points du chemin final (Dijkstra)
        
            index = retourneIndexVoisin(chemin[i],chemin[i+1]);
            
			switch (index) {
				case 0:
					cout << "GAUCHE" << endl;
					//tournerGauche();
					break;
				case 1:
					cout << "AVANCE" << endl;
					//suisLigne(100);
					break;
				case 2:
					cout << "DROITE" << endl;
					//tournerGauche();
					break;
				case 3:
					cout << "RECULE" << endl;
					//suisLigne(100);     //devrait déjà être avoir la bonne orientation avec le if
					break;
			}
			j++;
		}
        i++;
    }
}
    
//retourne distance entre deux points
uint8_t retournerDistancePoints(const uint8_t& premierPoint, const uint8_t& deuxiemePoint) {
	switch (premierPoint)
	{
	case point0:
		if (deuxiemePoint == point1 || deuxiemePoint == point3 || deuxiemePoint == point5 || deuxiemePoint == point7)
			return 5;
		break;
	case point1:
		if (deuxiemePoint == point2 || deuxiemePoint == point8 || deuxiemePoint == pointA || deuxiemePoint == point0)
			return 5;
		break;
	case point2:
		if (deuxiemePoint == point1 || deuxiemePoint == point3)
			return 5;
		else if (deuxiemePoint == pointB)
			return 7;
		break;
	case point3:
		if (deuxiemePoint == point2 || deuxiemePoint == pointC || deuxiemePoint == point4 || deuxiemePoint == pointN)
			return 5;
		break;
	case point4:
		if (deuxiemePoint == point3 || deuxiemePoint == point5)
			return 5;
		else if (deuxiemePoint == pointD)
			return 7;
		break;
	case point5:
		if (deuxiemePoint == point4 || deuxiemePoint == point6 || deuxiemePoint == pointE || deuxiemePoint == pointN)
			return 5;
		break;
	case point6:
		if (deuxiemePoint == point5 || deuxiemePoint == point7)
			return 5;
		else if (deuxiemePoint == pointF)
			return 7;
		break;
	case point7:
		if (deuxiemePoint == point6 || deuxiemePoint == point8 || deuxiemePoint == pointG || deuxiemePoint == pointN)
			return 5;
		break;
	case point8:
		if (deuxiemePoint == point7 || deuxiemePoint == point1)
			return 5;
		else if (deuxiemePoint == pointH)
			return 7;
		break;
	case pointA:
		if (deuxiemePoint == pointB || deuxiemePoint == pointH)
			return 10;
		else if (deuxiemePoint == point1)
			return 5;
		break;
	case pointB:
		if (deuxiemePoint == pointA || deuxiemePoint == pointC)
			return 10;
		else if (deuxiemePoint == point2)
			return 7;
		break;
	case pointC:
		if (deuxiemePoint == pointB || deuxiemePoint == pointD)
			return 10;
		else if (deuxiemePoint == point3)
			return 5;
		break;
	case pointD:
		if (deuxiemePoint == pointC || deuxiemePoint == pointE)
			return 10;
		else if (deuxiemePoint == point4)
			return 7;
		break;
	case pointE:
		if (deuxiemePoint == pointD || deuxiemePoint == pointF)
			return 10;
		else if (deuxiemePoint == point5)
			return 5;
		break;
	case pointF:
		if (deuxiemePoint == pointE || deuxiemePoint == pointG)
			return 10;
		else if (deuxiemePoint == point6)
			return 7;
		break;
	case pointG:
		if (deuxiemePoint == pointF || deuxiemePoint == pointH)
			return 10;
		else if (deuxiemePoint == point7)
			return 5;
		break;
	case pointH:
		if (deuxiemePoint == pointA || deuxiemePoint == pointG)
			return 10;
		else if (deuxiemePoint == point8)
			return 7;
		break;
	}
	return pointN; // erreur si on demande distance entre deux points non voisins 
				   //eventuellement, algo1s qui appel retournerDistance Points ?
}

//retour distance du chemin total (peu importe les points) 
uint8_t retournerDistanceChemin(const uint8_t (&chemin)[MAX_LONGUEUR_CHEMIN]) {
	uint8_t i = 1;
	uint8_t distance = 0;
	while (chemin[i] != pointN && i < MAX_LONGUEUR_CHEMIN)
	{
		distance += retournerDistancePoints(chemin[(i - 1)], chemin[i]);
		i++;
	}
	return distance;
}


//application de l'algorithme de Dijkstra entre les points.
//actualise le tableau de distances entre les points.

void simplifier(uint8_t(&distances)[Nobjectif][Nobjectif],
	const uint8_t(&points)[Nobjectif],
	uint8_t(&chemins)[Nobjectif][Nobjectif][MAX_LONGUEUR_CHEMIN])
{
	//pour chaque relation entre les points
	for (uint8_t i = 0; i < (Nobjectif - 1); i++)
	{
		//appliquer algo1S pour obtenir le chemin et la distance.
		// nous avons un tableau de distances et un tableau de chemins entre chaque point.
		for (uint8_t j = i + 1; j < Nobjectif; j++)
		{
			distances[i][j] = algo1S(points[i], points[j], chemins[i][j]);
			distances[j][i] = distances[i][j];

			//compter le nombre de point necessaire.
			uint8_t compteur = 0;
			while (chemins[i][j][compteur] != pointN && compteur != MAX_LONGUEUR_CHEMIN)
			{
				compteur++;
			}
			//ajouter les points dans le sens inverse.
			for (uint8_t k = 0 ;k < compteur; k++)
				chemins[j][i][k] = chemins[i][j][compteur-k-1];
		}

	}
	//les distances et les chemins ont tout été mis à jour
}

//fonction nearest_neighbor 
//la longueur d'un chemin ne peux pas etre plus longue que le nombre de points.
void nearest_neighbor(const uint8_t(&distances)[Nobjectif][Nobjectif],
	const uint8_t(&points)[Nobjectif],
	uint8_t(&chemins)[Nobjectif][Nobjectif],
	uint8_t(&distancesTotales)[Nobjectif])
{
	//pour chaque point etant un point de depart, 
	bool actif[Nobjectif];
	for (uint8_t i = 0; i < Nobjectif; i++)
	{
		//mettre tout les points actifs
		for (uint8_t i = 0; i < Nobjectif; i++) actif[i] = true;
		chemins[i][0] = i; //chemin de depart au premier point
		actif[i] = false; // ce point devient inactif
		distancesTotales[i] = 0;

		//ajouter le point le plus pret, pour tout les points
		for (uint8_t j = 0; j < (Nobjectif - 1); j++)
		{
			//trouver le point le plus pret
			uint8_t k = 0;
			uint8_t prochain = pointN;
			while (k < Nobjectif)
			{
				if (actif[k] && prochain == pointN)
					prochain = k;
				else if (actif[k] &&
					distances[chemins[i][j]][k] <
					distances[chemins[i][j]][prochain])
					prochain = k;
				k++;
			}
			//l'ajouter
			chemins[i][j + 1] = prochain;
			actif[prochain] = false;
			distancesTotales[i] += distances[chemins[i][j]][prochain];
		}
		// ce chemin est actualise
	}
	//voyons maintenant avec les fins. 
	for (uint8_t i = 0; i < Nobjectif; i++)
	{
		uint8_t pointFin = chemins[i][Nobjectif - 1];
		if (distancesTotales[i] < distancesTotales[pointFin])
		{
			for (uint8_t j = 0; j < Nobjectif; j++)
			{
				chemins[pointFin][j] = chemins[i][Nobjectif - 1 - j];
			}
		}
	}
	//mainenant, nous avons les chemins a partir d'un objectif pour aller
	//aux autres et la distance totale
}

// fonction qui trouve le chemin pour passer sur les 5 points. 
// retourne la distance total du chemin.
// dans les chemin, le premier point est toujours le point ou on se trouve.
/*
uint8_t trouverChemin(uint8_t(&objectifs)[Nobjectif], uint8_t(&chemin)[MAX_LONGUEUR_CHEMIN])
{
	//pour chaque relation entre les points, trouver meilleur chemin et distance
	uint8_t distances[Nobjectif][Nobjectif];
	uint8_t chemins [Nobjectif][Nobjectif][MAX_LONGUEUR_CHEMIN];
	
	simplifier(distances, objectifs, chemins); //rempli le tableau de distances entre nos points.
	
	distancesFictive[Nobjectif];
	
	//trouver de chaque point, la distance et le meilleur chemin pour aller a tout les prochains points.
	
	uint8_t cheminGeneral; //chemin entre objectifs
	
	nearest_neighbor(distances, chemins, objectifs);
	//determiner chemin du point de depart a la sortie fictive qui inclut tout de passer par tout les points.
	
	
}
*/
/*void analyseObjectifs(uint8_t(&objectifs)[Nobjectif]){
    uint8_t quadran = 0;
    rotationStationnaire();
    ligneDetecte()
    switch (quadran)
    {
        case 0:
            if(ligneDetecte() && insecteDetecte()){
                if(isInsecteProche())
                    insecteProcheTrouve();
                    //PLACER OBJ 1
                else
                    insecteLoinTrouve();
                    //PLACER OBJ A
            }
            if(!ligneDetecte && insecteDetecte()){
                if(isInsecteProche())
                    insecteProcheTrouve();
                    //PLACER OBJ 2
                else
                    insecteLoinTrouve();
                    //PLACER OBJ B
            }
            if(capteurDroite2())
                quadran++;
        case 1:
            if(ligneDetecte() && insecteDetecte()){
                if(isInsecteProche())
                    insecteProcheTrouve();
                    //PLACER OBJ 3
                else
                    insecteLoinTrouve();
                    //PLACER OBJ C
            }
            if(!ligneDetecte && insecteDetecte()){
                if(isInsecteProche())
                    insecteProcheTrouve();
                    //PLACER OBJ 4
                else
                    insecteLoinTrouve();
                    //PLACER OBJ D
            }
            if(capteurDroite2())
                quadran++;
        case 2:
            if(ligneDetecte() && insecteDetecte()){
                if(isInsecteProche())
                    insecteProcheTrouve();
                    //PLACER OBJ 5
                else
                    insecteLoinTrouve();
                    //PLACER OBJ E
            }
            if(!ligneDetecte && insecteDetecte()){
                if(isInsecteProche())
                    insecteProcheTrouve();
                    //PLACER OBJ 6
                else
                    insecteLoinTrouve();
                    //PLACER OBJ F
            }
            if(capteurDroite2())
                quadran++;
        case 3:
            if(ligneDetecte() && insecteDetecte()){
                if(isInsecteProche())
                    insecteProcheTrouve();
                    //PLACER OBJ 7
                else
                    insecteLoinTrouve();
                    //PLACER OBJ G
            }
            if(!ligneDetecte && insecteDetecte()){
                if(isInsecteProche())
                    insecteProcheTrouve();
                    //PLACER OBJ 8
                else
                    insecteLoinTrouve();
                    //PLACER OBJ H
            }
            quadran++;
        case 4:
            
            break;
    }*/
                
