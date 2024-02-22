#include "linav.h"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <stdlib.h>

/*
 * If Vector v is constructed without
 * any parameter, then v is assumed to be
 * a zero vector in R^2.
 */
anum::Vector::Vector() {
	this->D = 2;
	this->x.push_back(0);
	this->x.push_back(0);
}

/*
 * Declare a null vector
 * in D-dimension
 */
anum::Vector::Vector(unsigned int dimension) {
	for (int i = 0; i < dimension; i++)
		this->x.push_back(0);
	this->D = dimension;
}

/*
 * Declare the vector x = (x1, x2, ..., xn);
 */
anum::Vector::Vector(std::vector<double> v) {
	this->D = v.size();
	std::vector<double>::const_iterator itr_v = v.begin();
	for (int i = 0; i < D; i++) {
		this->x.push_back(*itr_v);
		++itr_v;
	}
}

// get the ith-value of x
double anum::Vector::accs(unsigned int ith_position) {
	double ith_comp;
	try {
		ith_comp = this->x.at(ith_position);
	} catch (const std::out_of_range& oor) {
		std::cerr << "ERROR: Out of Range Error Occurs: " << oor.what() << ' ';
		std::cerr << "the avaiable indexes are 0-" << D - 1 << '\n';
		std::exit(EXIT_FAILURE);
	}
	return ith_comp;
}

// change the ith_component/element of vector
void anum::Vector::updt(unsigned int ith_position, double val) {
	try {
		this->x.at(ith_position) = val;
	} catch(const std::out_of_range& oor) {
		std::cerr << "ERROR: Out of Range Error Occurs: " << oor.what() << ' ';
		std::cerr << "the avaiable indexes are 0-" << D - 1 << '\n';
		std::exit(EXIT_FAILURE);
	}
}

unsigned int anum::Vector::get_dim() { return this->D; } // get the dimension of x
