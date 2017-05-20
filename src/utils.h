/*
 * utils.h
 *
 *  Created on: Apr 2, 2017
 *      Author: Sofia
 */

#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include <sstream>
#include "Graph.h"

#define earthRadiusKm 6371.0

#define IMAGE_X_1 5000
#define IMAGE_Y_1 3496
#define MAX_LAT_1 40.69559
#define MIN_LAT_1 40.69026
#define MAX_LNG_1 -73.98061
#define MIN_LNG_1 -73.99066



#define IMAGE_X_2 5000
#define IMAGE_Y_2 4108
#define MAX_LAT_2 40.80380
#define MIN_LAT_2 40.79820
#define MAX_LNG_2 -73.94367
#define MIN_LNG_2 -73.95269



#define SCALE 0.14581997




#define TAB "		"
#define BIG_TAB "				"

typedef unsigned long long int ull_int;

/**
 * @brief converts the longitude to x axis
 *
 * @param longitude the value of longitude
 *
 * @param district
 *
 * @return the x value
 *
 */
int convertLongitudeToX(double longitude,string district);

/**
 * @brief converts the latitude to y axis
 *
 * @param latitude the value of latitude
 *
 * @param district
 *
 * @return the y value
 *
 */
int convertLatitudeToY(double latitude,string district);

/**
 * @brief clears the screen
 *
 */
void clearScreen();

/**
 * @brief pauses the screen
 *
 */
void pauseScreen();


/**
 *@brief splits a string in a vector of strings
 */
vector<string> split(string str);

/**
 * @brief Knuth-Morris-Pratt algorithm
 */
bool kmp(string text, string pattern);


/**
 * @brief KMP preprocessing function
 */
void pre_kmp(string pattern, vector<int> & prefix);

/**
 * @brief number of changes that need to be done in the string text
 */
int editDistance(string pattern, string text);

void normalize(string &str);

void upCase(string &str);

void normalize2(string &str);

string getFilePath(string file_name,string district);

#endif /* SRC_UTILS_H_ */
