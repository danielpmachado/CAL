#pragma once

#include <string>

using namespace std;

/**
 * @brief Class Road
 * This class contains a unique identifier for each road, its name
 * and a boolean flag telling if the road is one or two ways;
 */

class Road {
	unsigned int id; /** <private member containing the unique identifier> */
	string name; /**<private member containing the road name>  */
	bool twoWay; /**<private member that specifies if the road is twoWay, true if so or false if not>  */
public:
	/**
	 * @brief Constructor of Road
	 * Initializes an empty Road
	 */
	Road();
	/**
	 * @brief Constructor of Road
	 * @param unique identifier
	 * @param boolean telling if the road has two ways
	 *
	 */
	Road(unsigned long id, bool twoWay);
	/**
	 * @brief Constructor of Road
	 * @param unique identifier
	 * @param string containing the road's name
	 * @param boolean telling if the road has two ways
	 *
	 */
	Road(unsigned long id, const string &name, bool twoWay);
	/**
	 * @brief function that sets the name of the road
	 */
	void setName(const string &name);
	/**
	 * @brief function that returns the name of the road
	 * @return road name
	 */
	const string& getName() const;
	/**
	 * @brief function that sets the boolean two way
	 * @param boolean that tells if the road is two way
	 */
	void setTwoWay(bool twoWay);
	/**
	 * @brief returns true if the road is two away
	 * @return true if the road is two way
	 */
	bool getTwoWay() const;
	/**
	 * @brief function that returns the road's id
	 * @return unsigned long of the road's id
	 */
	unsigned long getId() const;
	/**
	 * @brief function that allows the overloading of the operator == , in order to compare two roads
	 * @param road
	 * @return true if equal, false if different
	 */
	bool operator == (const Road &p2) const;
	/**
	 * @brief function that allows the overloading of the operator <<, in order to compare to roads
	 * @param ostream
	 * @param road
	 * @return the stream
	 */
	friend ostream & operator << (ostream &os, Road &p);
};
