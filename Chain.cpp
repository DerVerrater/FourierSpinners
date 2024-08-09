/*
 * Chain.cpp
 *
 *  Created on: Feb 15, 2019
 *      Author: robert
 */

#include "Chain.h"
#include <stdio.h>

Chain::Chain(int chainlength, Spinner anchor){
	this->spinner_vec.reserve(chainlength);
	this->anchor = anchor;
}

int Chain::chain_length() const {
	return this->spinner_vec.size();
}

std::vector<Spinner>& Chain::spinners_mut() {
	return this->spinner_vec;
}

const Spinner* const Chain::spinners_ptr() const {
	return this->spinner_vec.data();
}

Spinner& Chain::anchor_mut() {
	return this->anchor;
}

const Spinner& Chain::anchor_ref() const {
	return this->anchor;
}
