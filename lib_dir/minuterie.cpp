
#include "minuterie.h"

volatile uint8_t minuterieExpiree;
volatile uint8_t boutonPoussoir;

void initialisation(void){

	cli();

	DDRB = 0xff;	//sortie	
	DDRD = 0x00;	//entrée

	EIMSK |= _BV(INT0);

	EICRA |= (1 << ISC01) | (1 << ISC00);

	sei();
}  
				
ISR (TIMER1_COMPA_vect) {
	minuterieExpiree = 1;
}

ISR (INT0_vect) {
	
	_delay_ms (30);

	if(PIND & 0x04)
		boutonPoussoir = 1;
}

void partirMinuterie (  uint16_t duree ) {

minuterieExpiree = 0;

// mode CTC du timer 1 avec horloge divisee par 1024

// interruption apres la duree specifiee

TCNT1 = 0;

OCR1A = duree;

TCCR1A = (1 << COM1A1) | (1 << COM1A0) ;

TCCR1B = (1 << CS12) | (1 << CS10) | (1 << WGM12) ;

TCCR1C = 0 ;

TIMSK1 |= (1 << ICIE1) | (1 << OCIE1A) ;

}
