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
public:
	int chainLength;
	Spinner* spinners;
	Spinner anchor;
	Chain() = default;
	Chain(int chainLength, Spinner anchor = Spinner{0, 0, 0});
	Chain(Spinner* spinners, int chainLength, Spinner anchor = Spinner{0, 0, 0});
};

#endif /* CHAIN_H_ */
