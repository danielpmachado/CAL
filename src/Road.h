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

	/*
	 * @brief Road constructor
	 *
	 * @param id the road id
	 *
	 * @param name the road name
	 *
	 * @param twoWays a boolean, true if the road has two ways, false otherwise
	 *
	 */
	Road(int id, string name, bool twoWays);

	/*
	 * @brief gets the road id
	 *
	 * @return the road id
	 */
	int getID();

	/*
	 * @brief gets the road name
	 *
	 * @return the road name
	 */
	string getName();

	/*
	 * @brief gets the information about the ways of the road
	 *
	 * @return a boolean, true if the road has two ways, false otherwise
	 */
	bool isTwoWays();

	/*
	 * @brief sets the road id
	 *
	 * @param id the road id
	 */
	void setID(int id);

	/*
	 * @brief sets the road name
	 *
	 * @param id the road name
	 */
	void setName(string name);

	/*
	 * @brief sets the road two ways value
	 *
	 */
	void setTwoWays();
};




#endif /* SRC_ROAD_H_ */
