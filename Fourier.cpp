/*
 * Fourier.cpp
 *
 *  Created on: Feb 15, 2019
 *      Author: robert
 */

#include "Fourier.h"
#include <cmath>
#include <stdio.h>

Chain* Fourier::createDFT(Point2D* signal, int N, int K){
	printf("Reading signal of len %d, creating samples %d\n", N, K);
	Chain *chains[2] = {new Chain(K, Spinner(0, 0)),
						new Chain(K, Spinner(0, 0))
	};
	for(int c = 0; c < 2; c++){// do both horizontal & vertical components.
		for(int k=0; k<K; k++){
			double re = 0; // the real portion of the Fourier transform
			double im = 0; // the imaginary portion """
			for(int n=0; n<N; n++){
	//			printf("chunk loop iter %d/%d\n", n, (length-1));
				double phi = (2*M_PI * k * n) / N;
				re += signal[n].x * cos(phi);
				im -= signal[n].x * sin(phi);
			}
			printf("DFT Params -> re: %d, im: %d\n", re, im);
			re = re/N;
			im = im/N;
			double amp = sqrt(pow(re, 2) + pow(im,2));
			double phase = atan2(re, im);
			double freq = k;
			printf("[%d/%d] <||> (rho:%f, theta:%f, freq:%f)\n", k, (K-1), amp, phase, freq);
			Spinner s = Spinner(amp, phase, freq);
			chains[c]->spinners[k] = s;
			printf("spinner properties: (%f, %f, %f)\n",
					chains[c]->spinners[k].rho,
					chains[c]->spinners[k].theta,
					chains[c]->spinners[k].freq);
		}
	}
	return *chains;
}
