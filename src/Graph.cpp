/*
 * Graph.cpp
 *
 *  Created on: 01/04/2017
 *      Author: bibib
 */
#include "Graph.h"
/*
 * CLASS VERTEX
 */
Vertex::Vertex(long id, double lon, double lat): longitude(lon),latitude(lat), visited(false), processing(false), indegree(0), dist(LONG_MAX), inQueue(false) {
	this->id = id;
	path = NULL;
}

void Vertex::addEdge(Vertex *dest, Road * road, double w) {
	Edge *edgeD = new Edge(dest, road, w);
	adj.push_back(edgeD);
}
vector<Edge *> Vertex::getAdj() const {
	return adj;
}
long Vertex::getID() const {
	return id;
}

double Vertex::getLongitude() const {
	return longitude;
}

double Vertex::getLatitude() const {
	return latitude;
}



long Vertex::getDist() const {
	return this->dist;
}

void Vertex::setLongitude(long lon) {
	this->longitude = lon;
}

void Vertex::setLatitude(long lat) {
	this->latitude = lat;
}

void Vertex::setID(long id) {
	this->id = id;
}


int Vertex::getIndegree() const {
	return this->indegree;
}

bool Vertex::removeEdgeTo(Vertex *d) {
	d->indegree--; //adicionado do exercicio 5
	typename vector<Edge*>::iterator it= adj.begin();
	typename vector<Edge*>::iterator ite= adj.end();
	while (it!=ite) {
		if ((*it)->dest == d) {
			adj.erase(it);
			return true;
		}
		else it++;
	}
	return false;
}

Edge * Vertex::getEdgeToVertex(Vertex * dest) {
	for(Edge * e : adj) {
		if(e->getDest() == dest) {
			return e;
		}
	}
	return NULL;
}

/*
 * CLASS EDGE
 */
int Edge::edgesID = 0;
Edge::Edge(Vertex *d, Road * road, double w): dest(d), weight(w){
	edgesID++;
	this->id = edgesID;
	this->road = road;
	inGraphViewer = false;
}
Road * Edge::getRoad () const {
	return road;
}
Vertex * Edge::getDest() const {
	return dest;
}
int Edge::getID() {
	return id;
}
double Edge::getWeight() {return weight;}
bool Edge::isInGraphViewer() {
	return inGraphViewer;
}
void Edge::setInGraphViewer() {
	inGraphViewer = inGraphViewer ? false : true;
}

/*
 * CLASS GRAPH
 */
int Graph::getNumVertex() const {
	return vertexSet.size();
}

vector<Vertex * > Graph::getVertexSet() const {
	return vertexSet;
}

bool Graph::addVertex(Vertex * v) {
	typename vector<Vertex*>::iterator it= vertexSet.begin();
	typename vector<Vertex*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++)
		if ((*it) == v) return false;

	vertexSet.push_back(v);
	return true;
}

bool Graph::addEdge(int sourcID, int destID, double w, Road * road) {
	typename vector<Vertex*>::iterator it= vertexSet.begin();
	typename vector<Vertex*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex *vS, *vD;
	while (found!=2 && it!=ite ) {
		if ( (*it)->getID() == sourcID )
			{ vS=*it; found++;}
		if ( (*it)->getID() == destID )
			{ vD=*it; found++;}
		it ++;
	}
	if (found!=2) return false;
	vD->indegree++;
	vS->addEdge(vD, road, w);

	return true;
}
bool Graph::removeVertex(Vertex * v) {
	typename vector<Vertex*>::iterator it= vertexSet.begin();
	typename vector<Vertex*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++) {
		if ((*it) == v) {
			Vertex * vertexRemoved= *it;
			vertexSet.erase(it);
			typename vector<Vertex*>::iterator it1= vertexSet.begin();
			typename vector<Vertex*>::iterator it1e= vertexSet.end();
			for (; it1!=it1e; it1++) {
				(*it1)->removeEdgeTo(vertexRemoved);
			}

			typename vector<Edge*>::iterator itAdj= vertexRemoved->adj.begin();
			typename vector<Edge*>::iterator itAdje= vertexRemoved->adj.end();
			for (; itAdj!=itAdje; itAdj++) {
				(*itAdj)->dest->indegree--;
			}
			delete v;
			return true;
		}
	}
	return false;
}
Vertex * Graph::getVertex(long id) const {
	for (int i = 0; i < vertexSet.size(); i++) {
		if(vertexSet[i]->getID() == id) {
			return vertexSet[i];
		}
	}
	return NULL;
}
/*vector<Vertex*> Graph::dfs(GraphViewer *myGV) const {
	typename vector<Vertex*>::const_iterator it= vertexSet.begin();
	typename vector<Vertex*>::const_iterator ite= vertexSet.end();
	for (; it !=ite; it++)
		(*it)->visited=false;
	vector<Vertex*> res;
	it=vertexSet.begin();
	for (; it !=ite; it++)
	    if ( (*it)->visited==false )
	    	dfs(*it,res, 0, myGV);
	return res;
}

void Graph::dfs(Vertex *v,vector<Vertex*> &res, double count, GraphViewer *myGV) const {
	double size = count;
	v->visited = true;
	if(size < 0.5 && size > 0) {
		myGV->setVertexSize(v->getID(), 0);
	}
	res.push_back(v);
	typename vector<Edge*>::iterator it= (v->adj).begin();
	typename vector<Edge*>::iterator ite= (v->adj).end();
	for (; it !=ite; it++)
	    if ( (*it)->dest->visited == false ){
	    	if(size < 0.5 && size > 0) {
	    		size += (*it)->getWeight();
	    	} else {
	    		size = 0;
	    	}
	    	dfs((*it)->dest, res, size, myGV);
	    }
}*/

vector<Vertex*> Graph::getSources() const {
	vector< Vertex* > buffer;
	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		if( vertexSet[i]->indegree == 0 ) buffer.push_back( vertexSet[i] );
	}
	return buffer;
}

void Graph::dijkstraShortestPath(Vertex * v) {
	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = LONG_MAX;
	}

	v->dist = 0;
	priority_queue< Vertex* > q;
	q.push(v);
	v->inQueue = true;

	while( !q.empty() ) {
		Vertex * processingVertex = q.top(); q.pop();
		processingVertex->inQueue = false;
		for(unsigned int i = 0; i < processingVertex->adj.size(); i++) {
			Vertex* w = processingVertex->adj[i]->dest;
			if( w->dist > (processingVertex->dist+ processingVertex->adj[i]->weight) ) {
				w->dist = (processingVertex->dist+ processingVertex->adj[i]->weight);
				w->path = processingVertex;
				if(!(w->inQueue)) {
					q.push(w);
					w->inQueue = true;
				}
			}
		}
	}
}

vector<Vertex *> Graph::getPath(Vertex * origin, Vertex * dest, long &totalDist){

	list<Vertex *> buffer;
	Vertex * v = dest;
	//cout << v->info << " ";
	while ( v->path != NULL) {
		totalDist += ((v->path)->getEdgeToVertex(v))->getWeight();
		cout << "\n>>>totalDist = " << totalDist << "<<\n";
		buffer.push_front(v);
		v = v->path;
	}
	if( v->path == NULL ) {
		if(totalDist == 0) {//o vertice origem nao chega ate ao dest
			totalDist = LONG_MAX;
		}
		buffer.push_front(v);
	}


	vector<Vertex *> res;
	while( !buffer.empty() ) {
		res.push_back( buffer.front() );
		buffer.pop_front();
	}
	return res;
}


vector<long> Graph::searchStreetNodes(string street) {
    vector<long> streetVertex;
    typename vector<Vertex*>::const_iterator it;
    bool found = false;

    for (it = vertexSet.begin(); it != vertexSet.end(); it++) {
        (*it)->visited = false;
    }

    for (it = vertexSet.begin(); it != vertexSet.end(); it++) {
        if (!(*it)->visited)
            searchStreetNodes(*it, street, streetVertex);
    }

    return streetVertex;
}

void Graph::searchStreetNodes(Vertex * v,string street, vector<long> &streetVertex) const {
    v->visited = true;


    for (Edge * e : v->getAdj()) {
        if(e->road->getName() == street && !e->dest->visited){
            streetVertex.push_back(v->getID());
            streetVertex.push_back(e->dest->getID());
        }

        if (!e->dest->visited)
            searchStreetNodes(e->dest,street, streetVertex);


    }

}

