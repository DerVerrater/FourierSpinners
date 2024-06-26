/*
 * CircularBuffer.h
 *
 *  Created on: Feb 13, 2019
 *      Author: robert
 */

#ifndef CIRCULARBUFFER_H_
#define CIRCULARBUFFER_H_

#include "Spinner.h"
#include "Helpers.h"
#include <vector>

//TODO: Use template to make this a generic ring-buffer.
class CircularBuffer {
	int capacity; // capacity of buffer
	int idx;  // current position in buffer
	std::vector<Point2D> point_buffer; // data in buffer
public:
	CircularBuffer(int size);
	Point2D pop();
	const Point2D& peek(); // return newest value without moving pos
	void push(Point2D inp);
	const Point2D* const data_mut();
	const Point2D* const data() const;
	const int size() const;
};

#endif /* CIRCULARBUFFER_H_ */


