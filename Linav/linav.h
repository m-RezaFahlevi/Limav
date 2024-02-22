#ifndef LINAV_H
#define LINAV_H

#include <vector>
#include <string>

namespace anum {
	// Linav stand for Linear algebra vector
	// All method of Linav instance is in linav.cpp file.
	class Vector {
		std::vector<double> x;
		unsigned int D; // dimension
		public:
			Vector(); // default constructor, return a null vector in 2-dimension
			Vector(unsigned int dimension); // return a null vector in d-dimension
			Vector(std::vector<double>);
			double accs(unsigned int ith_position); // get the ith-value of x
			void updt(unsigned int ith_position, double); // change the ith_componenth of vector
			unsigned int get_dim();
	};

	// All of these void functions are in printprog.cpp
	void print(Vector);
	void println(Vector);
	void print(Vector, std::string sentence);
	void println(Vector, std::string sentence);
	void print(std::string sentence, Vector);
	void println(std::string sentence, Vector);
	void print(double);
	void println(double);
	void print(double, std::string sentence);
	void println(double, std::string sentence);
	void print(std::string sentence, double);
	void println(std::string sentence, double);
	void print(std::string sentence);
	void println(std::string sentence);

}

// All of these linear operators are in linop.cpp file
anum::Vector operator +(anum::Vector lhs, anum::Vector rhs); // pointwise addition
anum::Vector operator -(anum::Vector lhs, anum::Vector rhs); // pointwise substraction
anum::Vector operator *(anum::Vector lhs, anum::Vector rhs); // elementwise multiplication
anum::Vector operator *(double, anum::Vector); // s-multiplication
anum::Vector operator *(anum::Vector, double); // s-multiplication
anum::Vector abs(anum::Vector); // elementwise absolute value
double sum(anum::Vector); // the Kahan's sum
anum::Vector power(anum::Vector, double); // the pointwise power
double lpnorm(anum::Vector, double p); // the lpnorm
double eunorm(anum::Vector); // the Euclidean norm
double inpro(anum::Vector, anum::Vector); // the inner product
double distance(anum::Vector, anum::Vector); // the Euclidean distance of two vector
anum::Vector normalize(anum::Vector); // compute the normalize vector, i.e. vector which has eunorm is one.

#endif
