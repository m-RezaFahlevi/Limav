#include "limav.h"
#include <stdexcept>
#include <stdlib.h>
#include <iostream>

anum::Vector operator *(anum::Matrix mat, anum::Vector vec) {
	// check if such performance can be performed or not
	// i.e., #col(mat) = dim(vec)
	const unsigned int comm_term = mat.col();
	std::vector<double> cpp_vec;
	try {
		if (comm_term != vec.get_dim()) {
			throw std::domain_error("ncol of matrix must be equal to dim of vectors\n");
		}
		for (int i = 0; i < mat.row(); i++) {
			double temp_sum = 0.0;
			for (int j = 0; j < comm_term; j++) {
				temp_sum += mat.accs(i, j) * vec.accs(j); // sum a_ij * x_j
			}
			cpp_vec.push_back(temp_sum);
		}
	} catch (const std::domain_error &doerr) {
		std::cerr << "ERROR: " << doerr.what();
		std::exit(EXIT_FAILURE);
	}
	anum::Vector v (cpp_vec);
	return v;
}

anum::Matrix t(anum::Matrix A) {
	const unsigned int a_row = A.row();
	const unsigned int a_col = A.col();
	std::vector<double> cpp_vec;
	for (int i = 0; i < a_col; i++) {
		for (int j = 0; j < a_row; j++) {
			cpp_vec.push_back(A.accs(j, i));
		}
	}
	anum::Matrix A_t (cpp_vec, a_col, a_row);
	return A_t;
}

anum::Matrix t(anum::Vector vec) {
	const unsigned int a_col = vec.get_dim();
	std::vector<double> cpp_vec;
	for (int i = 0; i < a_col; i++) {
		cpp_vec.push_back(vec.accs(i));
	}
	anum::Matrix A_t (cpp_vec, 1, a_col);
	return A_t;
}
