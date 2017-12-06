#include "moteurs.h"

void ajustementPWM ( uint16_t changementGauche, uint16_t changementDroite) {

		// mise a un des sorties OC1A et OC1B sur comparaison

		// reussie en mode PWM 8 bits, phase correcte

		// et valeur de TOP fixe a 0xFF (mode #1 de la table 16-5

		// page 130 de la description technique du ATmega324PA)

		//TCNT1 = 0;

		//TCCR1A |= (1 << COM1B1) | (1 << COM1A1) | (1 << WGM10);

		//TCCR1B |= (1 << CS11);

		//TCCR1C = 0;
    
    uint8_t changementBatterie = 85;    //pourcentage

		OCR1A =  uint16_t(changementGauche * changementBatterie / 100);

		OCR1B = uint16_t(changementDroite *  (changementBatterie-5) / 100);

	}

void initPWM(){

	TCNT1 = 0;

	TCCR1A |= (1 << COM1B1) | (1 << COM1A1) | (1 << WGM10);

	TCCR1B |= (1 << CS11);

	TCCR1C = 0;

	}

