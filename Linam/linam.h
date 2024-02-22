#ifndef LINAM_H
#define LINAM_H

#include <vector>
#include <string>

namespace anum {
	class Matrix {
		unsigned int mrow;
		unsigned int ncol;
		std::vector<double> matel; // elements of the matrix
		public:
			Matrix(std::vector<double>, unsigned int m_row, unsigned int n_col); // parameterized constructor
			unsigned int row();
			unsigned int col();
			double accs(unsigned int ith_row, unsigned int jth_col);
			void updt(double val, unsigned int ith_row, unsigned int jth_col);
	};
	
	// this println function are in printprog.cpp
	void println(Matrix A);
	void println(std::string, Matrix A);
}

// all of thes operators are in matop.cpp
anum::Matrix operator +(anum::Matrix A, anum::Matrix B);
anum::Matrix operator -(anum::Matrix A, anum::Matrix B);
anum::Matrix operator *(anum::Matrix A, anum::Matrix B);
anum::Matrix operator *(double sc, anum::Matrix A);

#endif
