/*
 * Fourier.cpp
 *
 *  Created on: Feb 15, 2019
 *      Author: robert
 */

#include "Fourier.h"
#include <cmath>
#include <stdio.h>

bool createDFT(Chain* chains, Point2D* signal, int sigLength, int numSamples){
	printf("Reading signal of len %d, creating samples %d\n", sigLength, numSamples);

	for(int k=0; k<numSamples; k++){
		double reHori = 0; // the real portion of the Fourier transform
		double imHori = 0; // the imaginary portion """
		double reVert = 0;
		double imVert = 0;
		for (int n = 0; n < sigLength; n++) {
//			printf("chunk loop iter %d/%d\n", n, (length-1));
			double phi = (2 * M_PI * k * n) / sigLength;
			// TODO: Find nicer way of picking Point2D variable (array-like offsets? Magic with pointers?)
			// horizontal spinners
			reHori += (signal[n].x - chains[0].anchor.getX()) * cos(phi);
			imHori -= (signal[n].x - chains[0].anchor.getX()) * sin(phi);
			// vertical spinners
			reVert += (signal[n].y - chains[1].anchor.getY()) * cos(phi);
			imVert -= (signal[n].y - chains[1].anchor.getY()) * sin(phi);
		}
//      printf("DFT Params -> re: %d, im: %d\n", reHori, imHori);
		reHori = reHori / sigLength;
		imHori = imHori / sigLength;
		reVert = reVert / sigLength;
		imVert = imVert / sigLength;
		double ampH = sqrtl(pow(reHori, 2) + pow(imHori, 2));
		double phaseH = atan2l(imHori, reHori);
		double freqH = k;
		double ampV = sqrtl(pow(reVert, 2) + pow(imVert, 2));
		double phaseV = atan2l(imVert, reVert);
		double freqV = k;

		// reassign values
		chains[0].spinners[k].freq = freqH;
		chains[0].spinners[k].theta = phaseH;
		chains[0].spinners[k].rho = ampH;
		chains[1].spinners[k].freq = freqV;
		chains[1].spinners[k].theta = phaseV + M_PI/2;
		chains[1].spinners[k].rho = ampV;

//		printf("	Sav'd (%f, %f, %f)\n",
//				chains[1].spinners[k].rho,
//				chains[1].spinners[k].theta,
//				chains[1].spinners[k].freq);
//		printf("	addr: %d\n", &chains[1].spinners[k]);
	}
//	printf("Transform complete. Returning...\n");
	return true;
}
