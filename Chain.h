/*
 * Chain.h
 *
 *  Created on: Feb 15, 2019
 *      Author: robert
 */

#ifndef CHAIN_H_
#define CHAIN_H_

#include "Spinner.h"
#include <vector>

class Chain {
	std::vector<Spinner> spinner_vec;
	Spinner anchor;
public:
	Chain(int chainLength, Spinner anchor = Spinner{0, 0, 0});
	int chain_length() const;
	std::vector<Spinner>& spinners_mut();
	const Spinner * const spinners_ptr() const;
	Spinner& anchor_mut();
	const Spinner& anchor_ref() const;
};

#endif /* CHAIN_H_ */
