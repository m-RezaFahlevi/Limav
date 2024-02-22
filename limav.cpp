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
	}
	anum::Vector v (cpp_vec);
	return v;
}
