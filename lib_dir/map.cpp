#include "map.h"

//matrice utilisée pour traduire le chemin en mouvement
uint8_t orientation[NPOINTS][NPOINTS] = {
	{0xFF, DEVANT, 0xFF, DROITE, 0xFF, DERRIERE, 0xFF, GAUCHE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
	{DERRIERE, 0xFF, DROITE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, GAUCHE, 0xFF, DEVANT, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
	{0xFF, GAUCHE, 0xFF, DERRIERE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, OBLIQUE_1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
	{GAUCHE, 0xFF, DEVANT, 0xFF, DERRIERE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, DROITE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
	{0xFF, 0xFF, 0xFF, DEVANT, 0xFF, GAUCHE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, OBLIQUE_2, 0xFF, 0xFF, 0xFF, 0xFF},
	{DEVANT, 0xFF, 0xFF, 0xFF, DROITE, 0xFF, GAUCHE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, DERRIERE, 0xFF, 0xFF, 0xFF},
	{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, DROITE, 0xFF, DEVANT, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, OBLIQUE_3, 0xFF, 0xFF},
	{DROITE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, DERRIERE, 0xFF, DEVANT, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, GAUCHE, 0xFF},
	{0xFF, DROITE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, DERRIERE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, OBLIQUE_4},
	{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
	{0xFF, DERRIERE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, DROITE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, GAUCHE},
	{0xFF, 0xFF, OBLIQUE_1,	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, GAUCHE, 0xFF, DERRIERE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
	{0xFF, 0xFF, 0xFF, GAUCHE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, DEVANT, 0xFF, DERRIERE, 0xFF, 0xFF, 0xFF, 0xFF},
	{0xFF, 0xFF, 0xFF, 0xFF, OBLIQUE_2,	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, DEVANT, 0xFF, GAUCHE, 0xFF, 0xFF, 0xFF},
	{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, DEVANT, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, DROITE, 0xFF, GAUCHE, 0xFF, 0xFF},
	{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, OBLIQUE_3,	0xFF, 0xFF,	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, DROITE, 0xFF, DEVANT, 0xFF},
	{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, DROITE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, DERRIERE, 0xFF, DEVANT},
	{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, OBLIQUE_4,	0xFF, DROITE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, DERRIERE, 0xFF}
};

//Nombre reel d'objectifs
uint8_t nrobjectif = 1;

//algorithme de Dijkstra, retourne le chemin dans un tableau en paramètre
//passé par référence et la distance directement
uint8_t algoDijsktra(const uint8_t& depart, const uint8_t& fin, uint8_t(&chemin)[MAX_LONGUEUR_CHEMIN])
{



	//			Dijkstra(G, Poids, sdeb)
	//			1 Initialisation(G, sdeb)
	///1 pour chaque point s de G faire
	///	2    d[s] : = infini             // on initialise les sommets autres que sdeb à infini
	///	3 fin pour
	///	4 d[sdeb] : = 0                        // sdeb étant le point le plus proche de sdeb 

	// test si on a affaire a un point qui existe
	if (depart == pointN || fin == pointN)
	{
		for (uint8_t i = 0; i < MAX_LONGUEUR_CHEMIN; i++)
			chemin[i] = pointN;
		return 0xff;
	}

	//initialisation
	uint8_t distances[NPOINTS];
	uint8_t precedant[NPOINTS];
	for (uint8_t i = 0; i < NPOINTS; i++)
	{
		distances[i] = 0xff;
	}
	distances[depart] = 0;





	//			2 Q : = ensemble de tous les nœuds //actif

	bool actif[NPOINTS];
	for (uint8_t i = 0; i < NPOINTS; i++) actif[i] = true; //quand 1 point est actif, c'est qu'il est dans l'ensemble Q



//			3 tant que Q n'est pas un ensemble vide faire // ici on vérifie juste pour la fin

	while (actif[fin])
	{

		//			4       s1 : = Trouve_min(Q)

		///mini: = infini
		///	2 sommet : = -1
		///	3 pour chaque sommet s de Q
		///	4    si d[s] < mini
		///	5    alors
		///	6        mini : = d[s]
		///	7        sommet : = s
		///	8 renvoyer sommet

		uint8_t s1 = fin; // sommetProche, on initialise à la fin, pour qu'il priorise la fin si il a un cas d'égalité.
		{
			uint8_t distanceProche = distances[fin];
			for (uint8_t i = 0; i < NPOINTS; i++)
			{
				if (actif[i] && (distances[i] < distanceProche))
				{
					s1 = i;
					distanceProche = distances[i];
				}
			}
		}

		//			5       Q : = Q privé de s1 -> enleve s1 de Q

		actif[s1] = false;

		if (s1 == fin) break; // histoire de s'eviter quelques lignes de codes inutiles.

		//			6       pour chaque nœud s2 voisin de s1 

		uint8_t voisins[MAX_NVOISINS];
		retournerPointsVoisins(s1, voisins);


		for (uint8_t i = 0; i < MAX_NVOISINS && (voisins[i] != pointN); i++)
		{
			uint8_t& s2 = voisins[i];

			//	7       maj_distances(s1, s2)


	///			1	 si d[s2] > d[s1] + Poids(s1, s2)      // Si la distance de sdeb à s2 est plus grande que 
	///			2                                      // celle de sdeb à S1 plus celle de S1 à S2 
	///			3    alors
	///			4        d[s2] : = d[s1] + Poids(s1, s2) // On prend ce nouveau chemin qui est plus court 
	///			5        prédécesseur[s2] : = s1        // En notant par où on passe 
			uint8_t nouvelleDist = (distances[s1] + retournerDistancePoints(s1, s2));
			if (nouvelleDist < distances[s2])
			{
				distances[s2] = nouvelleDist;
				precedant[s2] = s1;
			}
		}

		//			9 fin tant que 
	}
	// reste à parcourir les précédents à partir de la fin et de les envoyer dans l'ordre inverse.
	// nous partirons de la fin, ensuite, nous les decalerons.
	// fin, depart, chemin, precedant.

	uint8_t point = fin;
	uint8_t position = MAX_LONGUEUR_CHEMIN;
	do
	{
		chemin[--position] = point;
		point = precedant[point];
	} while (chemin[position] != depart);

	for (uint8_t i = 0; i < MAX_LONGUEUR_CHEMIN; i++)
	{
		if (position < MAX_LONGUEUR_CHEMIN)
		{
			chemin[i] = chemin[position++];
		}
		else
		{
			chemin[i] = pointN;
		}
	}


	// mettre la fin du chemin en pointN.

	return distances[fin];
}

//retourne les points qui sont voisins de celui en paramètre dans un 
//tableau de 4 points passé en référence
void retournerPointsVoisins(const uint8_t& point, uint8_t(&tableau)[MAX_NVOISINS]) {

	// 0xff représantant un point non existant, tout les points on minimum 3 points voisins.
	// ff, non connectee
	// 5, 7 ou 10 : distance.
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
		break;
	case point3:
		tableau[0] = point0;
		tableau[1] = point2;
		tableau[2] = pointC;
		tableau[3] = point4;
		break;
	case point4:
		tableau[0] = point5;
		tableau[1] = point3;
		tableau[2] = pointD;
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
		break;
	case pointA:
		tableau[0] = pointH;
		tableau[1] = pointB;
		tableau[2] = point1;
		break;
	case pointB:
		tableau[0] = pointA;
		tableau[1] = pointC;
		tableau[2] = point2;
		break;
	case pointC:
		tableau[0] = point3;
		tableau[1] = pointB;
		tableau[2] = pointD;
		break;
	case pointD:
		tableau[0] = pointC;
		tableau[1] = point4;
		tableau[2] = pointE;
		break;
	case pointE:
		tableau[0] = pointF;
		tableau[1] = point5;
		tableau[2] = pointD;
		break;
	case pointF:
		tableau[0] = pointG;
		tableau[1] = point6;
		tableau[2] = pointE;
		break;
	case pointG:
		tableau[0] = pointH;
		tableau[1] = point7;
		tableau[2] = pointF;
		break;
	case pointH:
		tableau[0] = pointG;
		tableau[1] = pointA;
		tableau[2] = point8;
		break;
	}	
}

//retourne direction du robot selon les points du chemin
uint8_t retournerDirection(uint8_t(&orientation)[NPOINTS][NPOINTS], const uint8_t& premierPoint, const uint8_t& deuxiemePoint) {
	
	uint8_t direction;
	direction = orientation[premierPoint][deuxiemePoint];

	return direction;
	
}

//permet déplacement du robot selon le chemin final et le tableau contenant les chemins Dijkstra
void deplacementRobot(uint8_t(&chemin)[MAX_LONGUEUR_CHEMIN], uint8_t (&points)[Nobjectif]) {
	uint8_t i = 0;
	uint8_t compteurBebitte = 0;
	uint8_t directionActuelle, prochaineDirection;
	bool cheminComplete = false;
	bool actifs[Nobjectif] = {true, true, true, true, true};
	
	while(chemin[i+1] != pointN)
	{   //itère sur les points intermédiaires entre les points du chemin final (Dijkstra)
		prochaineDirection = retournerDirection(orientation, chemin[i], chemin[i + 1]);
		if (i == 0)
			directionActuelle = prochaineDirection;

		switch (prochaineDirection) {
			case DEVANT:
				switch (directionActuelle) {
					case DROITE:
						tournerGauche();
						break;
					case OBLIQUE_2:
						if (chemin[i - 1] == point4 && chemin[i] == pointD)
							tournerGauche();
						else if(chemin[i - 1] == pointD && chemin[i] == point4)
							tournerDroite();
						break;
					case DERRIERE:
						tourner180();
						break;
					case OBLIQUE_3:
						if (chemin[i - 1] == point6 && chemin[i] == pointF)
							tournerDroite();
						else if(chemin[i - 1] == pointF && chemin[i] == point6)
							tournerGauche();
						break;
					case GAUCHE:
						tournerDroite();
						break;
				}

				suisLigne(150);
				break;

			case OBLIQUE_1:
				if (chemin[i-1] == pointA && chemin[i] == pointB) {
					tournerGrandDroite();
				}

				else if (chemin[i - 1] == pointC && chemin[i] == pointB) {
					tournerGrandGauche();
				}

				else if (chemin[i - 1] == point1 && chemin[i] == point2) {
					tournerGauche();
				}

				else if (chemin[i - 1] == point2 && chemin[i] == pointB) {
					tourner180();
				}

				else if (chemin[i - 1] == pointB && chemin[i] == point2) {
					tourner180();
				}

				else {
					tournerDroite();
				}

				suisLigne(150);
				break;

			case DROITE:
				switch (directionActuelle) {
					case DROITE:
						if (i == 0)
							tournerDroiteDebut();
						break;
					case DERRIERE:
						tournerGauche();
						break;
					case OBLIQUE_3:
						if (chemin[i - 1] == point6 && chemin[i] == pointF)
							tournerGauche();
						else if(chemin[i - 1] == pointF && chemin[i] == point6)
							tournerDroite();
						break;
					case GAUCHE:
						tourner180();
						break;
                    case OBLIQUE_4:
						if (chemin[i - 1] == point8 && chemin[i] == pointH)
							tournerDroite();
						else if(chemin[i - 1] == pointH && chemin[i] == point8)
							tournerGauche();
						break;
				}

				if (directionActuelle != DROITE && directionActuelle != DERRIERE
				 	&& directionActuelle != GAUCHE && directionActuelle != OBLIQUE_3
				 	&& directionActuelle != OBLIQUE_4) {
					tournerDroite();
				}

				suisLigne(150);
				break;
		
			case OBLIQUE_2:
				if (chemin[i - 1] == pointC && chemin[i] == pointD) {
					tournerGrandDroite();
				}

				else if (chemin[i - 1] == pointE && chemin[i] == pointD) {
					tournerGrandGauche();
				}

				else if (chemin[i - 1] == point3 && chemin[i] == point4) {
					tournerGauche();
				}

				else if (chemin[i - 1] == point4 && chemin[i] == pointD) {
					tourner180();
				}

				else if (chemin[i - 1] == pointD && chemin[i] == point4) {
					tourner180();
				}

				else {
					tournerDroite();
				}

				suisLigne(150);
				break;
		
			case DERRIERE:
				switch (directionActuelle) {
					case DEVANT:
						tourner180();
						break;
					case OBLIQUE_1:
						if (chemin[i - 1] == point2 && chemin[i] == pointB)
							tournerDroite();
						else if(chemin[i - 1] == pointB && chemin[i] == point2)
							tournerGauche();
						break;
					case DROITE:
						tournerDroite();
						break;
					case DERRIERE:
						if(i == 0)
							tourner180Debut();
						break;
					case GAUCHE:
						tournerGauche();
						break;
					case OBLIQUE_4:
						if (chemin[i - 1] == point8 && chemin[i] == pointH)
							tournerGauche();
						else if(chemin[i - 1] == pointH && chemin[i] == point8)
							tournerDroite();
						break;
				}

				suisLigne(150);
				break;
		
			case OBLIQUE_3:
				if (chemin[i - 1] == pointE && chemin[i] == pointF) {
					tournerGrandDroite();
				}

				else if (chemin[i - 1] == pointG && chemin[i] == pointF) {
					tournerGrandGauche();
				}

				else if (chemin[i - 1] == point5 && chemin[i] == point6) {
					tournerGauche();
				}

				else if (chemin[i - 1] == point6 && chemin[i] == pointF) {
					tourner180();
				}

				else if (chemin[i - 1] == pointF && chemin[i] == point6) {
					tourner180();
				}

				else {
					tournerDroite();
				}

				suisLigne(150);
				break;
		
			case GAUCHE:
				switch (directionActuelle) {
					case OBLIQUE_1:
						if (chemin[i - 1] == point2 && chemin[i] == pointB)
							tournerGauche();
						else if(chemin[i - 1] == pointB && chemin[i] == point2)
							tournerDroite();
						break;
					case DROITE:
						tourner180();
						break;
					case OBLIQUE_2:
						if (chemin[i - 1] == point4 && chemin[i] == pointD)
							tournerDroite();
						else if(chemin[i - 1] == pointD && chemin[i] == point4)
							tournerGauche();
						break;
					case DERRIERE:
						tournerDroite();
						break;
					case GAUCHE:
						if (i == 0) 
							tournerGaucheDebut();
						break;
				}

				if (directionActuelle != GAUCHE && directionActuelle != DERRIERE 
					&& directionActuelle != DROITE && directionActuelle != OBLIQUE_2
					&& directionActuelle != OBLIQUE_1) {
					tournerGauche();
				}

				suisLigne(150);
				break;
		
			case OBLIQUE_4:
				if (chemin[i - 1] == pointG && chemin[i] == pointH) {
					tournerGrandDroite();
				}

				else if (chemin[i - 1] == pointA && chemin[i] == pointH) {
					tournerGrandGauche();
				}

				else if (chemin[i - 1] == point7 && chemin[i] == point8) {
					tournerGauche();
				}

				else if (chemin[i - 1] == point8 && chemin[i] == pointH) {
					tourner180();
				}

				else if (chemin[i - 1] == pointH && chemin[i] == point8) {
					tourner180();
				}

				else {
					tournerDroite();
				}

				suisLigne(150);
				break;
		
		}
		directionActuelle = prochaineDirection;
		i++;

		for(uint8_t j = 0; j < nrobjectif; j++){
			if(chemin[i] == points[j] && actifs[j] == true){
				mangerBebitte(chemin[i]);
				actifs[j] = false;
				compteurBebitte++;
			}
		}
		
		if(compteurBebitte == nrobjectif && !cheminComplete){
			cheminComplete = true;
			pause();
			setup();
		}
		
	} 
    
    if( nrobjectif == 0){
        pause();
        setup();
    }
	arret();
}

//retourne distance entre deux points
uint8_t retournerDistancePoints(const uint8_t& premierPoint, const uint8_t& deuxiemePoint) {
	if (premierPoint == deuxiemePoint) return 0;
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
		if (deuxiemePoint == point2 || deuxiemePoint == pointC || deuxiemePoint == point4 || deuxiemePoint == point0)
			return 5;
		break;
	case point4:
		if (deuxiemePoint == point3 || deuxiemePoint == point5)
			return 5;
		else if (deuxiemePoint == pointD)
			return 7;
		break;
	case point5:
		if (deuxiemePoint == point4 || deuxiemePoint == point6 || deuxiemePoint == pointE || deuxiemePoint == point0)
			return 5;
		break;
	case point6:
		if (deuxiemePoint == point5 || deuxiemePoint == point7)
			return 5;
		else if (deuxiemePoint == pointF)
			return 7;
		break;
	case point7:
		if (deuxiemePoint == point6 || deuxiemePoint == point8 || deuxiemePoint == pointG || deuxiemePoint == point0)
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
	return pointN;
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
	uint8_t(&chemin)[MAX_LONGUEUR_CHEMIN])
{

	//initialisation

	for (uint8_t i = 0; i < Nobjectif; i++)
		for (uint8_t j = 0; j < Nobjectif; j++)
			distances[i][j] = 0x0;
	

	//pour chaque relation entre les points
	for (uint8_t i = 0; i < (Nobjectif - 1); i++)
	{
		//appliquer algoDijsktra pour obtenir le chemin et la distance.
		// nous avons un tableau de distances et un tableau de chemin entre chaque point.
		for (uint8_t j = i + 1; j < Nobjectif; j++)
		{
			//initialisation
			for (uint8_t k = 0; k < MAX_LONGUEUR_CHEMIN; k++)
				chemin[k] = pointN;


			distances[i][j] = algoDijsktra(points[i], points[j], chemin);
			distances[j][i] = distances[i][j];

		}

	}
	//les distances et les chemin ont tout été mis à jour
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

		//verifier si point existe
		if (points[i] == pointN)
		{
			distancesTotales[i] = 0xff;
			for (uint8_t j = 0; j < Nobjectif; j++)
				chemins[i][j] = pointN;
		}
		else
		{
			//mettre tout les points actifs
			for (uint8_t n = 0; n < nrobjectif; n++) actif[n] = true;
			chemins[i][0] = i; //chemin de depart au premier point
			actif[i] = false; // ce point devient inactif
			distancesTotales[i] = 0;

			//ajouter le point le plus pret, pour tout les points
			for (uint8_t j = 0; j < (nrobjectif - 1); j++)
			{
				//trouver le point le plus pret
				uint8_t k = 0;
				uint8_t prochain = pointN;
				while (k < nrobjectif)
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

	}
	//voyons maintenant avec les fins. 
	for (uint8_t i = 0; i < nrobjectif; i++)
	{
		uint8_t pointFin = chemins[i][nrobjectif - 1];
		if (distancesTotales[i] < distancesTotales[pointFin])
		{
			for (uint8_t j = 0; j < nrobjectif; j++)
			{
				chemins[pointFin][j] = chemins[i][nrobjectif - 1 - j];
			}
		}
	}
	//mainenant, nous avons les chemins a partir d'un objectif pour aller
	//aux autres et la distance totale
}

//Fonction pour trouver les objectifs au depart
void analyseObjectifs(uint8_t(&points)[Nobjectif]){
	
	uint8_t compteurBebitte = 0;
    uint8_t quadran = 0;
    rotationStationnaire();
    bool maxValeur = false;
    uint8_t lastValue = 0;
    uint8_t newValue = 0;
    
    //Le robot tourne tant qu'il n'a pas fait un tour complet
    while(quadran < 8) {
        
        //Le robot poll seulement s'il a trouvé moins de 5 insectes ou s'il n'a pas encore trouvé d'insecte dans un quadran donné
        if(!maxValeur && compteurBebitte < Nobjectif){
            
            //Détermine s'il doit lire avec les distances diagonales ou perpendiculaires
            if(quadran%2 == 0)
                newValue = positionPerp();
            else
                newValue = positionDiag();

            //Si la valeur lue correspond a un objet proche
            if(newValue == 2){
                
                //Antirebond
                _delay_ms(5);
				if(quadran%2 == 0)
					newValue = positionPerp();
				else
					newValue = positionDiag();
                
                //Reverification, si l'objet est encore lu, placer un objet a l'endroit approprie
                if(newValue == 2){
                    maxValeur = true;
                    arret();
                    placerObjet(quadran, newValue, points, compteurBebitte);
                    lastValue = 0;
                    rotationStationnaire();
                    _delay_ms(500);
                }
                
            }
            
            
            //Si l'ancienne valeur de lecture est plus petite que la courante
            if(newValue > lastValue){
                
                //Antirebond pour ne pas effectuer de fausse lecture
                _delay_ms(5);
                if(quadran%2 == 0)
                    newValue = positionPerp();
                else
                    newValue = positionDiag();
                
                //Enregistre la valeur courante comme ancienne valeur pour le prochain polling
                if(newValue > lastValue)
                    lastValue = newValue;
                
            }

            //Si l'ancienne valeur de lecture est plus grande que la courante
            else if(newValue < lastValue){
                
                //Antirebond pour ne pas effectuer de fausse lecture
                _delay_ms(5);
                if(quadran%2 == 0)
                    newValue = positionPerp();
                else
                    newValue = positionDiag();
                
                //Si l'objet n'est plus detecte, donc la nouvelle valeur est plus petite que l'ancienne, placer un objet loin dans le quadran approprie
                if(newValue < lastValue){
                    maxValeur = true;
                    arret();
                    placerObjet(quadran, lastValue, points, compteurBebitte);
                    lastValue = 0;
                    reajustementStationnaire();
                    rotationStationnaire();
                    _delay_ms(500);
                }
            }
        
        }
        
        //Passage d'un quadran perpendiculaire a diagonal
        if(aucunCapteur() && !(quadran%2)){
                quadran++;
                maxValeur = false;
                lastValue = 0;
        }
        
        //Passage d'un quadran diagonal a perpendiculaire
        if(capteurDroite2() && quadran%2){
                quadran++;
                maxValeur = false;
                lastValue = 0;
        }
        
    }
    
    //Donner le nombre d'objets reels trouves et reajustement pour etre droit avec la ligne
    nrobjectif = compteurBebitte;
    _delay_ms(300);
    arret();
    reajustementStationnaire();
                
}

//Methode qui place les objectifs aux bons endroits dans la map avec le quadran et la distance recues
void placerObjet(uint8_t quadran, uint8_t distance, uint8_t(&points)[Nobjectif], uint8_t 
&compteurBebitte){
    switch(quadran){
        case 0:
            if(distance == 1){
                insecteLoinTrouve();
                points[compteurBebitte] = pointA;
            }
            else if(distance == 2){
                insecteProcheTrouve();
                points[compteurBebitte] = point1;
            }
            break;
        case 1:
            if(distance == 1){
                insecteLoinTrouve();
                points[compteurBebitte] = pointB;
            }
            else if(distance == 2){
                insecteProcheTrouve();
                points[compteurBebitte] = point2;
            }
            break;
        case 2:
            if(distance == 1){
                insecteLoinTrouve();
                points[compteurBebitte] = pointC;
            }
            else if(distance == 2){
                insecteProcheTrouve();
                points[compteurBebitte] = point3;
            }
            break;
        case 3:
            if(distance == 1){
                insecteLoinTrouve();
                points[compteurBebitte] = pointD;
            }
            else if(distance == 2){
                insecteProcheTrouve();
                points[compteurBebitte] = point4;
            }
            break;
        case 4:
            if(distance == 1){
                insecteLoinTrouve();
                points[compteurBebitte] = pointE;
            }
            else if(distance == 2){
                insecteProcheTrouve();
                points[compteurBebitte] = point5;
            }
            break;
        case 5:
            if(distance == 1){
                insecteLoinTrouve();
                points[compteurBebitte] = pointF;
            }
            else if(distance == 2){
                insecteProcheTrouve();
                points[compteurBebitte] = point6;
            }
            break;
        case 6:
            if(distance == 1){
                insecteLoinTrouve();
                points[compteurBebitte] = pointG;
            }
            else if(distance == 2){
                insecteProcheTrouve();
                points[compteurBebitte] = point7;
            }
            break;
        case 7:
            if(distance == 1){
                insecteLoinTrouve();
                points[compteurBebitte] = pointH;
            }
            else if(distance == 2){
                insecteProcheTrouve();
                points[compteurBebitte] = point8;
            }
            break;
    }
    compteurBebitte++;
}


// fonction qui trouve le chemin pour passer sur les 5 points. 
// retourne la distance total du chemin.
// dans les chemin, le premier point est toujours le point ou on se trouve.
//
//	exemplel d'utilisation:
//
//	uint8_t points[Nobjectif] = { pointH, pointB, pointD, pointF, point5};
//	uint8_t chemin[MAX_LONGUEUR_CHEMIN];
//	uint8_t distanceTotale = trouverChemin(points, chemin);
//
uint8_t trouverChemin(uint8_t(&objectifs)[Nobjectif], uint8_t(&chemin)[MAX_LONGUEUR_CHEMIN])
{
	if (nrobjectif == 0)
	{
		chemin[0] = point0; chemin[1] = point1; chemin[2] = pointA; chemin[3] = pointN;
		return 10;
	}
	//pour chaque relation entre les points, trouver meilleur chemin et distance
	uint8_t distancesEntreObjectifs[Nobjectif][Nobjectif];
	uint8_t cheminFictif[MAX_LONGUEUR_CHEMIN];

	simplifier(distancesEntreObjectifs, objectifs, cheminFictif); //rempli le tableau de distances entre nos points.

	uint8_t distancesFictive[Nobjectif];

	//trouver de chaque point, la distance et le meilleur chemin pour aller a tout les prochains points.

	uint8_t cheminsGeneralFictif[Nobjectif][Nobjectif]; //chemin entre objectifs

	nearest_neighbor(distancesEntreObjectifs, objectifs, cheminsGeneralFictif, distancesFictive);
	//determiner chemin du point de depart a la sortie fictive qui inclut tout de passer par tout les points.

	//appliquer Dijkstra's du point de depart sur chaque point. et determiner le bon chemin
	uint8_t cheminFinal[MAX_LONGUEUR_CHEMIN];
	uint8_t distancesFinales[Nobjectif];
	uint8_t laBonne = 0;
	for (uint8_t i = 0; i < Nobjectif; i++)
	{
		//ca chie dans l'algo ici
		distancesFinales[i] = algoDijsktra(point0, objectifs[i], cheminFinal) + distancesFictive[i];
		if (i != 0 && distancesFinales[i] < distancesFinales[laBonne]) laBonne = i;
	}

	algoDijsktra(point0, objectifs[laBonne], cheminFinal);


	//retourner ce chemin.
	uint8_t i = 0;

	while (cheminFinal[i] != pointN)
	{
		chemin[i] = cheminFinal[i];
		i++;
	}

	for (uint8_t j = 0; j < (nrobjectif - 1); j++)
	{
		uint8_t pointPresent = objectifs[cheminsGeneralFictif[laBonne][j]];
		uint8_t next = objectifs[cheminsGeneralFictif[laBonne][j + 1]];
		uint8_t k = 1;
		algoDijsktra(pointPresent, next, cheminFictif);
		while (cheminFictif[k] != pointN)
		{
			chemin[i] = cheminFictif[k];
			i++;
			k++;
		}

	}

	//trouver chemin vers la sortie la plus proche : 

	const uint8_t nSorties = 4; //nb de sorties
	const uint8_t sorties[nSorties] = { point1, point3, point5, point7 };
	uint8_t distancesASorties[nSorties];
	uint8_t cheminsASorties[nSorties][MAX_LONGUEUR_CHEMIN];
	uint8_t bonneSortie = 0;
	for (uint8_t j = 0; j < nSorties; j++)
	{
		distancesASorties[j] = algoDijsktra(chemin[i - 1], sorties[j], cheminsASorties[j]);
		if (j != 0 && distancesASorties[j] < distancesASorties[bonneSortie])
			bonneSortie = j;

	}
	uint8_t apresSortie;
	switch (sorties[bonneSortie]) {
	case point1:
		apresSortie = pointA;
		break;
	case point3:
		apresSortie = pointC;
		break;
	case point5:
		apresSortie = pointE;
		break;
	case point7:
		apresSortie = pointG;
		break;
	}
	
	uint8_t k = 1;
	while (cheminsASorties[bonneSortie][k] != pointN)
	{
		chemin[i] = cheminsASorties[bonneSortie][k];
		i++;
		k++;
	}
	chemin[i] = apresSortie; i++;



	while (i < MAX_LONGUEUR_CHEMIN)
	{
		chemin[i] = pointN;
		i++;
	}
	return (distancesFinales[laBonne] + distancesASorties[bonneSortie] + 5);
}

