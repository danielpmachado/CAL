#ifndef PARK_H_
#define PARK_H_

#include "Vertex.h"

class Park {
private:
	string type; //Parking Meter or Garage
	double price; //euros per hour
	Vertex * node; //point in the graph
	string name;
public:
	Park (string type, double price, Vertex * node, string name);
	string getType () const;
	double getPrice () const;
	Vertex * getNode () const;
	string getName () const;
	void setType (string type);
	void setPrice (double price);
	void setNode (Vertex * node);
	void setName (string name);
};

#endif
