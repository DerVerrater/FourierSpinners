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

//TODO: Use template to make this a generic ring-buffer.
class CircularBuffer {
public:
	int size; // capacity of buffer
	int pos;  // current position in buffer
	Point2D* data; // pointer to data in buffer
	CircularBuffer(int size);
	virtual ~CircularBuffer();
	Point2D pop();
	Point2D peek(); // return newest value without moving pos
	void push(Point2D& inp);
};

#endif /* CIRCULARBUFFER_H_ */


