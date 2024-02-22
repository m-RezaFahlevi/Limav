#include "linav.h"
#include <math.h>
#include <limits>
#include <iostream>
#include <stdlib.h>
#include <stdexcept>

// pointwsie addition
anum::Vector operator +(anum::Vector lhs, anum::Vector rhs) {
	std::vector<double> v;
	const unsigned int DIM = lhs.get_dim();
	try {
		// check the criteria of adding two vectors, if two vectors
		// have different dimension each other, then domain error
		// will be catched.
		if (lhs.get_dim() != rhs.get_dim())
			throw std::domain_error("cannot add two vectors having different dimension\n");
		for (int ith = 0; ith < DIM; ith++) {
			double temp = lhs.accs(ith) + rhs.accs(ith);
			v.push_back(temp);
		}
	} catch (const std::domain_error& doerr) {
		std::cerr << "ERROR: Domain Error Occurs: " << doerr.what();
		std::exit(EXIT_FAILURE);
	}
	anum::Vector C(v); // create a new instance of vector C
	return C;
}

// pointwise substraction
anum::Vector operator -(anum::Vector lhs, anum::Vector rhs) {
	std::vector<double> v;
	const unsigned int DIM = lhs.get_dim();
	try {
		// check the criteria of performing pointwise substraction of two vectors.
		// If two vectors have different dimension, then domain error will be catched.
		if (DIM != rhs.get_dim())
			throw std::domain_error("cannot substract two vectors having different dimension\n");
		for (int ith = 0; ith < DIM; ith++) {
			double temp = lhs.accs(ith) - rhs.accs(ith);
			v.push_back(temp);
		}
	} catch (const std::domain_error &doerr) {
		std::cerr << "ERROR: Domain Error Occurs: " << doerr.what();
		std::exit(EXIT_FAILURE);
	}
	anum::Vector V(v);
	return V;
}

// pointwise multiplication
anum::Vector operator *(anum::Vector lhs, anum::Vector rhs) {
	std::vector<double> v;
	const unsigned int DIM = lhs.get_dim();
	try {
		// check the criteria of performing pointwise multiplication of two vectors.
		// If two vectors have different dimension, then terminate the program.
		if (DIM != rhs.get_dim())
			throw std::domain_error("cannot do pointwise multiplication of two vectors having different dimension\n");
		for (int ith = 0; ith < DIM; ith++) {
			double temp = lhs.accs(ith) * rhs.accs(ith);
			v.push_back(temp);
		}
	} catch (const std::domain_error &doerr) {
		std::cerr << "ERROR: Domain Error Occurs: " << doerr.what();
		std::exit(EXIT_FAILURE);
	}
	
	anum::Vector V(v);
	return V;
}

// s-multiplication
anum::Vector operator *(double scalar, anum::Vector rhs) {
	std::vector<double> v;
	const unsigned int Dimension = rhs.get_dim();
	for (int ith = 0; ith < Dimension; ith++) {
		double temp = scalar * rhs.accs(ith);
		v.push_back(temp);
	}
	anum::Vector V(v);
	return V;
}

anum::Vector operator *(anum::Vector rhs, double scalar) { return scalar * rhs; }

// pointwise absolute value
anum::Vector abs(anum::Vector v) {
	std::vector<double> v_abs;
	const unsigned int Dimension = v.get_dim();
	for (int ith = 0; ith < Dimension; ith++) {
		double temp = std::abs(v.accs(ith));
		v_abs.push_back(temp);
	}
	anum::Vector V(v_abs);
	return V;
}

// The Kahan's sum
double sum(anum::Vector v) {
	double khs = 0.0; // kahan's sum
	double khs_next = 0.0; // next khs
	double c = 0.0; // compute the compensate
	double temp = 0.0;
	const unsigned int Dimension = v.get_dim();
	for (int ith = 0; ith < Dimension; ith++) {
		temp = v.accs(ith) + c;
		khs_next = khs + temp;
		c = temp - (khs_next - khs);
		khs = khs_next;
	}
	return khs;
}

anum::Vector power(anum::Vector v, double p) {
	const unsigned int Dimension = v.get_dim();
	std::vector<double> v_pwr;
	for (int ith = 0; ith < Dimension; ith++) {
		double temp = std::pow(v.accs(ith), p);
		v_pwr.push_back(temp);
	}
	anum::Vector V(v_pwr);
	return V;
}

double lpnorm(anum::Vector v, double p) {
	// maxel is maximum absolute element. To avoid division
	// by zero, initially, maxel is epsilon
	double maxel = std::numeric_limits<double>::epsilon();
	// looking for the max absolute element of v
	// by using linear search;
	const unsigned int Dimension = v.get_dim();
	for (int ith = 0; ith < Dimension; ith++) {
		bool is_updt = std::abs(v.accs(ith)) > maxel;
		maxel = is_updt ? std::abs(v.accs(ith)) : maxel;
	}
	// create a new vector x s.t. x := (1/maxel) v
	std::vector<double> vtemp;
	for (int ith = 0; ith < Dimension; ith++) {
		double temp = std::abs(v.accs(ith) / maxel);
		vtemp.push_back(temp);
	}
	anum::Vector vpnorm(vtemp);
	vpnorm = power(vpnorm, p); // pointwise powered by p
	// take the pth-root after Kahan's sum, then multiply it back by
	// maximum element maxel to get the pnorm of v
	double pnormval = maxel * std::pow(sum(vpnorm), std::pow(p, -1.0));
	return pnormval;
}

// special case of lpnorm is when p = 2,
// it's known as the Euclidean norm
double eunorm(anum::Vector v) { return lpnorm(v, 2.0); }

// inner product
double inpro(anum::Vector u, anum::Vector v) {
	double val_inpro;
	try {
		// check the criteria of performing inner product. If two vectors
		// have different dimension, then domain error will be catched.
		if (u.get_dim() != v.get_dim())
			throw std::domain_error("Cannot take inner product of two vectors having different dimension\n");
		// looking for the max of the absolute element of vectors u and v
		// by using linear search.
		const unsigned int Dimension = u.get_dim();
		double u_max = std::numeric_limits<double>::epsilon();
		double v_max = std::numeric_limits<double>::epsilon(); 
		for (int ith = 0; ith < Dimension; ith++) {
			double u_temp = std::abs(u.accs(ith));
			double v_temp = std::abs(v.accs(ith));
			if (u_temp > u_max) u_max = u_temp;
			if (v_temp > v_max) v_max = v_temp;
		}
		anum::Vector u_shr = u * std::pow(u_max, -1.0); // u_shr is u shrinked
		anum::Vector v_shr = v * std::pow(v_max, -1.0); // v_shr is v shrinked
		val_inpro = u_max * v_max * sum(u_shr * v_shr);
	} catch (const std::domain_error &doerr) {
		std::cerr << "ERROR: Domain Error Occurs: " << doerr.what();
		std::exit(EXIT_FAILURE);
	}
	return val_inpro;
}


// the Euclidean distance of two vector
double distance(anum::Vector u, anum::Vector v) { return eunorm(u - v); }

// compute the normalize vector, i.e.,
// vector which has the Euclidean norm is equal to one
anum::Vector normalize(anum::Vector v) {
	double mu = eunorm(v);
	anum::Vector v_hat = v * (std::pow(mu, -1.0)); // v_hat := (1/mu) * v
	return v_hat;
}
