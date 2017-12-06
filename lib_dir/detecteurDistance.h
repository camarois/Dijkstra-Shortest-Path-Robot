#ifndef DETECTEURDISTANCE_H
#define DETECTEURDISTANCE_H

#include "constantes.h"

//Methodes pour trouver un instecte et s'il est proche ou loin
bool insecteDetecte();
bool isInsecteProche();

//Methodes pour signaler qu'un instecte a ete trouve
void insecteLoinTrouve();
void insecteProcheTrouve();

//Fonction qui retourne 0, 1 ou 2 dependamment de la distance de l'objet trouve
int positionPerp();
int positionDiag();

#endif
