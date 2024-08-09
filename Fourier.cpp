/*
 * Fourier.cpp
 *
 *  Created on: Feb 15, 2019
 *      Author: robert
 */

#include "Fourier.h"
#include <cmath>
#include <stdio.h>

std::pair<Chain, Chain> createDFT(const std::vector<const Point2D>& signal, int numSamples){
	printf("Reading signal of len %zu, creating samples %d\n", signal.size(), numSamples);
	std::pair<Chain, Chain> chains = {
		Chain(numSamples),
		Chain(numSamples)
	};

	for(int k=0; k<numSamples; k++){
		double reHori = 0; // the real portion of the Fourier transform
		double imHori = 0; // the imaginary portion """
		double reVert = 0;
		double imVert = 0;
		for (int n = 0; n < signal.size(); n++) {
//			printf("chunk loop iter %d/%d\n", n, (length-1));
			double phi = (2 * M_PI * k * n) / signal.size();
			// TODO: Find nicer way of picking Point2D variable (array-like offsets? Magic with pointers?)
			// horizontal spinners
			reHori += (signal[n].x - chains.first.anchor_ref().getX()) * cos(phi);
			imHori -= (signal[n].x - chains.first.anchor_ref().getX()) * sin(phi);
			// vertical spinners
			reVert += (signal[n].y - chains.second.anchor_ref().getY()) * cos(phi);
			imVert -= (signal[n].y - chains.second.anchor_ref().getY()) * sin(phi);
		}
//      printf("DFT Params -> re: %d, im: %d\n", reHori, imHori);
		reHori = reHori / signal.size();
		imHori = imHori / signal.size();
		reVert = reVert / signal.size();
		imVert = imVert / signal.size();
		double ampH = sqrtl(pow(reHori, 2) + pow(imHori, 2));
		double phaseH = atan2l(imHori, reHori);
		double freqH = k;
		double ampV = sqrtl(pow(reVert, 2) + pow(imVert, 2));
		double phaseV = atan2l(imVert, reVert);
		double freqV = k;

		// reassign values
		chains.first.spinners_mut()[k].freq = freqH;
		chains.first.spinners_mut()[k].theta = phaseH;
		chains.first.spinners_mut()[k].rho = ampH;
		chains.second.spinners_mut()[k].freq = freqV;
		chains.second.spinners_mut()[k].theta = phaseV + M_PI/2;
		chains.second.spinners_mut()[k].rho = ampV;

//		printf("	Sav'd (%f, %f, %f)\n",
//				chains[1].spinners[k].rho,
//				chains[1].spinners[k].theta,
//				chains[1].spinners[k].freq);
//		printf("	addr: %d\n", &chains[1].spinners[k]);
	}
//	printf("Transform complete. Returning...\n");
	return chains;
}
