#ifndef GASPUMP_H_
#define GASPUMP_H_

#include "Vertex.h"

class GasPump {
private:
	Vertex * node;
public:
	GasPum (Vertex * v): node(v) {}
	void setNode (Vertex * node);
	Vertex getNode () const;
};

#endif
