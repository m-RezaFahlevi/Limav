#include "linav.h"
#include <iostream>

void anum::print(Vector v) {
	const unsigned int Dimension = v.get_dim();
	std::cout << "(";
	for (int i = 0; i < Dimension; i++)
		std::cout << v.accs(i) << ", ";
	std::cout << "\b\b \b)";
}

void anum::println(Vector v) {
	print(v);
	std::cout << '\n';
}

void anum::print(Vector v, std::string sentence) {
	std::cout << sentence;
	print(v);
}

void anum::println(Vector v, std::string sentence) {
	print(v, sentence);
	std::cout << '\n';
}

void anum::print(std::string sentence, Vector v) { print(v, sentence); }

void anum::println(std::string sentence, Vector v) { println(v, sentence); }

void anum::print(double scalar) { std::cout << scalar; }

void anum::println(double scalar) {
	print(scalar);
	std::cout << '\n';
}

void anum::print(double scalar, std::string sentence) {
	std::cout << sentence;
	print(scalar);
}

void anum::println(double scalar, std::string sentence) {
	print(scalar, sentence);
	std::cout << '\n';
}

void anum::print(std::string sentence, double scalar) { print(scalar, sentence); }

void anum::println(std::string sentence, double scalar) { println(scalar, sentence); }

void anum::print(std::string sentence) { std::cout << sentence; }

void anum::println(std::string sentence) { print(sentence); std::cout << '\n'; }
