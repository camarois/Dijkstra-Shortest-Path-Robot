/****************************************************************************
* Fichier: projet.cpp
* Auteur: Charles Marois, François-Xavier Legault, Jacob Dorais et Jean-Sébastien Boulianne
* Date: 5 decembre 2017
* Description: Contient la fonction main de notre programme
****************************************************************************/

#include <constantes.h>

#define DEMO_DDR DDRC // `Data Direction Register' AVR occupé par l'aff.
#define DEMO_PORT PORTC // Port AVR occupé par l'afficheur

/*******************************************************************************
* Fonction: main
* Description: Fonction principale, qui appelle toutes les autres fonctions pour que 
*				le robot détecte et se rend aux objectifs, puis trouve la bonne sortie.
* Paramètres: aucun
*******************************************************************************/
int main(){
    //Attente d'appuis sur le bouton pour commencer
	pause();
	setup();
	demarrage();

    
	uint8_t chemin[MAX_LONGUEUR_CHEMIN];
	uint8_t points[Nobjectif]  = {pointN, pointN, pointN, pointN, pointN};
	
	analyseObjectifs(points);
    
    _delay_ms(50);
    uint8_t distanceTotale = trouverChemin(points, chemin);
    _delay_ms(1000);
    
    pause();
    setup();
    
    deplacementRobot(chemin, points);
 	
    pause();
    setup();
    
 	suisLigneFin(150);
    lireMusique();
    afficherVert();
 	
 	for(;;);
}
