/****************************************************************************
* Fichier: detecteurLigne.cpp
* Auteur: Charles Marois, Fran�ois-Xavier Legault, Jacob Dorais et Jean-S�bastien Boulianne
* Date: 5 decembre 2017
* Description: Impl�mentation des fonctions pour le detecteur de ligne Cytron
****************************************************************************/

#include "detecteurLigne.h"

/*******************************************************************************
* Fonction: capteurMilieu
* Description: Fonction retournant true si le capteur du milieu d�tecte quelque chose
* Param�tres: aucun
* Retour: bool : indiquant la sortie du capteur du milieu
*******************************************************************************/
bool capteurMilieu(){
	return (PINC & M);
}

/*******************************************************************************
* Fonction: capteurGauche1
* Description: Fonction retournant true si le capteur gauche1 d�tecte quelque chose
* Param�tres: aucun
* Retour: bool : indiquant la sortie du capteur gauche1
*******************************************************************************/
bool capteurGauche1(){
	return (PINC & L1);
}

/*******************************************************************************
* Fonction: capteurDroite1
* Description: Fonction retournant true si le capteur droite1 d�tecte quelque chose
* Param�tres: aucun
* Retour: bool : indiquant la sortie du capteur droite1
*******************************************************************************/
bool capteurDroite1(){
	return (PINC & R1);
}

/*******************************************************************************
* Fonction: capteurGauche2
* Description: Fonction retournant true si le capteur gauche2 d�tecte quelque chose
* Param�tres: aucun
* Retour: bool : indiquant la sortie du capteur gauche2
*******************************************************************************/
bool capteurGauche2(){
	return (PINC & L2);
}

/*******************************************************************************
* Fonction: capteurDroite2
* Description: Fonction retournant true si le capteur droite2 d�tecte quelque chose
* Param�tres: aucun
* Retour: bool : indiquant la sortie du capteur droite2
*******************************************************************************/
bool capteurDroite2(){
	return (PINC & R2);
}

/*******************************************************************************
* Fonction: aucunCapteur
* Description: Fonction retournant true si tout les capteurs ne d�tectent rien
* Param�tres: aucun
* Retour: bool : indiquant si tout les capteurs ne d�tectent rien
*******************************************************************************/
bool aucunCapteur(){
	return (!capteurMilieu()  &&
			!capteurDroite1() &&
			!capteurDroite2() &&
			!capteurGauche1() &&
			!capteurGauche2()	);
}

/*******************************************************************************
* Fonction: suisLigne
* Description: Fonction permettant de changer la puissance des moteurs afin que le robot suive une ligne
* Param�tres: (uint8_t) speed : la puissance voulue donn� au PWM des moteurs
* Retour: aucun
*******************************************************************************/
void suisLigne(uint8_t speed){
	PORTD |= (1 << 2);
	PORTD |= (1 << 3);
	_delay_ms(1000);
	
	kickstart(speed);
	_delay_ms(400);
	
	bool coinTrouve = false;
	
	do{														//tant qu'aucune intersection n'a �t� trouv�e, on suit une ligne
		if ( capteurMilieu()  &&
			!capteurDroite1() &&
			!capteurDroite2() &&
			!capteurGauche1() &&
			!capteurGauche2() ){							//Si seulement le capteur milieu d�tecte quelque chose
				ajustementPWM(speed, speed);				//on avance tout droit
				continue;
		}
		
		else if (capteurMilieu()  &&
				!capteurDroite1() &&
				!capteurDroite2() &&
				 capteurGauche1() &&
				!capteurGauche2() ){						//Si le capteur milieu et gauche1 d�tectent quelque chose
					ajustementPWM(speed, 0.75 * speed);		//on avance en tournant un peu � gauche
					continue;
		}
		
		else if (capteurMilieu()  &&
				 capteurDroite1() &&
				!capteurDroite2() &&
				 capteurGauche1() &&
				!capteurGauche2()){							//Si le capteur milieu, droite1 et gauche1 d�tectent quelque chose
					ajustementPWM(speed, speed);			//on avance tout droit
					continue;
		}
		
		else if (capteurMilieu()  &&
				 capteurDroite1() &&
				!capteurDroite2() &&
				!capteurGauche1() &&
				!capteurGauche2() ){						//Si le capteur milieu et droite1 d�tectent quelque chose
					ajustementPWM(0.75 * speed, speed);		//on avance en tournant un peu � droite
					continue;
		}
		
		else if (!capteurMilieu() && 
				 capteurDroite1() &&
				!capteurDroite2() &&
				!capteurGauche1() &&
				!capteurGauche2() ){						//Si seulement le capteur droite1 d�tecte quelque chose
					ajustementPWM(0.6 * speed, speed);		//on avance en tournant vers la droite
					continue;
		}
		
		else if (!capteurMilieu()  && 
				 capteurDroite1() &&	
				 capteurDroite2() &&	
				!capteurGauche1() &&
				!capteurGauche2() ){						//Si le capteur droite1 et droite2 d�tectent quelque chose
					ajustementPWM(0.5 * speed, speed);		//on avance en tournant vers la droite
					continue;
		}
		
		else if (!capteurMilieu()  && 
				 !capteurDroite1() &&
				 !capteurDroite2() &&
				 capteurGauche1() &&
				 !capteurGauche2() ){						//Si seulement le capteur gauche1 d�tecte quelque chose
					ajustementPWM(speed, 0.6 * speed);		//on avance en tournant vers la gauche
					continue;
		}
		
		else if (!capteurMilieu()  && 
				 !capteurDroite1() &&
				 !capteurDroite2() &&
				  capteurGauche1() &&
				  capteurGauche2() ){						//Si le capteur gauche1 et gauche2 d�tectent quelque chose
					ajustementPWM(speed, 0.5 * speed);		//on avance en tournant vers la gauche
					continue;
		}
		
		else if (!capteurMilieu()  && 
				 !capteurDroite1() &&
				 capteurDroite2() &&
				 !capteurGauche1() &&
				 !capteurGauche2() ){						//Si seulement le capteur droite2 d�tecte quelque chose
					ajustementPWM(0.25 * speed, speed);		//on avance en tournant grandement vers la droite
					continue;
		}
		
		else if (!capteurMilieu()  && 
				 !capteurDroite1() &&
				 !capteurDroite2() &&
				 !capteurGauche1() &&
				 capteurGauche2() ){						//Si seulement le capteur gauche2 d�tecte quelque chose
					ajustementPWM(speed, 0.25 * speed);		//on avance en tournant grandement vers la gauche
					continue;
		}
		

		/*
			Les prochains cas sont si le robot est � une intersection.
			Donc, plusieurs capteurs d�tectent quelque chose en m�me temps
			On effectue aussi une double v�rification pour chacun des cas apr�s 
			un cours d�lai
		*/
		else if (capteurMilieu()  && 			//milieu
				 capteurDroite1() &&			//et droite1
				 capteurDroite2() &&			//et droite2
				 capteurGauche1() &&			//et gauche1
				 capteurGauche2() ){			//et gauche2
                     _delay_ms(2);
                     if (capteurMilieu()  && 	//milieu
                        capteurDroite1() &&		//et droite1
                        capteurDroite2() &&		//et droite2
                        capteurGauche1() &&		//et gauche1
                        capteurGauche2() ){		//et gauche2
                            coinTrouve = true;
                            arret();
                     }
		}
		
        else if (capteurMilieu()  && 			//milieu
				 !capteurDroite1() &&
				 capteurDroite2() &&			//et droite2
				 !capteurGauche1() &&
				 capteurGauche2() ){			//et gauche2
                     _delay_ms(2);
                     if (capteurMilieu()  && 	//milieu
                        !capteurDroite1() &&
                        capteurDroite2() &&		//et droite2
                        !capteurGauche1() &&
                        capteurGauche2() ){		//et gauche2
                            coinTrouve = true;
                            arret();
                     }
		}
		
		else if ( capteurMilieu()  && 			//milieu
				  capteurDroite1() &&			//droite1
				  capteurDroite2() &&			//droite2
				  capteurGauche1() &&			//gauche1
				 !capteurGauche2() ){
                     _delay_ms(2);
                     if (capteurMilieu()  && 	//milieu
                        capteurDroite1() &&		//droite1
                        capteurDroite2() &&		//droite2
                        capteurGauche1() &&		//gauche1
                        !capteurGauche2() ){
                            coinTrouve = true;
                            arret();
                     }
		}
		
		else if ( capteurMilieu()  && 			//milieu
				  capteurDroite1() &&			//droite1
				 !capteurDroite2() &&
				  capteurGauche1() &&			//gauche1
				  capteurGauche2() ){			//gauche2
                     _delay_ms(2);
                     if (capteurMilieu()  && 	//milieu
                        capteurDroite1() &&		//droite1
                        !capteurDroite2() &&
                        capteurGauche1() &&		//gauche1
                        capteurGauche2() ){		//gauche2
                            coinTrouve = true;
                            arret();
                     }
		}
		
        else if (capteurMilieu()  &&			//milieu
				!capteurDroite1() &&	
				!capteurDroite2() &&	
				 capteurGauche1() &&			//et gauche1
				 capteurGauche2()){				//et gauche2
                     _delay_ms(2);
                     if (capteurMilieu()  && 	//milieu
                        !capteurDroite1() &&
                        !capteurDroite2() &&
                        capteurGauche1() &&		//gauche1
                        capteurGauche2() ){		//gauche2
                            coinTrouve = true;
                            arret();
                     }
		}
		
		else if (capteurMilieu()  &&			//milieu
				 capteurDroite1() &&			//et droite1
				 capteurDroite2() &&			//et droite2
				!capteurGauche1() &&
				!capteurGauche2()){
                     _delay_ms(2);
                     if (capteurMilieu()  && 	//milieu
                        capteurDroite1() &&		//droite1
                        capteurDroite2() &&		//droite2
                        !capteurGauche1() &&
                        !capteurGauche2() ){
                            coinTrouve = true;
                            arret();
                     }
		}
		
		else if (aucunCapteur()){		//Si aucuns des capteurs d�tectent quelque chose
            ajustementPWM(150,150);		//on avance un peu et on rev�rifie
			_delay_ms(1);
			if (aucunCapteur()){
				arret();				//si c'est toujours le cas, on s'arr�te
				return;
			}
        }
		
		else {			
            kickstart(150);
            arret();
			continue;
		}
	}while(!coinTrouve);				//tant qu'aucune intersection n'a �t� trouv�e, on continue la boucle
	arret();
}


/*******************************************************************************
* Fonction: suisLigneFin
* Description: Fonction permettant de changer la puissance des moteurs afin que le robot suive une ligne,
*				puis doit d�duire la bonne sortie et s'y diriger
* Param�tres: (uint8_t) speed : la puissance voulue donn� au PWM des moteurs
* Retour: aucun
*******************************************************************************/
void suisLigneFin(uint8_t speed) {
	PORTD |= (1 << 2);
	PORTD |= (1 << 3);

	_delay_ms(1000);
	
	kickstart(speed);
	_delay_ms(400);

	int compteur = 0;

	bool finGTrouve = false;
	bool finATrouve = false;
	bool finCTrouve = false;
	bool finETrouve = false;

	while (!finATrouve && !finCTrouve && !finETrouve && !finGTrouve) {	//tant qu'aucune sortie n'a �t� trouv�e, on suit une ligne

		//on incr�mente le compteur, cela va nous servir � savoir si on est � la sortie E ou A,
		//puisque la seule diff�rence entre ceux-ci est leur longueur.
		compteur++;

		/*
			La proc�dure suivante est pratiquement identique � la fonction suisLigne, 
			sauf que l'on cherche une sortie et non une intersection.
		*/
		if (capteurMilieu() &&		//milieu
			!capteurDroite1() &&
			!capteurDroite2() &&
			!capteurGauche1() &&
			!capteurGauche2()) {
                ajustementPWM(speed, speed);
                continue;
		}

		else if (capteurMilieu() &&	//milieu
			!capteurDroite1() &&
			!capteurDroite2() &&
			capteurGauche1() &&		//et gauche1
			!capteurGauche2()) {
                ajustementPWM(speed, 0.75 * speed);
                continue;
		}

		else if (capteurMilieu() &&	//milieu
			capteurDroite1() &&		//et droite1
			!capteurDroite2() &&
			capteurGauche1() &&		//et gauche1
			!capteurGauche2()) {
                ajustementPWM(speed, speed);
                continue;
		}

		else if (capteurMilieu() &&	 //milieu
			!capteurDroite1() &&
			!capteurDroite2() &&
			capteurGauche1() &&		//et gauche1
			capteurGauche2()) {		//et gauche2
                ajustementPWM(speed, 0.5 * speed);
                continue;
		}

		else if (capteurMilieu() &&	//milieu
			capteurDroite1() &&		//et droite1
			!capteurDroite2() &&
			!capteurGauche1() &&
			!capteurGauche2()) {
                ajustementPWM(0.75 * speed, speed);
                continue;
		}

		else if (!capteurMilieu() &&
			capteurDroite1() &&		//droite1
			!capteurDroite2() &&
			!capteurGauche1() &&
			!capteurGauche2()) {
                ajustementPWM(0.6 * speed, speed);
                continue;
		}

		else if (!capteurMilieu() &&
			capteurDroite1() &&		//droite1
			capteurDroite2() &&		//et droite2
			!capteurGauche1() &&
			!capteurGauche2()) {
                ajustementPWM(0.5 * speed, speed);
                continue;
		}

		else if (!capteurMilieu() &&
			!capteurDroite1() &&
			!capteurDroite2() &&
			capteurGauche1() &&		//gauche1
			!capteurGauche2()) {
                ajustementPWM(speed, 0.6 * speed);
                continue;
		}

		else if (!capteurMilieu() &&
			!capteurDroite1() &&
			!capteurDroite2() &&
			capteurGauche1() &&		//gauche1
			capteurGauche2()) {		//et gauche2
                ajustementPWM(speed, 0.5 * speed);
                continue;
		}

		else if (!capteurMilieu() &&
			!capteurDroite1() &&
			capteurDroite2() &&		//droite2
			!capteurGauche1() &&
			!capteurGauche2()) {
                ajustementPWM(0.25 * speed, speed);
                continue;
		}

		else if (!capteurMilieu() &&
			!capteurDroite1() &&
			!capteurDroite2() &&
			!capteurGauche1() &&
			capteurGauche2()) {		//gauche2
                ajustementPWM(speed, 0.25 * speed);
                continue;
		}

        else if (capteurMilieu() && //milieu
			capteurDroite1() &&		//droite1
			capteurDroite2() &&		//droite2
			capteurGauche1() &&		//gauche1
			capteurGauche2()) {		//gauche2
                finCTrouve = true;
                break;
		}
		
		else if (capteurMilieu() &&	//milieu
			capteurDroite1() &&		//et droite1
			capteurDroite2() &&		//et droite2
			!capteurGauche1() &&
			!capteurGauche2()) {
                finGTrouve = true;
                break;
		}
		
		else if (!capteurMilieu() &&	
			capteurDroite1() &&		//et droite1
			capteurDroite2() &&		//et droite2
			!capteurGauche1() &&
			!capteurGauche2()) {
                finGTrouve = true;
                break;
		}		
		
        else if (capteurMilieu() &&	//milieu
			capteurDroite1() &&		//et droite1
			capteurDroite2() &&		//et droite2
			capteurGauche1() &&	 //et gauche1
			!capteurGauche2()) {
                finGTrouve = true;
                break;
		}

		else {		//aucun
			ajustementPWM(150, 150);
			_delay_ms(100);
			if (aucunCapteur()) {
				if (compteur < 2000) {
					finATrouve = true;
					continue;
				}
				else {	
					finETrouve = true;
					continue;
				}
			}
		}
	}
	
	arret();
	
	_delay_ms(1000);

	/*
		D�pendamment de quelle sortie on se trouve pr�sentement,
		on effectue un parcours pour se rendre vers la bonne (E).
		Si on est d�ja � la sortie E, on quitte tout simplement la
		fonction.
	*/
	if (finATrouve) {
		tourner180();
		suisLigne(150);
		suisLigne(150);
		suisLigne(150);
		suisLigne(150);
		suisLigne(150);
		suisLigne(150);
		return;
	}

	else if (finCTrouve) {
		
		tourner180();
		suisLigne(150);
		suisLigne(150);
		tournerGauche();
		suisLigne(150); 
		suisLigne(150); 
		suisLigne(150);		
		return;
	}

	else if(finETrouve){
		return;
	}

	else if (finGTrouve) {
		tourner180();
		suisLigne(150);
		suisLigne(150);
		tournerDroite();
		suisLigne(150);
		suisLigne(150);
		suisLigne(150);
		return;
	}
}

/*******************************************************************************
* Fonction: tournerDroite
* Description: Fonction permettant de changer la puissance des moteurs afin de tourner � droite
* Param�tres: aucun
* Retour: aucun
*******************************************************************************/
void tournerDroite(){
	skipCoin();
	PORTD |= (1 << 2);
	PORTD &= ~(1 << 3);
	bool ligneTrouvee = false;
	
	kickstart(120);
	_delay_ms(300);
	do{
		if (capteurDroite2()||capteurDroite1()){
			ligneTrouvee = true;
		}
	}while(!ligneTrouvee);
    _delay_ms(150);
	arret();
}

/*******************************************************************************
* Fonction: tournerDroiteDebut
* Description: Fonction permettant de changer la puissance des moteurs afin de tourner � droite,
*				mais cette fois, on se trouve au d�but et on ne veut pas avancer avant de tourner.
* Param�tres: aucun
* Retour: aucun
*******************************************************************************/
void tournerDroiteDebut(){
	PORTD |= (1 << 2);
	PORTD &= ~(1 << 3);
	bool ligneTrouvee = false;
	
	kickstart(120);
	_delay_ms(300);
	do{
		if (capteurDroite2()||capteurDroite1()){
			ligneTrouvee = true;
		}
	}while(!ligneTrouvee);
    _delay_ms(150);
	arret();
}

/*******************************************************************************
* Fonction: tournerGauche
* Description: Fonction permettant de changer la puissance des moteurs afin de tourner � gauche
* Param�tres: aucun
* Retour: aucun
*******************************************************************************/
void tournerGauche(){
	skipCoin();
	PORTD |= (1 << 3);
	PORTD &= ~(1 << 2);
	bool ligneTrouvee = false;
	
	kickstart(120);
	_delay_ms(300);
	do{
		if (capteurGauche2()||capteurGauche1()) {
			ligneTrouvee = true;
		}
	}while(!ligneTrouvee);
    _delay_ms(150);
	arret();
}

/*******************************************************************************
* Fonction: tournerGaucheDebut
* Description: Fonction permettant de changer la puissance des moteurs afin de tourner � gauche,
*				mais cette fois, on se trouve au d�but et on ne veut pas avancer avant de tourner.
* Param�tres: aucun
* Retour: aucun
*******************************************************************************/
void tournerGaucheDebut(){
	PORTD |= (1 << 3);
	PORTD &= ~(1 << 2);
	bool ligneTrouvee = false;
	
	kickstart(120);
	_delay_ms(300);
	do{
		if (capteurGauche2()||capteurGauche1()) {
			ligneTrouvee = true;
		}
	}while(!ligneTrouvee);
	arret();
}

/*******************************************************************************
* Fonction: tournerGrandDroite
* Description: Fonction permettant de changer la puissance des moteurs afin de tourner � droite,
*				mais cette fois, on veux continuer � tourner apr�s avoir passer par-dessus une ligne.
* Param�tres: aucun
* Retour: aucun
*******************************************************************************/
void tournerGrandDroite(){
	skipCoin();
	PORTD |= (1 << 2);
	PORTD &= ~(1 << 3);
	bool ligneTrouvee = false;
	
	kickstart(120);
	_delay_ms(300);
	do{
		if (capteurDroite2()||capteurDroite1()){
			ligneTrouvee = true;
		}
	}while(!ligneTrouvee);
	arret();
    
    ligneTrouvee = false;
	
	kickstart(120);
	_delay_ms(300);
	do{
		if (capteurDroite2()||capteurDroite1()){
			ligneTrouvee = true;
		}
	}while(!ligneTrouvee);
	_delay_ms(150);
    arret();
}

/*******************************************************************************
* Fonction: tournerGrandDroite
* Description: Fonction permettant de changer la puissance des moteurs afin de tourner � gauche,
*				mais cette fois, on veux continuer � tourner apr�s avoir passer par-dessus une ligne.
* Param�tres: aucun
* Retour: aucun
*******************************************************************************/
void tournerGrandGauche(){
	skipCoin();
	PORTD |= (1 << 3);
	PORTD &= ~(1 << 2);
	bool ligneTrouvee = false;
	
	kickstart(120);
	_delay_ms(300);
	do{
		if (capteurGauche2()||capteurGauche1()) {
			ligneTrouvee = true;
		}
	}while(!ligneTrouvee);
	arret();
    
    ligneTrouvee = false;
	
	kickstart(120);
	_delay_ms(300);
	do{
		if (capteurGauche2()||capteurGauche1()) {
			ligneTrouvee = true;
		}
	}while(!ligneTrouvee);
    _delay_ms(150);
	arret();
}

/*******************************************************************************
* Fonction: tourner180
* Description: Fonction permettant de changer la puissance des moteurs afin de tourner � droite,
*				suis lui-m�me pour 180 degrees.
* Param�tres: aucun
* Retour: aucun
*******************************************************************************/
void tourner180(){
    _delay_ms(1000);
    PORTD |= (1 << 2);
	PORTD |= (1 << 3);
	ajustementPWM(255,255);
    _delay_ms(70);
    ajustementPWM(150, 150);
	_delay_ms(300);
	arret();
    
	PORTD |= (1 << 2);
	PORTD &= ~(1 << 3);
	
	bool ligneTrouvee = false;
	
	kickstart(130);
	_delay_ms(1700);
    
	do{
		if (capteurDroite2()){
			ligneTrouvee = true;
		}
	}while(!ligneTrouvee);
	_delay_ms(100);
	arret();
}

/*******************************************************************************
* Fonction: tourner180
* Description: Fonction permettant de changer la puissance des moteurs afin de tourner � droite,
*				suis lui-m�me pour 180 degrees, mais cette fois on se trouve au d�but et on ne 
*				veut pas avancer avant de tourner.
* Param�tres: aucun
* Retour: aucun
*******************************************************************************/
void tourner180Debut(){
	PORTD |= (1 << 2);
	PORTD &= ~(1 << 3);
	
	bool ligneTrouvee = false;
	
	kickstart(130);
	_delay_ms(1700);
	
	do{
		if (capteurDroite2()){
			ligneTrouvee = true;
		}
	}while(!ligneTrouvee);
	_delay_ms(100);
	arret();
}

/*******************************************************************************
* Fonction: kickstart
* Description: Fonction permettant au robot d'acc�l�rer
* Param�tres: (uint8_t) speed : la vitesse voulue apr�s sont acc�l�ration initiale.
* Retour: aucun
*******************************************************************************/
void kickstart(uint8_t speed){
    ajustementPWM(255,255);
    _delay_ms(70);
    ajustementPWM(speed, speed);
}

/*******************************************************************************
* Fonction: skipCoin
* Description: Fonction permettant au robot d'avancer juste assez pour d�passer une intersection.
* Param�tres: aucun
* Retour: aucun
*******************************************************************************/
void skipCoin(){
	
	_delay_ms(1000);
	
	PORTD |= (1 << 2);
	PORTD |= (1 << 3);
	ajustementPWM(255,255);
    _delay_ms(70);
    ajustementPWM(150, 150);
	_delay_ms(1100);
	arret();
}

/*******************************************************************************
* Fonction: rotationStationnaire
* Description: Fonction permettant au robot de tourner sur lui-m�me
* Param�tres: aucun
* Retour: aucun
*******************************************************************************/
void rotationStationnaire(){
    PORTD |= (1 << 2);
    PORTD &= ~(1 << 3);
    kickstart(120);
}

/*******************************************************************************
* Fonction: reajustementStationnaire
* Description: Fonction permettant au robot de r�ajust� sa position apr�s une rotation
* Param�tres: aucun
* Retour: aucun
*******************************************************************************/
void reajustementStationnaire(){
    PORTD |= (1 << 3);
    PORTD &= ~(1 << 2);
    kickstart(120);
    _delay_ms(220);
    arret();
}

/*******************************************************************************
* Fonction: arret
* Description: Fonction permettant au robot de s'arr�ter apr�s avoir bouger
* Param�tres: aucun
* Retour: aucun
*******************************************************************************/
void arret(){
    PORTD ^= (1 << 2);
    PORTD ^= (1 << 3);
    _delay_ms(100);
    ajustementPWM(0,0);
    PORTD ^= (1 << 2);
    PORTD ^= (1 << 3);
}

/*******************************************************************************
* Fonction: ligneDetecte
* Description: Fonction permettant de savoir si le capteur d�tecte une ligne
* Param�tres: aucun
* Retour: bool : retourne true si un des capteurs d�tecte quelque chose
*******************************************************************************/
bool ligneDetecte(){
    if(capteurDroite1() ||
        capteurDroite2() ||
        capteurMilieu() ||
        capteurGauche1() ||
        capteurGauche2() ){
        return true;
    }
    else
        return false;
}

/*******************************************************************************
* Fonction: mangerBebitte
* Description: Fonction permettant au robot de faire l'affichage quand il atteint un objectif
* Param�tres: (uint8_t) point : Le point sur lequel se trouve l'objectif
* Retour: aucun
*******************************************************************************/
void mangerBebitte(uint8_t point){
    playSoundH(76);
    playSoundL(52);
    if( point == pointA || point == pointB || point == pointC || point == pointD ||
    	point == pointE || point == pointF || point == pointG || point == pointH)
    	afficherRouge();
    
    else	
    	afficherVert();

    _delay_ms(3000);
    eteindre();
    stopSoundH();
    stopSoundL();
}
