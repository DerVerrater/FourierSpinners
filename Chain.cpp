/*
 * Chain.cpp
 *
 *  Created on: Feb 15, 2019
 *      Author: robert
 */

#include "Chain.h"
#include <stdio.h>



Chain::Chain(){
	this->spinners = nullptr;
	this->chainLength = 0;
	this->anchor = Spinner(0, 0, 0);
}

Chain::Chain(int chainlength, Spinner anchor){
	this->spinners = new Spinner[chainlength];
	this->chainLength = chainlength;
	this->anchor = anchor;
}

Chain::Chain(Spinner* spinners, int chainlength, Spinner anchor) {
	this->spinners = spinners;
	this->chainLength = chainLength;
	this->anchor = anchor;
}

// VVV UNTESTED STUFF FOR COPYING OBJECTS AROUND VVV
// 		this existed for an incomplete solution that would allow
// 		the Fourier.cpp's DFT function to return a pointer to
// 		a pair of Chain objects put on the heap.
// 		Problems with shallow copying the Chain's caused segfaults.

//Chain::Chain(Chain const& copy){
//	spinners = copy.spinners;
//	chainLength = copy.chainLength;
//	anchor = copy.anchor;
//}
//
//Chain& Chain::operator=(Chain rhs){
//	rhs.swap(*this);
//	return *this;
//}
//
//void Chain::swap(Chain& s) noexcept{
//	this->spinners = s.spinners;
//}


Chain::~Chain() {
	//TODO SOLVE DOUBLE-FREE ERROR
	// VVV results in double-free memory corruption. WTF?
	this->spinners = nullptr;
}

