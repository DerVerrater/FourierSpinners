#include "point2d.h"

Point2D Point2DComplex::operator+(const Point2D& rhs) {
	return Point2D {x + rhs.x, y + rhs.y};
}

Point2D Point2DComplex::operator-(const Point2D& rhs){
	return Point2D {x - rhs.x, y-rhs.y};
}

Point2D Point2DComplex::operator*(const Point2D& rhs) {
	double re = this->x * rhs.x - this->y * rhs.y;
	double im = this->x * rhs.y + this->x * rhs.x;
	return Point2D{ im, re };
}
