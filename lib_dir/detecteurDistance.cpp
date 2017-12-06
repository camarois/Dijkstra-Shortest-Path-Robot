#include "detecteurLigne.h"

//Convertisseur analogique numerique
can dist;

//Methode qui montre qu'un instecte loin a ete trouve
void insecteLoinTrouve(){
    PORTA=ROUGE;
    playSoundH(76);
    playSoundL(52);
    _delay_ms(1000);
    PORTA=ETEINT;
    stopSoundH();
    stopSoundL();
}

//Methode qui montre qu'un instecte proche a ete trouve
void insecteProcheTrouve(){
    PORTA=VERT;
    playSoundH(76);
    playSoundL(52);
    _delay_ms(1000);
    PORTA=ETEINT;
    stopSoundH();
    stopSoundL();
}

//Retourne la lecture Perpendiculaire
int positionPerp(){
    char distance = dist.lecture(port) >> 2;
    if(distance >= THRESHHOLD_PROCHE_PERP)
        return 2;
    else if(distance >= THRESHHOLD_LOIN_PERP)
        return 1;
    else
        return 0;
}

//Retourne la lecture Diagonale
int positionDiag(){
    char distance = dist.lecture(port) >> 2;
    if(distance >= THRESHHOLD_PROCHE_DIAG)
        return 2;
    else if(distance >= THRESHHOLD_LOIN_DIAG)
        return 1;
    else
        return 0;
}
