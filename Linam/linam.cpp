#include "linam.h"
#include <vector>
#include <stdlib.h>
#include <stdexcept>
#include <iostream>
#include <string>

// parameterized constructor of a matrix
anum::Matrix::Matrix(std::vector<double> vec, unsigned int m_row, unsigned int n_col) {
	this->mrow = m_row;
	this->ncol = n_col;
	const unsigned int DIM = m_row * n_col;
	try {
		// Elements of matrix is initialized by row
		std::vector<double>::const_iterator itr_vec = vec.begin();
		for (itr_vec = vec.begin(); itr_vec != vec.end(); itr_vec++) {
			this->matel.push_back(*itr_vec);
		}
		if (vec.size() != DIM) {
			throw std::domain_error("WARNING: Length of the elements is not equal to mrow * ncol");
		}
	} catch (const std::domain_error& doerr) {
		std::cerr << doerr.what() << '\n';
		std::cerr << "Length of the elements = " << vec.size() << '\n';
		std::cerr << "Size of the matrix (mrow * ncol) = " << this->mrow << "x" << this->ncol << " = " << DIM << '\n';
		const unsigned int remainder = DIM - vec.size();
		if (vec.size() == 0) {
			std::cerr << this->mrow << "x" << this->ncol << " null matrix is constructed\n";
			for (int idx = 0; idx < remainder; idx++) {
				this->matel.push_back(0.0);
			}
		} else if (vec.size() < DIM) {
			std::cerr << "The rest of the elements of the matrix are assigned by 0.0\n";
			for (int idx = 0; idx < remainder; idx++) {
				this->matel.push_back(0.0);
			}
		} else {
			std::cerr << "The rest of the elements are ignored\n";
		}
	} catch (const std::exception &e) {
		std::cerr << e.what() << '\n';
		std::exit(EXIT_FAILURE);
	}
}

unsigned int anum::Matrix::row() { return this->mrow; }
unsigned int anum::Matrix::col() { return this->ncol; }

double anum::Matrix::accs(unsigned int ith_row, unsigned int jth_col) {
	unsigned int idx; // index
	double anel; // an element
	try {
		if (ith_row > (this->mrow - 1)) { // range for i = 0, 1, ..., mrow - 1
			const std::string orr_log = "ERROR: Row Is Out of Range\nRange for ith_row = 0, 1, ..., mrow-1\n";
			throw std::out_of_range(orr_log);
		}
		if (jth_col > (this->ncol - 1)) { // range for j = 0, 1, ..., ncol - 1
			const std::string orr_log = "ERROR: Column Is Out of Range\nRange for jth_col = 0, 1, ..., ncol-1\n";
			throw std::out_of_range(orr_log);
		}
		idx = (ith_row * this->ncol) + jth_col;
		anel = this->matel.at(idx);
	} catch (const std::out_of_range &oor) {
		anel = 1.0;
		std::cerr << oor.what();
		std::cerr << "Size of the matrix is " << this->mrow << "x" << this->ncol << "\n";
		std::exit(EXIT_FAILURE);
	} catch (const std::exception &e) {
		std::cerr << e.what() << '\n';
		std::exit(EXIT_FAILURE);
	}
	return anel;
}

void anum::Matrix::updt(double val, unsigned int ith_row, unsigned int jth_col) {
	try {
		if (ith_row > (this->mrow - 1)) { // range for ith_row = 0, 1, ..., mrow - 1
			const std::string orr_log = "ERROR: Row Is Out of Range\nRange for ith_row = 0, 1, ..., mrow-1\n";
			throw std::out_of_range(orr_log);
		}
		if (jth_col > (this->ncol - 1)) { // range for jth_col = 0, 1, ..., ncol - 1
			const std::string orr_log = "ERROR: Column Is Out of Range\nRange for jth_col = 0, 1, ..., ncol-1\n";
			throw std::out_of_range(orr_log);
		}
		const unsigned int idx = (ith_row * this->ncol) + jth_col;
		this->matel.at(idx) = val;
	} catch (const std::out_of_range &oor) {
		std::cerr << oor.what();
		std::cerr << "Size of the matrix is " << this->mrow << "x" << this->ncol << "\n";
		std::exit(EXIT_FAILURE);
	} catch (const std::exception &e) {
		std::cerr << e.what() << '\n';
		std::exit(EXIT_FAILURE);
	}
}
