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

Chain::Chain(Spinner* spinners, int chainlength, Spinner anchor) {
	this->spinners = spinners;
	this->chainLength = chainlength;
	this->anchor = anchor;
}
