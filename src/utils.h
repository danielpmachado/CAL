/*
 * utils.h
 *
 *  Created on: Apr 2, 2017
 *      Author: Sofia
 */

#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include "Graph.h"

#define earthRadiusKm 6371.0

#define IMAGE_X 5000
#define IMAGE_Y 3496
#define SCALE 0.14581997


#define MAX_LAT 40.69559
#define MIN_LAT 40.69026
#define MAX_LNG -73.98061
#define MIN_LNG -73.99066

#define TAB "		"
#define BIG_TAB "				"

typedef unsigned long long int ull_int;

/*
 * @brief converts the longitude to x axis
 *
 * @param longitude the value of longitude
 *
 * @return the x value
 *
 */
int convertLongitudeToX(double longitude);

/*
 * @brief converts the latitude to y axis
 *
 * @param latitude the value of latitude
 *
 * @return the y value
 *
 */
int convertLatitudeToY(double latitude);

/*
 * @brief clears the screen
 *
 */
void clearScreen();

/*
 * @ pauses the screen
 *
 */
void pauseScreen();






#endif /* SRC_UTILS_H_ */
