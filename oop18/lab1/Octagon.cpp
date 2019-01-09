#include "Octagon.h"
#include <iostream>
#include <cmath>

Octagon::Octagon() : Octagon(0) {
}
Octagon::Octagon(size_t i) : side_a(i) {
	std::cout << "Octagon created: " << side_a << std::endl;
}

Octagon::Octagon(std::istream &is) {
	is >> side_a;
}

double Octagon::Square() {
	return 2*(side_a)*(side_a)*(1+sqrt(2));
}

void Octagon::Print() {
	std::cout << "a=" << side_a << std::endl;
}

Octagon::~Octagon() {
	std::cout << "Octagon deleted" << std::endl;
}
