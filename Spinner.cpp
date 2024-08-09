/*
 * Spinner.cpp
 *
 *  Created on: Feb 5, 2019
 *      Author: robert
 */

#include "Spinner.h"
#include <cmath>
#include <stdio.h>

Spinner Spinner::fromCartesian(double x, double y){
	double rho = sqrt(pow(x, 2) + pow(y, 2));
	double theta = atan2(y, x);
	return Spinner{rho, theta, 1};
}

Spinner Spinner::operator +(const Spinner& inp){
	// ugly to look at and read, but better than explicitly declaring 6 doubles (compiler optimization, or whatever)
	double x = (cos(inp.theta)*inp.rho)+(cos(this->theta)*this->rho);
	double y = (sin(inp.theta)*inp.rho)+(sin(this->theta)*this->rho);
	return Spinner(sqrt(pow(x, 2) + pow(y, 2)), atan2(y, x));
}

Spinner Spinner::operator -(const Spinner& inp){
	double x = (cos(inp.theta)*inp.rho)-(cos(this->theta)*this->rho);
	double y = (sin(inp.theta)*inp.rho)-(sin(this->theta)*this->rho);
	return Spinner(sqrt(pow(x, 2) + pow(y, 2)), atan2(y, x));
}

double Spinner::getX(){ return cos(this->theta) * this->rho; }
double Spinner::getY(){ return sin(this->theta) * this->rho; }

/*	// The following is a verbose version of the addition & subtraction operators
	double x1 = cos(inp.theta)*inp.rho;
	double y1 = sin(inp.theta)*inp.rho;
	double x2 = cos(this->theta)*this->rho;
	double y2 = sin(this->theta)*this->rho;
	double x3 = x1+x2;
	double y3 = y1+y2;
	Spinner s = Spinner(0, 0);
	s.theta = atan2(y3, x3);
	s.rho = sqrt(pow(x3, 2) + pow(y3, 2));
	return s;
}*/
