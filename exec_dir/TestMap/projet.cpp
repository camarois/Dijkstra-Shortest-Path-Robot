#include "map.h"
#include <ostream>
#include <iostream>
using namespace std;

int main()
{
	int a = retourneIndexVoisin(point0, point5);
	int b = retourneIndexVoisin(pointH, pointG);
	int c = retourneIndexVoisin(point1, pointA);
	cout << a << " " << b << " " << c;

	const uint8_t points[Nobjectif] = {0x01, 0x02, 0x0C, 0x0D, 0x0E};
	uint8_t chemin[MAX_LONGUEUR_CHEMIN] = {0X00, 0X01, 0X02, 0X03, 0X0C, 0X0D, 0X0E};

	deplacementRobot((&chemin)[MAX_LONGUEUR_CHEMIN], (&points)[Nobjectif]);

	return 0;
}