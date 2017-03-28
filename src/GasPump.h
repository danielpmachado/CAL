#ifndef GASPUMP_H_
#define GASPUMP_H_

#include "Vertex.h"

class GasPump {
private:
	Vertex * node;
	string name;
public:
	GasPum (string n, Vertex * v): name(n), node(v) {}
	void setName (string name);
	void setNode (Vertex * node);
	Vertex getNode () const;
	string getName () const;
};

#endif
