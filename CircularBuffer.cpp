/*
 * CircularBuffer.cpp
 *
 *  Created on: Feb 13, 2019
 *      Author: robert
 */

#include "CircularBuffer.h"
#include "Helpers.h"
#include <stdio.h>

CircularBuffer::CircularBuffer(int size) {
	this->capacity = size;
	this->idx = 0; // the next available space to write into
	this->point_buffer.reserve(size);
	for(size_t idx = 0; idx < size; idx++){
		this->point_buffer.push_back(Point2D{});
	}
}

Point2D CircularBuffer::pop(){
	--idx; // current pos is *next* available, so decrement first.
	if(idx == -1){
		idx = capacity-1;
//		printf("Circular buffer rollunder!\n");
	}
	Point2D p = point_buffer[idx];
	return p;
}

const Point2D& CircularBuffer::peek(){
	return point_buffer[idx-1];
}

void CircularBuffer::push(Point2D inp){
	point_buffer[idx++] = inp; // current pos is in bounds
		// and advance to next available
	if(idx >= capacity){ // if new pos is out of bounds, then fix
		idx = 0;
		printf("Circular buffer rollover!\n");
	} // roll over to min
}

const Point2D* const CircularBuffer::data_mut() {
	return this->point_buffer.data();
}

const std::vector<Point2D> CircularBuffer::data_vec() const {
	return this->point_buffer;
}

const Point2D* const CircularBuffer::data() const {
	return this->point_buffer.data();
}

const int CircularBuffer::size() const {
	return this->capacity;
}