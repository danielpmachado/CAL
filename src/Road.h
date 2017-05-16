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
	string district;
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

class MatchingRoad {
private:
	string roadName;
	int editDist;
public:
	/**
		 * @brief MatchingRoad constructor
		 *
		 * @param s represents the road name
		 *
		 * @param dist represents the edit distance
		 *
		 */
	MatchingRoad(string s, int dist);
		/**
		 * @brief gets the road name
		 *
		 * @return string road name
		 *
		 */
		string getRoadName() const;
		/**
		 * @brief changes the value string by s
		 *
		 * @param s string road name
		 *
		 */
		void setRoadName(string s);
		/**
			 * @brief gets the distance of v to the src vertex
			 *
			 * @return dist
			 *
			 */
		int getDist() const;
		/**
			 * @brief changes the edit distance
			 *
			 * @param dist new edit distance value
			 *
			 */
		void setDist(int dist);
		/**
			 * @brief overload of the < operator
			 *
			 * @param r2 MatchingRoad to be compared to this
			 *
			 * @return true if this edit distance is higher than v2 edit distance, false otherwise
			 *
			 */
		bool operator<(const MatchingRoad &r2) const;
};


#endif /* SRC_ROAD_H_ */
