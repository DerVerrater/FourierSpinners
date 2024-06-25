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

// Pointer to pre-existing Chain objects,
// pointer to an array of Point2D's for the signal,
// length of signal,
// number of samples to take (epicycles to create) from signal.
// returns the success/failure of the function
// !!! ALWAYS RETURNS TRUE (because loop always finishes, and I can't detect memory corruption)
bool createDFT(Chain* chains, Point2D* signal, int length, int samples);

#endif /* FOURIER_H_ */
