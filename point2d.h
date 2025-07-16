/*
 * Series.h
 *
 *  Created on: Feb 15, 2019
 *      Author: robert
 */

#ifndef HELPERS_H_
#define HELPERS_H_

struct Point2D{
	double x;
	double y;
//	double size = 0;
};


// Just like the above Point2D, but with operator overloads for
// complex arithmetic (because imaginary numbers can't quite
// be represented as normal vectors)
struct Point2DComplex{
	double x;
	double y;
	Point2D operator + (const Point2D& b);
	Point2D operator - (const Point2D& b);
	
	// This multiplication overload only makes sense for complex numbers.
	// Be careful using Point2DComplex as a simple coordinate type.
	Point2D operator * (const Point2D& b);
};
#endif /* HELPERS_H_ */
