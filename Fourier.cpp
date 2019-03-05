/*
 * Fourier.cpp
 *
 *  Created on: Feb 15, 2019
 *      Author: robert
 */

#include "Fourier.h"
#include <cmath>
#include <stdio.h>

Chain** Fourier::createDFT(Point2D* signal, int N, int K){
	printf("Reading signal of len %d, creating samples %d\n", N, K);
	Chain* chains[] = new Chain[2]{
		new Chain(K, Spinner(0, 0, 0)),
		new Chain(K, Spinner(0, 0, 0))
	};

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
			reHori += signal[n].x * cos(phi);
			imHori -= signal[n].x * sin(phi);
			 // vertical spinners
			reVert += signal[n].y * cos(phi);
			imVert -= signal[n].y * sin(phi);
		}
//		printf("DFT Params -> re: %d, im: %d\n", reHori, imHori);
		reHori = reHori/N;
		imHori = imHori/N;
		reVert = reVert/N;
		imVert = imVert/N;
		double ampH = sqrt(reHori*reHori + reHori*reHori);
		double phaseH = atan2(reHori, reHori);
		double freqH = k;
		double ampV = sqrt(imVert*reHori + imVert*reHori);
		double phaseV = atan2(imVert, reHori);
		double freqV = k;
//		printf("[%d/%d] <||> (rho:%f, theta:%f, freq:%f)\n", k, (K-1), ampH, phaseH, freqH);
		Spinner* sV = new Spinner(ampV, phaseV, freqV);
		Spinner* sH = new Spinner(ampH, phaseH, freqH);

		chains[0]->spinners[k] = *sH;
		chains[1]->spinners[k] = *sV;
//		printf("spinner properties: (%f, %f, %f)\n",
//				chains[c]->spinners[k].rho,
//				chains[c]->spinners[k].theta,
//				chains[c]->spinners[k].freq);
	}
	printf("Transform complete. Returning...\n");
	return chains;
}
