/*
 * Series.h
 *
 *  Created on: Feb 15, 2019
 *      Author: robert
 */

#ifndef HELPERS_H_
#define HELPERS_H_

//TODO: Move point struct to a more sensible place (or use a stdc++ definition)
struct Point2D{
	double x = -1;
	double y = -1;
//	double size = 0;
};


// Just like the above Point2D, but with operator overloads for
// complex arithmetic (because imaginary numbers can't quite
// be represented as normal vectors)
struct Point2DComplex{
	double x = -1;
	double y = -1;
	Point2D operator + (const Point2D& b){
			return Point2D {x + b.x, y+b.y};
	}
	Point2D operator - (const Point2D& b){
		return Point2D {x - b.x, y-b.y};
	}
	// This is a non-standard multiplication operator.
	// be warry when trying to use this as a mathematical vector
	//(as opposed to variable length list std::vector) ^
	Point2D operator * (const Point2D& b){
		double re = x * b.x - y*b.y;
		double im = x * b.y + x*b.x;
		return Point2D {im, re};
	}
};
#endif /* HELPERS_H_ */
