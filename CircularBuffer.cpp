/*
 * CircularBuffer.cpp
 *
 *  Created on: Feb 13, 2019
 *      Author: robert
 */

#include "CircularBuffer.h"
#include <stdio.h>

CircularBuffer::CircularBuffer(int size) {
	this-> size = size;
	this-> pos = 0; // the next available space to write into
	data = new Point2D[size];
}

CircularBuffer::~CircularBuffer() {
	// TODO Auto-generated destructor stub
}

Point2D CircularBuffer::pop(){
	--pos; // current pos is *next* available, so decrement first.
	if(pos <= 0){
		pos = size;
//		printf("Circular buffer rollunder!\n");
	}
	Point2D p = data[pos];
	return p;
}

Point2D CircularBuffer::peek(){
	return data[pos-1];
}

void CircularBuffer::push(Point2D& inp){
	data[pos++] = inp; // current pos is in bounds
		// and advance to next available
	if(pos > size){ // if new pos is out of bounds, then fix
		pos = 0;
		printf("Circular buffer rollover!\n");
	} // roll over to min
}
