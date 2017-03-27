/*
 * Coordinates.cpp
 */
#include "Point.h"

#include "Road.h"
#include <cmath>
#include <iostream>


/* Class Point*/

Point::Point(){
	this->id=0;
	this->x=0;
	this->y=0;
	this->latitude=0;
	this->longitude=0;
}

Point::Point(unsigned long id,double latitude, double longitude, double x, double y) {
	this->id=id;
	this->latitude=latitude;
	this->longitude=longitude;
	this->x=x;
	this->y=y;

}

unsigned long Point:: getId() const{
	return id;
}

double Point:: getX() const{
	return x;
}

double Point:: getY() const{
	return y;
}

double  Point:: getLatitude() const{
	return latitude;
}

double  Point:: getLongitude() const{
	return longitude;
}

void Point::setPOI(string POI){
	this->POI=POI;
}

void Point::setSuburb(const string &suburb){
	this->suburb=suburb;
}

string Point::getSuburb() const{
	return suburb;
}

string Point::getPOI() const{
	return POI;
}

double Point::getDistance(const Point &c) const {
	double radlat1 = PI * this->getLatitude()/180;
	double radlat2 = PI * c.getLatitude()/180;
	double theta = this->longitude-c.getLongitude();
	double radtheta =PI * theta/180;
	double dist = sin(radlat1) * sin(radlat2) +cos(radlat1) * cos(radlat2) * cos(radtheta);
	dist = acos(dist);
	dist = dist * 180/PI;
	dist = dist * 60 * 1.1515;
	dist = dist * 1.609344;

	return dist;
}

bool Point::operator==(const Point &rhs) const {
	return this->id == rhs.id;
}

ostream& operator<<(ostream& out, const Point &point) {
	out << "ID: " << point.getId() << "\tLatitude: " << point.getLatitude() << "\tLongitude: " << point.getLongitude();
	return out;
}
