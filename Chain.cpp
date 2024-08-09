/*
 * Chain.cpp
 *
 *  Created on: Feb 15, 2019
 *      Author: robert
 */

#include "Chain.h"
#include <stdio.h>

Chain::Chain(int chainlength, Spinner anchor){
	this->spinners = new Spinner[chainlength];
	this->chainLength = chainlength;
	this->anchor = anchor;
}

int Chain::chain_length() const {
	return this->chainLength;
}

Spinner* const Chain::spinners_mut() const {
	return this->spinners;
}

const Spinner* const Chain::spinners_ptr() const {
	return this->spinners;
}

Spinner& Chain::anchor_mut() {
	return this->anchor;
}

const Spinner& Chain::anchor_ref() const {
	return this->anchor;
}
