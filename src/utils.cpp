/*
 * utils.cpp
 *
 *  Created on: 07/04/2017
 *      Author: up201504570
 */


#include "utils.h"


int convertLongitudeToX(double longitude) {
	return floor((longitude - MIN_LNG) * IMAGE_X / (MAX_LNG - MIN_LNG));
}

int convertLatitudeToY(double latitude) {
	return IMAGE_Y - floor((latitude - MIN_LAT) * IMAGE_Y / (MAX_LAT - MIN_LAT))
			+ 3.5;

}

void clearScreen() {
	system("cls");
}

void pauseScreen() {
	getchar();
}



