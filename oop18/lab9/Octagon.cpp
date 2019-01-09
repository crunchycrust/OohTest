#include "Octagon.h"
#include <iostream>
#include <cmath>

Octagon::Octagon() : Octagon(0) {
}
Octagon::Octagon(size_t i) : side_a(i) {
}

Octagon::Octagon(const Octagon& orig) {
	side_a = orig.side_a;
}

Octagon::Octagon(std::istream &is) {
	std::cout << "PLEASE, one side of your octagon:\n";
	is >> side_a;
}

 
bool operator==(const Octagon& fst, const Octagon& snd) {
	return fst.side_a == snd.side_a;
}

std::ostream& operator<<(std::ostream& os, const Octagon& obj) {
	os<< "a = " << obj.side_a << std::endl;
	return os;
}

double Octagon::Square() {
	return 2*(side_a)*(side_a)*(1+sqrt(2));
}

void Octagon::Print() {
	std::cout << "Octagon: a = " << side_a << "; Square = "<< Square() << std::endl;
}

Octagon::~Octagon() {
}
