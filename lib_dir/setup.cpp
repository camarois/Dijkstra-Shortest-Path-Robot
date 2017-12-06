#include "setup.h"

//setup pour le robot lorsqu'il est en mouvement
void setup() {
	DDRA = 0x03;//PINA1 et PINA2 en SORTIE, les autres en ENTREE. 1100 0000
	DDRB = 0x0C;//PINB3 et PINB4 en SORTIE, les autres en ENTREE 0011 0000
	DDRC = ENTREE;
	DDRD = SORTIE;
	
	//CTC Piezo 1 (H)
	TCCR2A = (1 << WGM21) | (1 << COM2A0); //Mode CTC, toggle on COMPARE-MATCH
	TCCR2B = (1 << CS22); //prescaler
	OCR2A = 0;
    //CTC Piezo 2 (L)
    TCCR0A = (1 << WGM01) | (1 << COM0A0); //Mode CTC, toggle on COMPARE-MATCH
	TCCR0B = (1 << CS01) | (1 << CS00); //prescaler
	OCR0A = 0;

	 //PWM Roues
	TCCR1A |= (1 << WGM10) | (1 << COM1A1) | (1 << COM1B1);
	TCCR1B |= (1 << CS11) ; 
	TCCR1C = 0;
	TCNT1 = 0;

	//initialisationUART();
	_delay_ms(50);
	
}

//routine de démarrage
void demarrage() {
	fadeDEL(ROUGE, VERT);
	PORTA = ETEINT;
	_delay_ms(500);
	for(int i = 0 ; i <= 10 ; i++){	
			PORTA = ROUGE;
			_delay_ms(50);
			PORTA = ETEINT;
			_delay_ms(50);
		}
}

//setup pour le robot lorsqu'il est en attente
void setupInterruption() {
	DDRA = 0x03;//PINA1 et PINA2 en SORTIE, les autres en ENTREE. 1100 0000
	DDRB = 0x0C;//PINB3 et PINB4 en SORTIE, les autres en ENTREE 0011 0000
	DDRC = ENTREE;
	DDRD = ENTREE;
	_delay_ms(50);
}

//fonction qui met le robot temporairement en attente 
void pause(){
	setupInterruption();
    _delay_ms(50);
	while(!(PIND & 0x04)){
		afficherAmbre();
	}
	eteindre();
	_delay_ms(3000);
}
