/*
 * Fourier.h
 *
 *  Created on: Feb 15, 2019
 *      Author: robert
 */

#ifndef FOURIER_H_
#define FOURIER_H_

#include "Chain.h"
#include "Helpers.h"
#include "Spinner.h"


// don't actually need to create a class
class Fourier {
public:
	static Chain** createDFT(Point2D* signal, int length, int samples);
};

#endif /* FOURIER_H_ */
