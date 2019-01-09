#include "Triangle.h"
#include <iostream>
#include <cmath>

Triangle::Triangle() : Triangle(0, 0, 0) {
}
Triangle::Triangle(size_t i, size_t j, size_t k) : side_a(i), side_b(j), side_c(k) {
}

Triangle::Triangle(const Triangle& orig) { //copy of our triangle
	side_a = orig.side_a;
	side_b = orig.side_b;
	side_c = orig.side_c;
}

Triangle::Triangle(std::istream &is) {
	std::cout << "Enter sides of your triangle:\n";
	is >> side_a;
	is >> side_b;
	is >> side_c;
}
 
bool operator==(const Triangle& fst, const Triangle& snd) {
	return fst.side_a == snd.side_a;
}
		 
std::ostream& operator<<(std::ostream& os, const Triangle& obj) {
	os<< "a = " << obj.side_a << std::endl;
	return os;
}

double Triangle::Square() {
	double p = double(side_a + side_b + side_c) / 2.0;
	return sqrt(p * (p - double(side_a))*(p - double(side_b))*(p - double(side_c)));
}

void Triangle::Print() {
	std::cout << "a=" << side_a << ", b=" << side_b << ", c=" << side_c << std::endl;
}

Triangle::~Triangle() {
}
