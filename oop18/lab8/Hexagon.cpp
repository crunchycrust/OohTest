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

/*Hexagon::Hexagon(std::istream &is) {
	std::cout << "One side of your hexagon, please:\n";
	is >> side_a;
}*/

bool Hexagon::operator==(const Hexagon &obj) const
{
    return (this->side_a == obj.side_a);
}

Hexagon Hexagon::operator=(const Hexagon &obj)
{
    if (&obj == this) {
        return *this;
    }
    side_a = obj.side_a;
    return *this;
}
std::ostream& operator<<(std::ostream& os, const Hexagon& obj) {
    os << obj.side_a << std::endl;
    return os;
}

std::istream& operator>>(std::istream &is, Hexagon &obj)
{
    std::cout << "One side of your hexagon, please:\n";
    is >> obj.side_a;
    return is;
}

double Hexagon::Square() {
	return 3*sqrt(3)*(side_a)*(side_a)/2;
}

void Hexagon::Print() {
	std::cout << "Hexagon: a = " << this->side_a << "; Square = " << this->Square() << std::endl;
}
