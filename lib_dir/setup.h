#ifndef SETUP_H
#define SETUP_H

#include "constantes.h"

//setup pour le robot en mouvement
void setup();

//routine de démarrage
void demarrage();

//setup pour le robot en attente
void setupInterruption();

//fonction qui met le robot temporairement en attente 
void pause();

#endif //SETUP_H
