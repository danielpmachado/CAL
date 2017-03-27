/*
 * Coordinates.h
 */

#ifndef SRC_POINT_H_
#define SRC_POINT_H_

#include "Road.h"
#include <math.h>
#define PI 3.14159265359

using namespace std;

/**
 * @brief Class Point.
 * Class that contains all the dots of the map, containing information on its
 * latitude, longitude, projected coordinates and, if it is a point of interest,
 * the name of the POI;
 */

class Point{
	unsigned long id; /**< private member that contains the unique identifier */
	double latitude; /**< private member that contains the latitude */
	double longitude; /**< private member that contains the longitude */
	double x; /**< private member that contains the projected coordinate on x */
	double y; /**< private member that contains the projected coordinate on y */
	string POI = ""; /**< private member that, in the case of a point of interest, contains its name */
	string suburb = ""; /**< private member containing info on the suburb of the point */

public:
	/**
	 * @brief Constructor of Point
	 * Initializes an empty Point
	 */
	Point();
	/**
	 * @brief Constructor of Point
	 * @param unique identifier
	 * @param latitude
	 * @param longitude
	 * @param projected coordinate on x
	 * @param projected coordinate on y
	 *
	 */
	Point(unsigned long id,double latitude, double longitude, double x, double y);

	/**
	 * @brief function that returns the point identifier;
	 * @return identifier;
	 */
	unsigned long getId() const;

	/**
	 * @brief function the returns the projected coordinate on x
	 * @return projected coordinate on x
	 */
	double getX() const;

	/**
	 * @brief function the returns the projected coordinate on y
	 * @return projected coordinate on y
	 */
	double getY() const;

	/**
	 * @brief function the returns the latitude
	 * @return latitude
	 */
	double getLatitude() const;

	/**
	 * @brief function the returns the longitude
	 * @return longitude
	 */
	double getLongitude() const;

	/**
	 * @brief sets the name of the POI
	 */
	void setPOI(string POI);

	/**
	 * @brief sets the name of the suburb
	 */
	void setSuburb(const string &suburb);

	/**
		 * @brief returns a string with the suburb
		 * @return string of the suburb
	*/

	string getSuburb() const;

	/**
	 * @brief if it is a point of interest returns its name, else
	 * returns an empty string
	 * @return string of point of interest
	 */

	string getPOI() const;

	/**
	 * @brief returns the distance between this point and the point given
	 * in the argument
	 * @return a double containing the distance
	 */
	double getDistance(const Point &c) const;

	/**
	 * @brief function that allows the overloading of the operator == , in order to compare to points
	 * @param point
	 * @return true if equal, false if different
	 */
	bool operator==(const Point &rhs) const;

	/**
	 * @brief function that allows the overloading of the operator <<, in order to compare to points
	 * @param ostream
	 * @param point
	 * @return the stream
	 */
	friend ostream &operator<<(ostream& out, const Point &point);
};


#endif /* SRC_POINT_H_ */
