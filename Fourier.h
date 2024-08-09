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

// Signal is a vector of points.
// number of samples to take (epicycles to create) from signal.
// returns a std::pair of chains
std::pair<Chain, Chain> createDFT(const std::vector<const Point2D>& signal, int samples);

#endif /* FOURIER_H_ */
