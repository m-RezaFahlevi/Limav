#include "linam.h"
#include <iostream>


void anum::println(anum::Matrix A) {
	const unsigned int mrow = A.row();
	const unsigned int ncol = A.col();
	for (int i = 0; i < mrow; i++) {
		for (int j = 0; j < ncol; j++) {
			std::cout << A.accs(i, j) << " ";
		}
		std::cout << '\n';
	}
}

void anum::println(std::string sentence, Matrix A) {
	std::cout << sentence << '\n';
	println(A);
}
