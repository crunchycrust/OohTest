#include "Hexagon.h"
#include <iostream>
#include <cmath>

Hexagon::Hexagon() : Hexagon(0) {
}
Hexagon::Hexagon(size_t i) : side_a(i) {
}

Hexagon::Hexagon(const Hexagon& orig) { //copy of the hexagon
	side_a = orig.side_a;	
}

Hexagon::Hexagon(std::istream &is) {
	is >> side_a;
}

bool operator==(const Hexagon& fst, const Hexagon& snd) {
	return fst.side_a == snd.side_a;	
}

std::ostream& operator<<(std::ostream& os, const Hexagon& obj) {
	os<< "a = " << obj.side_a << std::endl;
	return os;
}

double Hexagon::Square() {
	return 3*sqrt(3)*(side_a)*(side_a)/2;
}

void Hexagon::Print() {
	std::cout << "a=" << side_a << std::endl;
}

Hexagon::~Hexagon() {

}
