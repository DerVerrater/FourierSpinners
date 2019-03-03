/*
 * Spinner.h
 *
 *  Created on: Feb 5, 2019
 *      Author: robert
 */

#ifndef SPINNER_H_
#define SPINNER_H_


class Spinner{
public:
	double rho, theta, freq;
	// arguments are radius, angle, frequency
	Spinner(double rho=0, double theta=0, double freq=1);
	~Spinner();
	static Spinner fromCartesian(double x, double y); // create a spinner from Cartesian space
	Spinner operator+(const Spinner& inp);
	Spinner operator-(const Spinner& inp);
	double getX();
	double getY();
};

#endif /* SPINNER_H_ */
