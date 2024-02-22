#include "linam.h"
#include <stdexcept>
#include <iostream>
#include <stdlib.h>

anum::Matrix operator+(anum::Matrix A, anum::Matrix B) {
	const unsigned int mrow = A.row();
	const unsigned int ncol = A.col();
	std::vector<double> cpp_vec;
	try {
		// check criteria if A and B do not violet the domains
		// if A and B have the same row and column, then matrices
		// addition can be performed. Otherwise, terminate the program
		if ((mrow != B.row()) || (ncol != B.col())) {
			throw std::domain_error("A and B have different numbers of row and/or column\n");
		}
		for (int i = 0; i < mrow; i++) {
			for (int j = 0; j < ncol; j++) {
				double c_ij = A.accs(i, j) + B.accs(i, j); // c_ij = a_ij + b_ij
				cpp_vec.push_back(c_ij);
			}
		}
	} catch (const std::domain_error &doerr) {
		std::cerr << doerr.what();
		std::exit(EXIT_FAILURE);
	} catch (const std::exception e) {
		std::cerr << e.what() << '\n';
		std::terminate();
	}
	anum::Matrix C (cpp_vec, mrow, ncol);
	return C; // C = A + B
}

anum::Matrix operator-(anum::Matrix A, anum::Matrix B) {
	const unsigned int mrow = A.row();
	const unsigned int ncol = A.col();
	std::vector<double> cpp_vec;
	try {
		// check criteria if A and B do not violet the domains
		// if A and B have the same row and column, then matrices
		// substraction can be performed. Otherwise, terminate the program
		if ((mrow != B.row()) || (ncol != B.col())) {
			throw std::domain_error("A and B have different numbers of row and/or column\n");
		}
		for (int i = 0; i < mrow; i++) {
			for (int j = 0; j < ncol; j++) {
				double c_ij = A.accs(i, j) - B.accs(i, j); // c_ij = a_ij - b_ij
				cpp_vec.push_back(c_ij);
			}
		}
	} catch (const std::domain_error &doerr) {
		std::cerr << doerr.what();
		std::exit(EXIT_FAILURE);
	} catch (const std::exception e) {
		std::cerr << e.what() << '\n';
		std::terminate();
	}
	anum::Matrix C (cpp_vec, mrow, ncol);
	return C; // C = A - B

}

anum::Matrix operator*(anum::Matrix A, anum::Matrix B) {
	const unsigned int a_mrow = A.row();
	const unsigned int b_ncol = B.col();
	const unsigned int comm_term = A.col(); // (exclusive) or B.row()
	std::vector<double> cpp_vec;
	try {
		// check the criteria to perform matrix multiplication
		// i.e. if C = AB, then the number of columns of matrix A must equals to
		// the number of rows of matrix B, so that for C = AB, C is matrix s.t.
		// C.row() equals to A.row() and C.col() equals to B.col()
		if (A.col() != B.row())
			throw std::domain_error("ERROR: Domains of Error Occus\n");
		double c_ij;
		for (int i = 0; i < a_mrow; i++) {
			for (int j = 0; j < b_ncol; j++) {
				double temp_sum = 0;
				for (int k = 0; k < comm_term; k++) {
					temp_sum += A.accs(i, k) * B.accs(k, j);
				}
				cpp_vec.push_back(temp_sum);
			}
		}
	} catch (const std::domain_error &doerr) {
		std::cerr << doerr.what();
		std::cerr << "C = AB, cols of A must be equals to rows of B\n";
		std::exit(EXIT_FAILURE);
	}
	anum::Matrix C (cpp_vec, a_mrow, b_ncol);
	return C;
}

anum::Matrix operator *(double sc, anum::Matrix A) {
	std::vector<double> cpp_vec;
	const unsigned int a_row = A.row();
	const unsigned int a_col = A.row();
	for (int i = 0; i < a_row; i++) {
		for (int j = 0; j < a_row; j++) {
			cpp_vec.push_back(sc * A.accs(i, j));
		}
	}
	anum::Matrix sc_A (cpp_vec, a_row, a_col); // scaled A
	return sc_A;
}
