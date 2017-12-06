#include "del.h"

void afficherVert() {
	PORTA = VERT;
}

void afficherRouge() {
	PORTA = ROUGE;
}

void afficherAmbre() {
	afficherRouge();
    _delay_ms(1);
    afficherVert();
    _delay_ms(7);
}

void eteindre(){
	PORTA = ETEINT;
}

void fadeDEL(uint8_t origine, uint8_t cible)
{

    uint16_t a = 180;
    uint16_t b = a;
	
	while (a > 0)
	{
		for(uint32_t i = 0; i < a; i++)
		{
			PORTA = origine;
			_delay_us(13);
		}
			
		for(uint32_t i = 0; i < b - a; i++)
		{
			PORTA = cible;
			_delay_us(13);
		}
			
		a -= 1;
	}
}
