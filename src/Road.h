/*
 * Road.h
 *
 *  Created on: 02/04/2017
 *      Author: bibib
 */

#ifndef SRC_ROAD_H_
#define SRC_ROAD_H_

#include <vector>
#include <queue>
#include <list>
#include <climits>
#include <cmath>
#include <cstdint>
#include <string>
using namespace std;

class Road {
private:
	int id;
	string name;
	bool twoWays;
public:
	Road(int id, string name, bool twoWays);
	int getID();
	string getName();
	bool isTwoWays();
	void setID(int id);
	void setName(string name);
	void setTwoWays();
};




#endif /* SRC_ROAD_H_ */
