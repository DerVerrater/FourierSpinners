/*
 * Fourier.cpp
 *
 *  Created on: Feb 15, 2019
 *      Author: robert
 */

#include "Fourier.h"
#include <cmath>
#include <stdio.h>

bool Fourier::createDFT(Chain* chains, Point2D* signal, int N, int K){
	printf("Reading signal of len %d, creating samples %d\n", N, K);

	for(int k=0; k<K; k++){
		double reHori = 0; // the real portion of the Fourier transform
		double imHori = 0; // the imaginary portion """
		double reVert = 0;
		double imVert = 0;

		for(int n=0; n<N; n++){
//			printf("chunk loop iter %d/%d\n", n, (length-1));
			double phi = (2*M_PI * k * n) / N;
			// TODO: Find nicer way of picking Point2D variable (array-like offsets? Magic with pointers?)
			// horizontal spinners
			reHori += signal[n].x * sin(phi);
			imHori -= signal[n].x * cos(phi);
			 // vertical spinners
			reVert += signal[n].y * cos(phi);
			imVert -= signal[n].y * sin(phi);
		}
//		printf("DFT Params -> re: %d, im: %d\n", reHori, imHori);
		reHori = reHori/N;
		imHori = imHori/N;
		reVert = reVert/N;
		imVert = imVert/N;
		double ampH = sqrt(pow(reHori, 2) + pow(imHori, 2));
		double phaseH = atan2(reHori, imHori);
		double freqH = k;
		double ampV = sqrt(pow(reVert, 2) + pow(imVert, 2));
		double phaseV = atan2(reVert, imVert);
		double freqV = k;
//		printf("[%d/%d] =>rho:	theta:	freq:\n	Gen'd (%f, %f, %f)\n", k, (K-1), ampV, phaseV, freqV);

		// reassign values
		chains[0].spinners[k].freq = freqH;
		chains[0].spinners[k].theta = phaseH;
		chains[0].spinners[k].rho = ampH;
		chains[1].spinners[k].freq = freqV;
		chains[1].spinners[k].theta = phaseV;
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
