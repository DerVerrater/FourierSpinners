/*
 * Chain.h
 *
 *  Created on: Feb 15, 2019
 *      Author: robert
 */

#ifndef CHAIN_H_
#define CHAIN_H_

#include "Spinner.h"
#include <stdio.h>


class Chain {
	int chainLength;
	Spinner* spinners;
	Spinner anchor;
public:
	Chain() = default;
	Chain(int chainLength, Spinner anchor = Spinner{0, 0, 0});
	Chain(Spinner* spinners, int chainLength, Spinner anchor = Spinner{0, 0, 0});

	int chain_length() const;
	Spinner * const spinners_mut() const;
	const Spinner * const spinners_ptr() const;
	Spinner& anchor_mut();
	const Spinner& anchor_ref() const;
};

#endif /* CHAIN_H_ */
