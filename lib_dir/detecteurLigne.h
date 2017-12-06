
#ifndef DETECTEURLIGNE_H
#define DETECTEURLIGNE_H

#include "constantes.h"

//Boolens qui retournent la valeur lue par les differents capteurs de ligne
bool capteurMilieu();
bool capteurGauche1();
bool capteurDroite1();
bool capteurGauche2();
bool capteurDroite2();

//Si aucun capteur ne detecte de ligne, retourne true
bool aucunCapteur();

//Methode pour suivre une ligne jusqu'a une intersection, recois la vitesse de deplacement sur 255
void suisLigne(uint8_t speed);

//Methode pour detecter la sortie puis se diriger vers la bonne a la fin
void suisLigneFin(uint8_t speed);

//Methodes qui avancent puis tournent a droite ou a gauche
void tournerDroite();
void tournerGauche();

//Methodes qui tournent directement a droite au gauche
void tournerDroiteDebut();
void tournerGaucheDebut();

//Methodes pour effectuer un virage serre a droite ou a gauche dans les quatres coins de la toile
void tournerGrandDroite();
void tournerGrandGauche();

//Methode pour effectuer un virage en U (180 degres)
void tourner180();

//Methode qui effectue directement un virage en U
void tourner180Debut();

//Methode pour continuer lorsque le robot rencontre une intersection, avance avec un delai
void skipCoin();

//Methode pour effectuer une rotation stationnaire stable dans le sens horaire
void rotationStationnaire();

//Methode pour reajuster la rotation stationnaire, rebrousser le chemin parcouru avec l'intertie restante
void reajustementStationnaire();

//Methode qui arrete les moteurs
void arret();

//Retourne si n'importe quel capteur est actif
bool ligneDetecte();

//Methode qui allume la DEL et joue un son lorsque le robot a atteint un objectif
void mangerBebitte(const uint8_t point);

//Methode qui part les moteurs a 100% pendant un court moment puis ajuste a une vitesse desiree afin de
//faciliter le demarrage des moteurs a des vitesses plus lentes
void kickstart(uint8_t speed);

#endif 

